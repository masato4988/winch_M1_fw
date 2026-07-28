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
    MOTOR_STATE_DISABLE = 0,
    MOTOR_STATE_FREE,
    MOTOR_STATE_BRAKE,
    MOTOR_STATE_DRIVE,
    MOTOR_STATE_REGEN,      // TODO

} MotorState_t;

void MotorDriver_Init(void);

void MotorDriver_SetState(MotorState_t state);

void MotorDriver_SetDuty(int16_t duty);

MotorState_t MotorDriver_GetState(void);

int16_t MotorDriver_GetDuty(void);

#endif /* INC_ACTUATOR_MOTOR_MOTOR_DRIVER_H_ */
