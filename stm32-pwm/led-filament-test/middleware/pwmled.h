/*
author          Oliver Blaser
date            31.12.2022
copyright       GNU GPLv3 - Copyright (c) 2022 Oliver Blaser
*/

#ifndef IG_MIDDLEWARE_PWMLED_H
#define IG_MIDDLEWARE_PWMLED_H

#include <stddef.h>
#include <stdint.h>


#define PWMLED_ON       (1024)
#define PWMLED_OFF      (0)


void PWMLED_init();

void PWMLED_setRGBW(uint8_t r, uint8_t g, uint8_t b, uint8_t w);
void PWMLED_setRGB(uint8_t r, uint8_t g, uint8_t b);
void PWMLED_setRGBhex(uint32_t rgb);
void PWMLED_setR(uint8_t value);
void PWMLED_setG(uint8_t value);
void PWMLED_setB(uint8_t value);
void PWMLED_setW(uint8_t value);


#endif // IG_MIDDLEWARE_PWMLED_H
