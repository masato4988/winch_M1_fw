/*
 * canfd.c
 *
 *  Created on: Sep 20, 2026
 *      Author: miyab
 */


#include <communication/canfd.h>
#include "fdcan.h"
#include "main.h"

#include <string.h>

extern FDCAN_HandleTypeDef hfdcan1;

/* -------------------------------------------------------------------------- */
/* Configuration                                                              */
/* -------------------------------------------------------------------------- */

#define CANFD_RX_QUEUE_SIZE    (16U)

/* -------------------------------------------------------------------------- */
/* Private variables                                                          */
/* -------------------------------------------------------------------------- */

static volatile CANFD_Frame_t s_rx_queue[CANFD_RX_QUEUE_SIZE];

static volatile uint8_t s_rx_write_index = 0U;
static volatile uint8_t s_rx_read_index  = 0U;

/* -------------------------------------------------------------------------- */
/* Private functions                                                          */
/* -------------------------------------------------------------------------- */

static uint8_t CANFD_GetNextIndex(uint8_t index)
{
    index++;

    if(index >= CANFD_RX_QUEUE_SIZE)
    {
        index = 0U;
    }

    return index;
}

static uint32_t CANFD_LengthToDLC(uint8_t length)
{
    if(length <= 8U)
    {
        return FDCAN_DLC_BYTES_0 + length;
    }
    else if(length <= 12U)
    {
        return FDCAN_DLC_BYTES_12;
    }
    else if(length <= 16U)
    {
        return FDCAN_DLC_BYTES_16;
    }
    else if(length <= 20U)
    {
        return FDCAN_DLC_BYTES_20;
    }
    else if(length <= 24U)
    {
        return FDCAN_DLC_BYTES_24;
    }
    else if(length <= 32U)
    {
        return FDCAN_DLC_BYTES_32;
    }
    else if(length <= 48U)
    {
        return FDCAN_DLC_BYTES_48;
    }
    else
    {
        return FDCAN_DLC_BYTES_64;
    }
}

static uint8_t CANFD_DLCToLength(uint32_t dlc)
{
    switch(dlc)
    {
    case FDCAN_DLC_BYTES_0:
        return 0U;

    case FDCAN_DLC_BYTES_1:
        return 1U;

    case FDCAN_DLC_BYTES_2:
        return 2U;

    case FDCAN_DLC_BYTES_3:
        return 3U;

    case FDCAN_DLC_BYTES_4:
        return 4U;

    case FDCAN_DLC_BYTES_5:
        return 5U;

    case FDCAN_DLC_BYTES_6:
        return 6U;

    case FDCAN_DLC_BYTES_7:
        return 7U;

    case FDCAN_DLC_BYTES_8:
        return 8U;

    case FDCAN_DLC_BYTES_12:
        return 12U;

    case FDCAN_DLC_BYTES_16:
        return 16U;

    case FDCAN_DLC_BYTES_20:
        return 20U;

    case FDCAN_DLC_BYTES_24:
        return 24U;

    case FDCAN_DLC_BYTES_32:
        return 32U;

    case FDCAN_DLC_BYTES_48:
        return 48U;

    case FDCAN_DLC_BYTES_64:
        return 64U;

    default:
        return 0U;
    }
}

/* -------------------------------------------------------------------------- */
/* Initialization                                                             */
/* -------------------------------------------------------------------------- */

void CANFD_Init(void)
{
    FDCAN_FilterTypeDef filter;

    memset(&filter, 0, sizeof(filter));

    filter.IdType       = FDCAN_STANDARD_ID;
    filter.FilterIndex  = 0U;
    filter.FilterType   = FDCAN_FILTER_MASK;
    filter.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;

    /*
     * Accept standard ID 0x100.
     *
     * FilterID1 = ID
     * FilterID2 = mask
     */
    filter.FilterID1 = 0x100U;
    filter.FilterID2 = 0x7FFU;

    HAL_FDCAN_ConfigFilter(&hfdcan1, &filter);

    /*
     * Reject non-matching frames.
     */
    HAL_FDCAN_ConfigGlobalFilter(
        &hfdcan1,
        FDCAN_REJECT,
        FDCAN_REJECT,
        FDCAN_REJECT_REMOTE,
        FDCAN_REJECT_REMOTE
    );

    HAL_FDCAN_Start(&hfdcan1);

    HAL_FDCAN_ActivateNotification(
        &hfdcan1,
        FDCAN_IT_RX_FIFO0_NEW_MESSAGE,
        0U
    );
}

