/*
 * encoder.h
 *
 *  Created on: Aug 1, 2026
 *      Author: miyab
 */

#ifndef INC_SENSOR_ENCODER_H_
#define INC_SENSOR_ENCODER_H_


#include <stdint.h>

void Encoder_Init(void);
void Encoder_Reset(void);

void Encoder_ResetPosition(float position);

void Encoder_Update(float dt);


int32_t Encoder_GetRawCount(void);
float Encoder_GetPosition(void);
float Encoder_GetSpeed(void);
float Encoder_GetAcceleration(void);




#endif /* INC_SENSOR_ENCODER_H_ */
