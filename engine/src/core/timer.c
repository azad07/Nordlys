/**
 * @file timer.c
 * @author Ashish Azad (ashish.azad07@gmail.com)
 * @brief
 * @version 1.0
 * @date 2023-07-25
 *
 * @copyright Nordlys Game Engine is Copyright (c) Ashish Azad 2023.
 *
 */

#include "timer.h"

#include "core/asserts.h"
#include "platform/platform.h"

void timer_start(timer* timer)
{
    NASSERT(timer);

    timer->start_time = platform_get_absolute_time();
    timer->elapsed = 0;
}

void timer_stop(timer* timer)
{
    NASSERT(timer);
    timer->start_time = 0;
}

void timer_update(timer* timer)
{
    NASSERT(timer);

    if (timer == NULL)
        return;
    if (timer->start_time != 0)
    {
        timer->elapsed = platform_get_absolute_time() - timer->start_time;
    }
}

