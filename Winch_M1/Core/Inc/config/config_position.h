/*
 * config_position.h
 *
 *  Created on: Aug 29, 2026
 *      Author: miyab
 */

#ifndef CONFIG_POSITION_H_
#define CONFIG_POSITION_H_

/* Position Controller Gain */

#define POSITION_CTRL_KP              (5.0f)


/* Target Position Limit [rad] */

#define POSITION_CTRL_TARGET_MAX      (1000.0f)


/* Output Speed Limit [rad/s] */

#define POSITION_CTRL_OUTPUT_MAX      (100.0f)


#endif /* CONFIG_POSITION_H_ */
