/**
 * @file entry.h
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
#include "core/logger.h"
#include "game_types.h"

/**
 * @brief Externally defined function to create a new game.
 *
 */
extern b8 create_game(game *out_game);

int main(void)
{
    /* Request the game instance from the application. */
    game game_instance;
    if (!create_game(&game_instance))
    {
        NFATAL("Couldn't create game instance.");
        return -1;
    }

    /* Ensure the function pointers exist. */
    if (!game_instance.initialize || !game_instance.render ||
        !game_instance.update || !game_instance.on_resize)
    {
        NFATAL("The game's function pointers must be initialized.");
        return -2;
    }

    /* Initialization. */
    if (!application_create(&game_instance))
    {
        NINFO("Application failed to create from game instance.");
        return 1;
    }

    /* Begin the game loop. */
    if (!application_run())
    {
        NINFO("Application did not shut down gracefully.");
        return 2;
    }

    return 0;
}