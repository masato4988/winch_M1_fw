/*
 * RGBLED.h
 *
 *  Created on: Jul 26, 2026
 *      Author: miyab
 */



#ifndef INC_ACTUATOR_RGBLED_H_
#define INC_ACTUATOR_RGBLED_H_


#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief プリセットカラー
 */
typedef enum
{
    RGBLED_COLOR_OFF = 0,
    RGBLED_COLOR_RED,
    RGBLED_COLOR_GREEN,
    RGBLED_COLOR_BLUE,
    RGBLED_COLOR_YELLOW,
    RGBLED_COLOR_CYAN,
    RGBLED_COLOR_MAGENTA,
    RGBLED_COLOR_WHITE

} RGBLED_Color_t;

/**
 * @brief RGB LEDを初期化する
 */
void RGBLED_Init(void);

/**
 * @brief RGB値を指定してLEDを点灯
 *
 * @param r 赤 (0～255)
 * @param g 緑 (0～255)
 * @param b 青 (0～255)
 */
void RGBLED_SetRGB(uint8_t r, uint8_t g, uint8_t b);

/**
 * @brief プリセットカラーを表示
 *
 * @param color 色
 */
void RGBLED_SetColor(RGBLED_Color_t color);

#ifdef __cplusplus
}
#endif


#endif /* INC_ACTUATOR_RGBLED_H_ */
