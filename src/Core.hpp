/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-arcade-camille.erades
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include "IGame.hpp"
#include "IGraphic.hpp"
#include <string>
#include <dlfcn.h>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <exception>
#include "thread"
#include <chrono>

namespace Arcade {    
    class Core {
        public:
            class Error : public std::exception {
                public:
                    Error(const std::string &erroMessage) : _error(erroMessage) {};
                    const char* what() const noexcept {
                        return _error.c_str();
                    }
                private:
                    std::string _error;
            };
            Core();
            ~Core();
            void run();
            void loadGraphicLib(const std::string &libPath);
            void loadGameLib(const std::string &libPath);
            std::vector<std::string> create_games_list(const std::vector<std::string>& files);
            std::vector<std::string> create_graphics_list(const std::vector<std::string>& files);
            void launch_game(const std::string& game_library, const std::string& graphic_library);
            std::vector<std::string> get_files_in_directory(const std::string& directory);
            void select_game_and_graphical();
            void set_scores_list(std::string infoname);
            std::vector<std::string> get_scores_list();
            void create_scores_list();

        private:
            void *graphicLibHandle;
            void *gameLibHandle;
            bool execCmd(Keys);
            IGraphic *graphic;
            IGame *game;
            void unloadGraphicLib();
            void unloadGameLib();
            std::vector<std::string> games_list;
            std::vector<std::string> graphics_list;
            std::vector<std::string> scores_list;
            size_t selected_game;
            size_t selected_graphical;
            std::string player_name;
            std::vector<std::string> files;
            int score;
    };
};

#endif /* !CORE_HPP_ */
