/*
author          Oliver Blaser
date            31.12.2022
copyright       GNU GPLv3 - Copyright (c) 2022 Oliver Blaser
*/

#include <stddef.h>
#include <stdint.h>

#include "pwmled.h"

#include "tim.h"


#define TIM_CCR_R (TIM3->CCR4)
#define TIM_CCR_G (TIM3->CCR3)
#define TIM_CCR_B (TIM3->CCR1)
#define TIM_CCR_W (TIM3->CCR2)

#define GAMMA_CORRECTED(x) (gamma_1(x))


// L = B^(gamma) | gamma = 1.5..3
static uint16_t gamma_1(uint8_t b); // no gamma correction, linear


void PWMLED_init()
{
    PWMLED_setRGBW(0, 0, 0, 0);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
}

void PWMLED_setRGBW(uint8_t r, uint8_t g, uint8_t b, uint8_t w)
{
    TIM_CCR_R = GAMMA_CORRECTED(r);
    TIM_CCR_G = GAMMA_CORRECTED(g);
    TIM_CCR_B = GAMMA_CORRECTED(b);
    TIM_CCR_W = GAMMA_CORRECTED(w);
}

void PWMLED_setRGB(uint8_t r, uint8_t g, uint8_t b)
{
    TIM_CCR_R = GAMMA_CORRECTED(r);
    TIM_CCR_G = GAMMA_CORRECTED(g);
    TIM_CCR_B = GAMMA_CORRECTED(b);
}

void PWMLED_setRGBhex(uint32_t rgb)
{
    TIM_CCR_R = GAMMA_CORRECTED((rgb >> 16) & 0x0FF);
    TIM_CCR_G = GAMMA_CORRECTED((rgb >> 8) & 0x0FF);
    TIM_CCR_B = GAMMA_CORRECTED(rgb & 0x0FF);
}

void PWMLED_setR(uint8_t value) { TIM_CCR_R = GAMMA_CORRECTED(value); }
void PWMLED_setG(uint8_t value) { TIM_CCR_G = GAMMA_CORRECTED(value); }
void PWMLED_setB(uint8_t value) { TIM_CCR_B = GAMMA_CORRECTED(value); }
void PWMLED_setW(uint8_t value) { TIM_CCR_W = GAMMA_CORRECTED(value); }


uint16_t gamma_1(uint8_t b)
{
    uint16_t l = b;
    l <<= 2;
    if (b == 0xFF) l |= 0x03;
    return l;
}
