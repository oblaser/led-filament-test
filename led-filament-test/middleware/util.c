/*
author          Oliver Blaser
date            31.12.2022
copyright       GNU GPLv3 - Copyright (c) 2022 Oliver Blaser
*/

#include <stddef.h>
#include <stdint.h>

#include "util.h"


size_t UTIL_strfind(const char* str, char ch) { return UTIL_strnfind(str, ch, SIZE_MAX); }

size_t UTIL_strnfind(const char* str, char ch, size_t count)
{
    size_t len = 0;

    while ((*(str + len) != ch) && (len < count))
    {
        if (*(str + len) == 0) len = SIZE_MAX;
        else ++len;
    }

    return len;
}

size_t UTIL_strlen(const char* str)
{
    return UTIL_strnlen(str, SIZE_MAX);
}

size_t UTIL_strnlen(const char* str, size_t count)
{
    size_t len = 0;

    while ((*(str + len) != 0) && (len < count))
        ++len;

    return len;
}

int UTIL_strncmp(const char* lhs, const char* rhs, size_t count)
{
    int r = 0;

    for (size_t i = 0; i < count; ++i)
    {
        r = (((unsigned char)(*(lhs + i))) - ((unsigned char)(*(rhs + i))));

        if (r != 0) break;
    }

    return r;
}

bool_t UTIL_strneq(const char* lhs, const char* rhs, size_t count)
{
    return (UTIL_strncmp(lhs, rhs, count) == 0);
}
