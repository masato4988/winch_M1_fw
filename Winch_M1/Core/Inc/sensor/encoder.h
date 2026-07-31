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
void Encoder_Update(void);

int32_t Encoder_GetCount(void);
void Encoder_SetCount(int32_t count);
void Encoder_Reset(void);

float Encoder_GetPosition(void);
float Encoder_GetSpeed(void);
float Encoder_GetAcceleration(void);



#endif /* INC_SENSOR_ENCODER_H_ */
