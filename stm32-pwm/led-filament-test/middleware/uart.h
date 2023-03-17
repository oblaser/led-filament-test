/*
author          Oliver Blaser
date            31.12.2022
copyright       GNU GPLv3 - Copyright (c) 2022 Oliver Blaser
*/

#ifndef IG_MIDDLEWARE_UART_H
#define IG_MIDDLEWARE_UART_H

#include <stddef.h>
#include <stdint.h>

#define UART_RXBUFFERSIZE (20)

void UART_init();
void UART_write(const uint8_t* data, size_t count);
void UART_print(const char* str);
int UART_rxReady();
void UART_rxDataRead();
const uint8_t* UART_rxBuffer();
const char* UART_rxBufferStr();

#endif // IG_MIDDLEWARE_UART_H
