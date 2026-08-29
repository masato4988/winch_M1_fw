/*
 * ir2302_bridge.h
 *
 *  Created on: Jul 28, 2026
 *      Author: miyab
 */

#ifndef INC_ACTUATOR_MOTOR_IR2302_BRIDGE_H_
#define INC_ACTUATOR_MOTOR_IR2302_BRIDGE_H_

void IR2302bridge_Init(void);

void IR2302bridge_Enable(void);
void IR2302bridge_Disable(void);

/**
 * @brief ハーフブリッジ1 Duty設定
 *
 * duty : 0.0 ～ 1.0
 */
void IR2302Bridge_SetHB1Duty(float duty);

/**
 * @brief ハーフブリッジ2 Duty設定
 *
 * duty : 0.0 ～ 1.0
 */
void IR2302Bridge_SetHB2Duty(float duty);


#endif /* INC_ACTUATOR_MOTOR_IR2302_BRIDGE_H_ */
