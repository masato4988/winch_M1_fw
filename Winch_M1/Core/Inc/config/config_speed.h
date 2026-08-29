/*
 * config_speed.h
 *
 *  Created on: Aug 1, 2026
 *      Author: miyab
 */

#ifndef INC_CONFIG_CONFIG_SPEED_H_
#define INC_CONFIG_CONFIG_SPEED_H_


/* PID Gain */
#define SPEED_CTRL_KP                 (0.005f)
#define SPEED_CTRL_KD                 (0.0000f)
#define SPEED_CTRL_KI                 (0.01f)

/* Integral Limit */
#define SPEED_CTRL_INTEGRAL_MAX       (1000.0f)

/* Output Limit */
#define SPEED_CTRL_OUTPUT_MAX         (1.0f)

/* Target Speed Limit */
#define SPEED_CTRL_TARGET_MAX         (3000.0f)

/* Feed Forward */
#define SPEED_CTRL_FF_GAIN            (0.0f)


#endif /* INC_CONFIG_CONFIG_SPEED_H_ */
