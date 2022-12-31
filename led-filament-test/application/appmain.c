/*
author          Oliver Blaser
date            31.12.2022
copyright       GNU GPLv3 - Copyright (c) 2022 Oliver Blaser
*/

#include <stddef.h>
#include <stdint.h>

#include "appmain.h"
#include "middleware/pwmled.h"

enum STATE
{
    S_init = 0,
    S_crash,
    S_idle
};

static int state = S_init;
static uint32_t tmr_led = 0;

void APP_task()
{
    switch (state)
    {
    case S_init:
        state = S_idle;
        break;

    case S_idle:
        break;

    case S_crash:
        if (tmr_led == 11)
        {
            --tmr_led;
            PWMLED_setRGBhex(0);
        }
        if (tmr_led == 0)
        {
            tmr_led = 21;
            PWMLED_setRGBhex(0x00FF0000);
        }
        break;

    default:
        state = S_crash;
        break;
    }
}

void APP_timehandler_10ms()
{
    if (tmr_led) --tmr_led;
}
