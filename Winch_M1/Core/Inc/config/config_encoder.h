/*
 * config_encoder.h
 *
 *  Created on: Aug 1, 2026
 *      Author: miyab
 */

#ifndef INC_CONFIG_CONFIG_ENCODER_H_
#define INC_CONFIG_CONFIG_ENCODER_H_


#define ENCODER_PPR            (64.0f)

/* 1count当たりの回転角[rad] */
#define ENCODER_RAD_PER_COUNT \
    (2.0f * 3.141592f / ENCODER_PPR)

#define ENCODER_SPEED_FIT_POINTS    10U

#endif /* INC_CONFIG_CONFIG_ENCODER_H_ */
