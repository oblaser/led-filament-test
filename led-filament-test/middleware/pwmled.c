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

#define GAMMA_CORRECTED(x) (gamma_2_2(x))


// L = B^(gamma) | gamma = 1.5..3
static uint16_t gamma_1(uint8_t b); // no gamma correction, linear
static uint16_t gamma_2_2(uint8_t b);


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

uint16_t lookUpTable_2_2[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2,
    2, 3, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 9, 9, 10, 11, 11, 12, 13, 14, 15,
    16, 16, 17, 18, 19, 20, 21, 23, 24, 25, 26, 27, 28, 30, 31, 32, 34, 35,
    36, 38, 39, 41, 42, 44, 46, 47, 49, 51, 52, 54, 56, 58, 60, 61, 63, 65,
    67, 69, 71, 73, 76, 78, 80, 82, 84, 87, 89, 91, 94, 96, 98, 101, 103,
    106, 109, 111, 114, 117, 119, 122, 125, 128, 130, 133, 136, 139, 142,
    145, 148, 151, 155, 158, 161, 164, 167, 171, 174, 177, 181, 184, 188,
    191, 195, 198, 202, 206, 209, 213, 217, 221, 225, 228, 232, 236, 240,
    244, 248, 252, 257, 261, 265, 269, 274, 278, 282, 287, 291, 295, 300,
    304, 309, 314, 318, 323, 328, 333, 337, 342, 347, 352, 357, 362, 367,
    372, 377, 382, 387, 393, 398, 403, 408, 414, 419, 425, 430, 436, 441,
    447, 452, 458, 464, 470, 475, 481, 487, 493, 499, 505, 511, 517, 523,
    529, 535, 542, 548, 554, 561, 567, 573, 580, 586, 593, 599, 606, 613,
    619, 626, 633, 640, 647, 653, 660, 667, 674, 681, 689, 696, 703, 710,
    717, 725, 732, 739, 747, 754, 762, 769, 777, 784, 792, 800, 807, 815,
    823, 831, 839, 847, 855, 863, 871, 879, 887, 895, 903, 912, 920, 928,
    937, 945, 954, 962, 971, 979, 988, 997, 1005, 1014, 1023
};

uint16_t gamma_2_2(uint8_t b)
{
    return lookUpTable_2_2[b];
}
