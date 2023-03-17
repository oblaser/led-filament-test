/*
author          Oliver Blaser
date            17.03.2023
copyright       GNU GPLv3 - Copyright (c) 2023 Oliver Blaser
*/

#include <stddef.h>
#include <stdint.h>

#include "bcmled.h"

#include "gpio.h"


#define GPIO_LED_R GPIO_LED_4
#define GPIO_LED_G GPIO_LED_3
#define GPIO_LED_B GPIO_LED_1
#define GPIO_LED_W GPIO_LED_2

#define GAMMA_CORRECTED(x) (gamma_1(x)) // 8bit in / 10bit out


// L = B^(gamma) | gamma = 1.5..3
static uint16_t gamma_1(uint8_t b); // no gamma correction, linear
static uint16_t gamma_2_2(uint8_t b);


static const int bcm_bit_times[10] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512 };
static uint16_t value_r, value_g, value_b, value_w;


void BCMLED_init()
{
    BCMLED_setRGBW(0, 0, 0, 0);
    HAL_GPIO_WritePin(GPIO_LED_R, 0);
    HAL_GPIO_WritePin(GPIO_LED_G, 0);
    HAL_GPIO_WritePin(GPIO_LED_B, 0);
    HAL_GPIO_WritePin(GPIO_LED_W, 0);
}

void BCMLED_task()
{
    static int pos = 0;
    static int cnt = 0;

    if (cnt == 0)
    {
        HAL_GPIO_WritePin(GPIO_LED_R, (value_r & (1 << pos)));
        HAL_GPIO_WritePin(GPIO_LED_G, (value_g & (1 << pos)));
        HAL_GPIO_WritePin(GPIO_LED_B, (value_b & (1 << pos)));
        HAL_GPIO_WritePin(GPIO_LED_W, (value_w & (1 << pos)));

        //cnt = UTIL_pow(2, pos);
        cnt = bcm_bit_times[pos];
        if (pos < 7) ++pos;
        else pos = 0;
    }

    --cnt;
}

void BCMLED_setRGBW(uint8_t r, uint8_t g, uint8_t b, uint8_t w)
{
    value_r = GAMMA_CORRECTED(r);
    value_g = GAMMA_CORRECTED(g);
    value_b = GAMMA_CORRECTED(b);
    value_w = GAMMA_CORRECTED(w);
}

void BCMLED_setRGB(uint8_t r, uint8_t g, uint8_t b)
{
    value_r = GAMMA_CORRECTED(r);
    value_g = GAMMA_CORRECTED(g);
    value_b = GAMMA_CORRECTED(b);
}

void BCMLED_setRGBhex(uint32_t rgb)
{
    value_r = GAMMA_CORRECTED((rgb >> 16) & 0x0FF);
    value_g = GAMMA_CORRECTED((rgb >> 8) & 0x0FF);
    value_b = GAMMA_CORRECTED(rgb & 0x0FF);
}

void BCMLED_setR(uint8_t value) { value_r = GAMMA_CORRECTED(value); }
void BCMLED_setG(uint8_t value) { value_g = GAMMA_CORRECTED(value); }
void BCMLED_setB(uint8_t value) { value_b = GAMMA_CORRECTED(value); }
void BCMLED_setW(uint8_t value) { value_w = GAMMA_CORRECTED(value); }


// gamma = 1
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

// gamma = 2.2
uint16_t gamma_2_2(uint8_t b)
{
    return lookUpTable_2_2[b];
}
