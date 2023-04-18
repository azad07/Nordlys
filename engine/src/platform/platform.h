/**
 * @file platform.h
 * @author Ashish Azad (ashish.azad07@gmail.com)
 * @brief
 * @version 1.0
 * @date 2023-04-17
 *
 * @copyright Nordlys Game Engine is Copyright (c) Ashish Azad 2023.
 *
 */

#pragma once

#include "defines.h"

/**
 * @brief struct for platform specific definitions.
 *
 */
typedef struct platform_state
{
    void *internal_state;
} platform_state;

/**
 * @brief platform specific initialization.
 *
 * @param p_state platform internal state.
 * @param application_name Name of the application/game.
 * @param x_pos x position of the application.
 * @param y_pos y position of the application.
 * @param width width of the application.
 * @param height height of the application.
 * @return true if success, otherwise false.
 */
b8 platform_initialize(platform_state *p_state,
                       const char *application_name,
                       i32 x_pos,
                       i32 y_pos,
                       i32 width,
                       i32 height);

/**
 * @brief Clean up all the states related to platform.
 *
 * @param p_state platform internal state.
 * @return void
 */
void platform_shutdown(platform_state *p_state);

b8 platform_pump_messages(platform_state *p_state);

void *platform_allocate(u64 size, b8 alligned);

void platform_free(void *block, b8 alligned);

void *platform_zero_memory(void *block, u64 size);

void *platform_copy_memory(void *dest, const void *src, u64 size);

void *platform_set_memory(void *dest, i32 value, u64 size);

void platform_console_write(const char *message, u8 color);

void platform_console_write_error(const char *message, u8 color);

/**
 * @brief Gets the platform absolute time in milliseconds.
 *
 * @return f64 absolute time in milliseconds.
 */
f64 platform_get_absolute_time();

/**
 * @brief platform specific sleep.
 *        Sleep on the thrad for the provided amount of time in milliseconds.
This blocks the main thread.
 * @param milliseconds sleep time in milliseconds.
 * @return void
 */
void platform_sleep(u64 milliseconds);