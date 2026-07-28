/*
 * driver.h
 *
 *  Created on: Jul 28, 2026
 *      Author: miyab
 */

#ifndef INC_ACTUATOR_MOTOR_DRIVER_H_
#define INC_ACTUATOR_MOTOR_DRIVER_H_

typedef enum
{
    MOTOR_MODE_FREE = 0,
    MOTOR_MODE_FORWARD,
    MOTOR_MODE_REVERSE,
    MOTOR_MODE_BRAKE,
    MOTOR_MODE_REGEN,     // 将来実装
} MotorMode_t;

#endif /* INC_ACTUATOR_MOTOR_DRIVER_H_ */
