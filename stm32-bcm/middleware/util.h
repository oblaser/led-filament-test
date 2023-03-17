/*
author          Oliver Blaser
date            31.12.2022
copyright       GNU GPLv3 - Copyright (c) 2022 Oliver Blaser
*/

#ifndef IG_MIDDLEWARE_UTIL_H
#define IG_MIDDLEWARE_UTIL_H

#include <stddef.h>
#include <stdint.h>

#include "types.h"

size_t UTIL_strfind(const char* str, char ch);
size_t UTIL_strnfind(const char* str, char ch, size_t count);
size_t UTIL_strlen(const char* str);
size_t UTIL_strnlen(const char* str, size_t count);
int UTIL_strncmp(const char* lhs, const char* rhs, size_t count);
bool_t UTIL_strneq(const char* lhs, const char* rhs, size_t count);

#endif // IG_MIDDLEWARE_UTIL_H
