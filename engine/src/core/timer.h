/**
 * @file timer.h
 * @author Ashish Azad (ashish.azad07@gmail.com)
 * @brief
 * @version 1.0
 * @date 2023-07-25
 *
 * @copyright Nordlys Game Engine is Copyright (c) Ashish Azad 2023.
 *
 */

#pragma once

#include "defines.h"

typedef struct timer
{
    /** @brief start timer. (in milliseconds) */
    f64 start_time;

    /** @brief time elapsed from start. (in milliseconds) */
    f64 elapsed;
}timer;

/**
 * @brief Starts the timer. Reset elapsed time.
 *
 * @param timer Pointer to timer.
 */
void timer_start(timer* timer);

/**
 * @brief Stops the timer. Does not reset the elapsed time.
 *
 * @param timer Pointer to timer.
 */
void timer_stop(timer* timer);

/**
 * @brief Updated the provided timer. Should be called just before checking elapsed time.
 *        Has no effect on non-started clock.
 *
 * @param timer Pointer to timer.
 */
void timer_update(timer* timer);