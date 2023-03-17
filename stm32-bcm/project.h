/*
author          Oliver Blaser
date            31.12.2022
copyright       GNU GPLv3 - Copyright (c) 2022 Oliver Blaser
*/

#ifndef IG_PROJECT_H
#define IG_PROJECT_H


#define PRJ_VERSION_MAJOR           (0)
#define PRJ_VERSION_MINOR           (1)
#define PRJ_VERSION_PATCH           (0)
#define PRJ_VERSION_PRERELEASE_STR  (PRJ_version_preRelease_str)
const char* const PRJ_version_preRelease_str = "alpha";


#ifdef DEBUG
#define PRJ_DEBUG (1)
#endif

#ifdef PRJ_DEBUG
#define PRJ_DBG_UART (1)
#endif


#endif // IG_PROJECT_H
