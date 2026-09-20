/*
 * canfd.h
 *
 *  Created on: Sep 20, 2026
 *      Author: miyab
 */

#ifndef INC_COMMUNICATION_CANFD_H_
#define INC_COMMUNICATION_CANFD_H_

#include <stdint.h>
#include <stdbool.h>

#define CANFD_MAX_DATA_LENGTH    (64U)

/* -------------------------------------------------------------------------- */
/* CAN FD node IDs                                                            */
/* -------------------------------------------------------------------------- */

#define CANFD_NODE_MASTER        (0U)
#define CANFD_NODE_WINCH_1      (1U)
#define CANFD_NODE_WINCH_2      (2U)
#define CANFD_NODE_WINCH_3      (3U)
#define CANFD_NODE_WINCH_4      (4U)

/* -------------------------------------------------------------------------- */
/* CAN FD frame                                                               */
/* -------------------------------------------------------------------------- */

typedef struct
{
    uint32_t id;
    uint8_t  length;
    uint8_t  data[CANFD_MAX_DATA_LENGTH];
} CANFD_Frame_t;

/* -------------------------------------------------------------------------- */
/* Initialization                                                             */
/* -------------------------------------------------------------------------- */

void CANFD_Init(void);

void CANFD_Enable(void);
void CANFD_Disable(void);

/* -------------------------------------------------------------------------- */
/* Transmission                                                               */
/* -------------------------------------------------------------------------- */

bool CANFD_Send(uint32_t id,
                const uint8_t *data,
                uint8_t length);

/* -------------------------------------------------------------------------- */
/* Reception                                                                  */
/* -------------------------------------------------------------------------- */

bool CANFD_Receive(CANFD_Frame_t *frame);


#endif /* INC_COMMUNICATION_CANFD_H_ */
