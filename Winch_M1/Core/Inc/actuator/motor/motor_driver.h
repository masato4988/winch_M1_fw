/*
 * driver.h
 *
 *  Created on: Jul 28, 2026
 *      Author: miyab
 */

#ifndef INC_ACTUATOR_MOTOR_MOTOR_DRIVER_H_
#define INC_ACTUATOR_MOTOR_MOTOR_DRIVER_H_


#include <stdint.h>

typedef enum
{
    MOTOR_STATE_DISABLE,
    MOTOR_STATE_FREE,
    MOTOR_STATE_BRAKE,
    MOTOR_STATE_DRIVE,
    MOTOR_STATE_REGEN
} MotorState_t;

void MotorDriver_Init(void);

void MotorDriver_SetState(MotorState_t state);

/* Duty [-1.0 ～ +1.0]
 * + : Forward
 * - : Reverse
 */
void MotorDriver_SetDuty(float duty);

MotorState_t MotorDriver_GetState(void);

float MotorDriver_GetDuty(void);

#endif /* INC_ACTUATOR_MOTOR_MOTOR_DRIVER_H_ */
