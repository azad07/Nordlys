/**
 * @file game_types.h
 * @author Ashish Azad (ashish.azad07@gmail.com)
 * @brief
 * @version 1.0
 * @date 2023-04-18
 *
 * @copyright Nordlys Game Engine is Copyright (c) Ashish Azad 2023.
 *
 */

#pragma once

#include "core/application.h"

typedef struct game
{
    /**
     * @brief The application configuration.
     *
     */
    application_config app_config;

    /**
     * @brief Function pointer to game's initialize function.
     *
     */
    b8 (*initialize)(struct game *game_instance);

    /**
     * @brief Function pointer to game's update function.
     *
     */
    b8 (*update)(struct game *game_instance, f32 delta_time);

    /**
     * @brief Function pointer to game's render function.
     *
     */
    b8 (*render)(struct game *game_instance, f32 delta_time);

    /**
     * @brief Function pointer to handle resize, if applicable.
     *
     */
    void (*on_resize)(struct game *game_instance, u32 width, u32 height);

    /**
     * @brief Game-specific game state. Created and managed by the game.
     *
     */
    void *state;
} game;