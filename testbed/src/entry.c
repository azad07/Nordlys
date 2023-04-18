/**
 * @file entry.c
 * @author Ashish Azad (ashish.azad07@gmail.com)
 * @brief
 * @version 1.0
 * @date 2023-04-18
 *
 * @copyright Nordlys Game Engine is Copyright (c) Ashish Azad 2023.
 *
 */

#include "game.h"

#include <entry.h>

#include "core/nmemory.h"

/* Define the function to create the game. */
b8 create_game(game *out_game)
{
    /* Application configuration. */
    out_game->app_config.start_pos_x = 100;
    out_game->app_config.start_pos_y = 100;
    out_game->app_config.start_width = 1280;
    out_game->app_config.start_height = 720;
    out_game->app_config.name = "Nordlys Game Engine Testbed";
    out_game->initialize = game_initialize;
    out_game->update = game_update;
    out_game->render = game_render;
    out_game->on_resize = game_on_resize;

    /* Create the game state. */
    out_game->state = nallocate(sizeof(game_state), MEMORY_TAG_GAME);

    return TRUE;
}