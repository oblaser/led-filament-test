/*
author          Oliver Blaser
date            31.12.2022
copyright       GNU GPLv3 - Copyright (c) 2022 Oliver Blaser
*/

#include <stddef.h>
#include <stdint.h>

#include "appmain.h"
#include "middleware/pwmled.h"
#include "middleware/uart.h"
#include "middleware/util.h"
#include "project.h"


enum STATE
{
    S_init = 0,
    S_crash,
    S_idle,

    S_bounce
};

static int state = S_init;
static uint32_t tmr_led = 0;


static void bounce();


void APP_task()
{
    if (UART_rxReady())
    {
#if defined(PRJ_DEBUG) && 1
        const uint8_t* const data = UART_rxBuffer();
        const size_t len = UTIL_strnfind(data, '\n', UART_RXBUFFERSIZE);

        if (len < UART_RXBUFFERSIZE) UART_write(data, len + 1);
        else UART_print("echo bot failed!\n");
#else
                // nop, flush
#endif

        UART_rxDataRead();
    }

    switch (state)
    {
    case S_init:
        state = S_idle;

#ifdef PRJ_DBG_UART_EN
        UART_print("\n");
        UART_print("  --====# started #====--\n");
        UART_print("     LED filament test   \n");
#endif

#ifndef PRJ_DEBUG
        if(UTIL_strlen(PRJ_VERSION_PRERELEASE_STR))
        {
            UART_print("\n");
            UART_print("#####################################\n");
            UART_print("#####                           #####\n");
            UART_print("#####  Pre-Release as release!  #####\n");
            UART_print("#####                           #####\n");
            UART_print("#####################################\n");
            UART_print("\n");

            state = S_crash;
        }
#endif
        break;

    case S_idle:
        state = S_bounce;
        break;

    case S_bounce:
        bounce();
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

void bounce()
{
    static int state = (-1);
    static bool_t dir = 0;
    static uint8_t value = 0;
    const uint8_t step = 5;

    if (tmr_led == 0)
    {
        tmr_led = 2;

        if (dir)
        {
            if (value < 0xFF) value += step;
            else
            {
                dir = !dir;
                value -= step; // skip decrement => 2 cycles 0xFF
            }
        }
        else
        {
            if (value > 0) value -= step;
            else
            {
                dir = !dir;
                ++state;
                value += step; // skip increment => 2 cycles 0
            }
        }

        if (state >= 7) state = 0;

        if (state == 0) PWMLED_setRGBW(value, 0, 0, 0);
        else if (state == 1) PWMLED_setRGBW(0, value, 0, 0);
        else if (state == 2) PWMLED_setRGBW(0, 0, value, 0);
        else if (state == 3) PWMLED_setRGBW(0, 0, 0, value);
        else if (state == 4) PWMLED_setRGBW(value, value, 0, 0);
        else if (state == 5) PWMLED_setRGBW(0, value, value, 0);
        else if (state == 6) PWMLED_setRGBW(value, 0, value, 0);
    }
}
