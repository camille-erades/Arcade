/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-arcade-camille.erades
** File description:
** Core
*/

#include "Core.hpp"

namespace Arcade {
    Core::Core() : graphicLibHandle(nullptr), gameLibHandle(nullptr), graphic(nullptr), game(nullptr)
    {
        files = get_files_in_directory("./lib");
        create_games_list(files);
        create_graphics_list(files);
    }

    Core::~Core()
    {
        unloadGraphicLib();
        unloadGameLib();
    }

    bool Core::execCmd(Keys key)
    {
        switch(key) {
            case Keys::Q:
                graphic->close();
                break;
            case Keys::R:
                loadGameLib(games_list[selected_game]);
                break;
            case Keys::M:
                set_scores_list(player_name);
                select_game_and_graphical();
                return true;
            case Keys::G:
                selected_game = (selected_game < games_list.size() - 1) ? selected_game + 1 : 0;
                loadGameLib(games_list[selected_game]);
                break;
            case Keys::V:
                selected_graphical = (selected_graphical < graphics_list.size() - 1) ? selected_graphical + 1 : 0;
                loadGraphicLib(graphics_list[selected_graphical]);
                break;
            default:
                game->updateMatrix(key);
                break;
        }
        return false;
    }

    void Core::run()
    {
        Keys key;
        
        if (!graphic || !game)
            return;
        while (graphic->isOpen()) {
            key = graphic->getEvents();
            if (execCmd(key))
                return;
            if (game->isOver())
                graphic->drawGover();
            else {
                auto matrix = game->getMatrix();
                graphic->draw(matrix, game->getScore());
            }
            std::chrono::duration<float> duration(0.1);
            std::this_thread::sleep_for(duration);
        }
        set_scores_list(player_name);
    }

    void Core::loadGraphicLib(const std::string &libPath)
    {
        unloadGraphicLib();
    
        graphicLibHandle = dlopen(libPath.c_str(), RTLD_LAZY);
        if (!graphicLibHandle)
            throw Error("Error loading graphics library: " + std::string(dlerror()));
        auto createFunc = (IGraphic*(*)())dlsym(graphicLibHandle, "createGraphic");
        if (!createFunc)
            throw Error("Failed to find create function: " + std::string(dlerror()));
        graphic = createFunc();
    }

        void Core::loadGameLib(const std::string &libPath)
    {
        unloadGameLib();
    
        gameLibHandle = dlopen(libPath.c_str(), RTLD_LAZY);
        if (!graphicLibHandle)
            throw Error("Error loading games library: " + std::string(dlerror()));
        auto createFunc = (IGame*(*)())dlsym(gameLibHandle, "createGame");
        if (!createFunc)
            throw Error("Failed to find create function: " + std::string(dlerror()));
        game = createFunc();
    }

    void Core::unloadGraphicLib()
    {
        if (graphicLibHandle) {
            dlclose(graphicLibHandle);
            graphic = nullptr;
        }
    }

    void Core::unloadGameLib()
    {
        if (gameLibHandle) {
            dlclose(gameLibHandle);
            game = nullptr;
        }
    }
}
