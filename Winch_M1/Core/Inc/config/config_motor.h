/*
 * config_motor.h
 *
 *  Created on: Jul 28, 2026
 *      Author: miyab
 */

#ifndef INC_CONFIG_CONFIG_MOTOR_H_
#define INC_CONFIG_CONFIG_MOTOR_H_

/* TIM1 clock */
#define MOTOR_PWM_TIMER_CLOCK_HZ    170000000UL

/* Prescaler */
#define MOTOR_PWM_PRESCALER         0U

/* PWM frequency */
#define MOTOR_PWM_FREQ_HZ           20000U

/* ARR */
#define MOTOR_PWM_PERIOD \
    ((MOTOR_PWM_TIMER_CLOCK_HZ / \
     ((MOTOR_PWM_PRESCALER + 1U) * MOTOR_PWM_FREQ_HZ)) - 1U)

/* Compare最大値
 * ブートストラップ維持のため100%にはしない
 */

#define MOTOR_PWM_COMPARE_MARGIN    170U

#define MOTOR_PWM_COMPARE_MAX \
(MOTOR_PWM_PERIOD - MOTOR_PWM_COMPARE_MARGIN)


#endif /* INC_CONFIG_CONFIG_MOTOR_H_ */
