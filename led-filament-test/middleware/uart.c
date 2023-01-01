/*
author          Oliver Blaser
date            31.12.2022
copyright       GNU GPLv3 - Copyright (c) 2022 Oliver Blaser
*/

#include <stddef.h>
#include <stdint.h>

#include "middleware/uart.h"
#include "middleware/util.h"

#include "../Core/Inc/usart.h"
#include "stm32f0xx_hal.h"
#include "stm32f0xx_it.h"


static UART_HandleTypeDef* const huart = &huart1;
static uint8_t rxBuffer[UART_RXBUFFERSIZE];
static int rxComplete;


void UART_init()
{
    for (size_t i = 0; i < UART_RXBUFFERSIZE; ++i)
        rxBuffer[i] = 0;

    rxComplete = 0;

    HAL_UART_Receive_IT(huart, rxBuffer, UART_RXBUFFERSIZE);
}

void UART_write(const uint8_t* data, size_t count)
{
    HAL_UART_Transmit(huart, (uint8_t*) data, count, 20);
}

void UART_print(const char* str)
{
    UART_write((const uint8_t*) str, UTIL_strnlen(str, SIZE_MAX));
}

int UART_rxReady()
{
    return rxComplete;
}

void UART_rxDataRead()
{
    rxComplete = 0;
    huart->pRxBuffPtr = rxBuffer;
    huart->RxXferCount = 0;
}

const uint8_t* UART_rxBuffer()
{
    return rxBuffer;
}

const char* UART_rxBufferStr()
{
    return (const char*)rxBuffer;
}

void USART1_IRQHandler()
{
    HAL_UART_IRQHandler(huart);

    if (*(huart->pRxBuffPtr - 1) == '\n') rxComplete = 1;
}
