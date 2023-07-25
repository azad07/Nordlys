/**
 * @file application.h
 * @author Ashish Azad (ashish.azad07@gmail.com)
 * @brief
 * @version 1.0
 * @date 2023-04-18
 *
 * @copyright Nordlys Game Engine is Copyright (c) Ashish Azad 2023.
 *
 */

#pragma once

#include "defines.h"

/* forward declaration. */
struct game;

/**
 * @brief struct for application configuration.
 *
 */
typedef struct application_config
{
/**
 * @brief window starting position x axis, if applicable.
 *
 */
    i16 start_pos_x;

    /**
     * @brief window starting position y axis, if applicable.
     *
     */
    i16 start_pos_y;

    /**
     * @brief window starting width, if applicable.
     *
     */
    i16 start_width;

    /**
     * @brief window starting height, if applicable.
     *
     */
    i16 start_height;

    /**
     * @brief The application name used in windowing, if applicable.
     *
     */
    char* name;
} application_config;

/**
 * @brief Creates a new application.
 *
 * @param game_instance The game instance.
 * @return true if the application was successfully created, otherwise false.
 */
NAPI b8 application_create(struct game* game_instance);

/**
 * @brief starts the application.
 *
 * @return true if the application was successfully started, otherwise false.
 */
NAPI b8 application_run();