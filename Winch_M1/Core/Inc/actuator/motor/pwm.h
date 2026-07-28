/*
 * pwm.h
 *
 *  Created on: Jul 28, 2026
 *      Author: miyab
 */

#ifndef INC_ACTUATOR_MOTOR_PWM_H_
#define INC_ACTUATOR_MOTOR_PWM_H_

#include <stdint.h>

void MotorPWM_Init(void);

void MotorPWM_Enable(void);
void MotorPWM_Disable(void);

/**
 * @brief ハーフブリッジ1 Duty設定
 *
 * duty : 0～1000
 */
void MotorPWM_SetDutyHB1(uint16_t duty);

/**
 * @brief ハーフブリッジ2 Duty設定
 *
 * duty : 0～1000
 */
void MotorPWM_SetDutyHB2(uint16_t duty);


#endif /* INC_ACTUATOR_MOTOR_PWM_H_ */
