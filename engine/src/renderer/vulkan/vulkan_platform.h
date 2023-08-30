/**
 * @file vulkan_platform.h
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
 * @brief Appends the name of platform specific vulkan extension for this platform to the names_array.
 *
 * @param names_darray Array should be created and passed in.
 */
void platform_get_required_extension_names(const char*** names_darray);