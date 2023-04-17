/**
@file main.c
 * @author Ashish Azad (ashish.azad07@gmail.com)
 * @brief Main program for the application.
 * @version 1.0
 * @date 2023-04-17
 *
 * @copyright Nordlys Game Engine is Copyright (c) Ashish Azad 2023.
 *
 */

#include <core/asserts.h>
#include <core/logger.h>

#include <platform/platform.h>

const i32 x_pos = 100;
const i32 y_pos = 100;
const i32 window_width = 1280;
const i32 window_height = 720;

int main()
{
    NFATAL("A test message: %f", 3.14f);
    NERROR("A test message: %f", 3.14f);
    NWARN("A test message: %f", 3.14f);
    NINFO("A test message: %f", 3.14f);
    NDEBUG("A test message: %f", 3.14f);
    NTRACE("A test message: %f", 3.14f);

    platform_state state;
    if (platform_initialize(&state, "Nordlys Engine Testbed", x_pos, y_pos,
                            window_width, window_height))
    {
        while (TRUE)
        {
            platform_pump_messages(&state);
        }
    }
    platform_shutdown(&state);

    return 0;
}