/*
 * motor_driver.c
 *
 *  Created on: Jul 28, 2026
 *      Author: miyab
 */
#include "actuator/motor/ir2302_bridge.h"
#include "actuator/motor/motor_driver.h"

static MotorState_t s_state = MOTOR_STATE_DISABLE;
static int16_t s_duty = 0;

/* private -----------------------------------------------------------*/

static void MotorDriver_OutputForward(uint16_t duty);
static void MotorDriver_OutputReverse(uint16_t duty);

/* public ------------------------------------------------------------*/

void MotorDriver_Init(void)
{
	IR2302bridge_Init();

    MotorDriver_SetDuty(0);
    MotorDriver_SetState(MOTOR_STATE_DISABLE);
}

void MotorDriver_SetState(MotorState_t state)
{
    s_state = state;

    switch(state)
    {
    case MOTOR_STATE_DISABLE:

    	IR2302bridge_Disable();

        break;

    case MOTOR_STATE_FREE:

    	IR2302bridge_Disable();

    	IR2302Bridge_SetHB1Duty(0);
    	IR2302Bridge_SetHB2Duty(0);

        break;

    case MOTOR_STATE_BRAKE:

    	IR2302bridge_Enable();

        /* 両Low Side ON */
    	IR2302Bridge_SetHB1Duty(0);
    	IR2302Bridge_SetHB2Duty(0);

        break;

    case MOTOR_STATE_DRIVE:

    	IR2302bridge_Enable();

        /* 現在Dutyを反映 */
        MotorDriver_SetDuty(s_duty);

        break;

    case MOTOR_STATE_REGEN:

        /* 将来実装 */

        break;
    }
}

void MotorDriver_SetDuty(int16_t duty)
{
    if(duty > 1000)
    {
        duty = 1000;
    }

    if(duty < -1000)
    {
        duty = -1000;
    }

    s_duty = duty;

    if(s_state != MOTOR_STATE_DRIVE)
    {
        return;
    }

    if(duty >= 0)
    {
        MotorDriver_OutputForward((uint16_t)duty);
    }
    else
    {
        MotorDriver_OutputReverse((uint16_t)(-duty));
    }
}

MotorState_t MotorDriver_GetState(void)
{
    return s_state;
}

int16_t MotorDriver_GetDuty(void)
{
    return s_duty;
}

/* private -----------------------------------------------------------*/

static void MotorDriver_OutputForward(uint16_t duty)
{
	IR2302Bridge_SetHB1Duty(duty);
	IR2302Bridge_SetHB2Duty(0);
}

static void MotorDriver_OutputReverse(uint16_t duty)
{
	IR2302Bridge_SetHB1Duty(0);
	IR2302Bridge_SetHB2Duty(duty);
}