void CANFD_Enable(void)
{
    HAL_GPIO_WritePin(
    	CAN_STBY_GPIO_Port,
        CAN_STBY_Pin,
        GPIO_PIN_RESET
    );
}

void CANFD_Disable(void)
{
    HAL_GPIO_WritePin(
        CAN_STBY_GPIO_Port,
        CAN_STBY_Pin,
        GPIO_PIN_SET
    );
}

/* -------------------------------------------------------------------------- */
/* Transmission                                                               */
/* -------------------------------------------------------------------------- */

bool CANFD_Send(uint32_t id,
                const uint8_t *data,
                uint8_t length)
{
    FDCAN_TxHeaderTypeDef tx_header;

    if(data == NULL)
    {
        return false;
    }

    if(length > CANFD_MAX_DATA_LENGTH)
    {
        return false;
    }

    memset(&tx_header, 0, sizeof(tx_header));

    tx_header.Identifier          = id;
    tx_header.IdType              = FDCAN_STANDARD_ID;
    tx_header.TxFrameType         = FDCAN_DATA_FRAME;
    tx_header.DataLength          = CANFD_LengthToDLC(length);
    tx_header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;

    /*
     * CAN FD + Bit Rate Switching
     */
    tx_header.BitRateSwitch       = FDCAN_BRS_ON;
    tx_header.FDFormat            = FDCAN_FD_CAN;

    tx_header.TxEventFifoControl  = FDCAN_NO_TX_EVENTS;
    tx_header.MessageMarker       = 0U;

    if(HAL_FDCAN_GetTxFifoFreeLevel(&hfdcan1) == 0U)
    {
        return false;
    }

    if(HAL_FDCAN_AddMessageToTxFifoQ(
            &hfdcan1,
            &tx_header,
            (uint8_t *)data) != HAL_OK)
    {
        return false;
    }

    return true;
}

/* -------------------------------------------------------------------------- */
/* Reception                                                                  */
/* -------------------------------------------------------------------------- */

bool CANFD_Receive(CANFD_Frame_t *frame)
{
    if(frame == NULL)
    {
        return false;
    }

    if(s_rx_read_index == s_rx_write_index)
    {
        return false;
    }

    frame->id     = s_rx_queue[s_rx_read_index].id;
    frame->length = s_rx_queue[s_rx_read_index].length;

    memcpy(
        frame->data,
        (const void *)s_rx_queue[s_rx_read_index].data,
        frame->length
    );

    s_rx_read_index = CANFD_GetNextIndex(s_rx_read_index);

    return true;
}

/* -------------------------------------------------------------------------- */
/* HAL callback                                                               */
/* -------------------------------------------------------------------------- */

void HAL_FDCAN_RxFifo0Callback(
    FDCAN_HandleTypeDef *hfdcan,
    uint32_t RxFifo0ITs)
{
    FDCAN_RxHeaderTypeDef rx_header;
    uint8_t data[CANFD_MAX_DATA_LENGTH];

    uint8_t next_write_index;
    uint8_t length;

    if(hfdcan->Instance != FDCAN1)
    {
        return;
    }

    if((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) == 0U)
    {
        return;
    }

    if(HAL_FDCAN_GetRxMessage(
            hfdcan,
            FDCAN_RX_FIFO0,
            &rx_header,
            data) != HAL_OK)
    {
        return;
    }

    length = CANFD_DLCToLength(rx_header.DataLength);

    if(length > CANFD_MAX_DATA_LENGTH)
    {
        return;
    }

    next_write_index = CANFD_GetNextIndex(s_rx_write_index);

    /*
     * Queue full.
     *
     * For now, discard the new frame.
     */
    if(next_write_index == s_rx_read_index)
    {
        return;
    }

    s_rx_queue[s_rx_write_index].id     = rx_header.Identifier;
    s_rx_queue[s_rx_write_index].length = length;

    memcpy(
        (void *)s_rx_queue[s_rx_write_index].data,
        data,
        length
    );

    s_rx_write_index = next_write_index;
}
