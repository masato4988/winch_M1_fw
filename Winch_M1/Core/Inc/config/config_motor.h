/*
 * config_motor.h
 *
 *  Created on: Jul 28, 2026
 *      Author: miyab
 */

#ifndef INC_CONFIG_CONFIG_MOTOR_H_
#define INC_CONFIG_CONFIG_MOTOR_H_

#define MOTOR_PWM_TIMER_CLOCK_HZ    170000000UL
#define MOTOR_PWM_PRESCALER         0U
#define MOTOR_PWM_PERIOD            8499U

#define MOTOR_PWM_FREQ_HZ \
		(MOTOR_PWM_TIMER_CLOCK_HZ / \
		((MOTOR_PWM_PRESCALER + 1U) * (MOTOR_PWM_PERIOD + 1U)))

#define MOTOR_PWM_MAX_DUTY          8000U


#endif /* INC_CONFIG_CONFIG_MOTOR_H_ */
