/**
 * @file nstring.h
 * @author Ashish Azad (ashish.azad07@gmail.com)
 * @brief
 * @version 1.0
 * @date 2023-08-30
 *
 * @copyright Nordlys Game Engine is Copyright (c) Ashish Azad 2023.
 *
 */

#pragma once

#include "defines.h"

/**
 * @brief Calculate the length of the string.
 * 
 * @param str array of char.
 * @return length of string. 
 */
NAPI u64 string_length(const char* str);

/**
 * @brief Create a copy of the string.
 * 
 * @param str input string.
 * @return str returns char array.
 */
NAPI char *string_duplicate(const char *str);

/**
 * @brief Compare str1 with str2, returns true if equal, otherwise false.
 * 
 * @param str1 pointer to string.
 * @param str2 pointer to string.
 * @return b8 true is equal, otherwise false.
 */
NAPI b8 strings_equal(const char* str1, const char* str2);