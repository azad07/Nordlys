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

int main()
{
    NFATAL("A test message: %f", 3.14f);
    NERROR("A test message: %f", 3.14f);
    NWARN("A test message: %f", 3.14f);
    NINFO("A test message: %f", 3.14f);
    NDEBUG("A test message: %f", 3.14f);
    NTRACE("A test message: %f", 3.14f);

    NASSERT(1 == 0);

    return 0;
}