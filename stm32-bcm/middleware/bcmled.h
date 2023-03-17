/*
author          Oliver Blaser
date            17.03.2023
copyright       GNU GPLv3 - Copyright (c) 2023 Oliver Blaser
*/

#ifndef IG_MIDDLEWARE_BCMLED_H
#define IG_MIDDLEWARE_BCMLED_H

#include <stddef.h>
#include <stdint.h>


#define BCMLED_ON       (1024)
#define BCMLED_OFF      (0)


void BCMLED_init();

void BCMLED_task();

void BCMLED_setRGBW(uint8_t r, uint8_t g, uint8_t b, uint8_t w);
void BCMLED_setRGB(uint8_t r, uint8_t g, uint8_t b);
void BCMLED_setRGBhex(uint32_t rgb);
void BCMLED_setR(uint8_t value);
void BCMLED_setG(uint8_t value);
void BCMLED_setB(uint8_t value);
void BCMLED_setW(uint8_t value);


#endif // IG_MIDDLEWARE_BCMLED_H
