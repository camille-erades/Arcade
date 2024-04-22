/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-arcade-camille.erades
** File description:
** Menu
*/

#include "Core.hpp"

namespace Arcade {
    std::vector<std::string> Core::create_games_list(const std::vector<std::string>& files)
    {
        for (const std::string& file : files) {
            if (file.find("_centipede.so") != std::string::npos ||
                file.find("_pacman.so") != std::string::npos ||
                file.find("_qix.so") != std::string::npos ||
                file.find("_nibbler.so") != std::string::npos ||
                file.find("_snake.so") != std::string::npos ||
                file.find("_solarfox.so") != std::string::npos) {
                games_list.push_back("./lib/" + file);
            }
        }
        return games_list;
    }

    std::vector<std::string> Core::create_graphics_list(const std::vector<std::string>& files)
    {
        for (const std::string& file : files) {
            if (file.find("_ncurses.so") != std::string::npos ||
                file.find("_sdl2.so") != std::string::npos ||
                file.find("_ndk++.so") != std::string::npos ||
                file.find("_aalib.so") != std::string::npos ||
                file.find("_libcaca.so") != std::string::npos ||
                file.find("_allegro5.so") != std::string::npos ||
                file.find("_xlib.so") != std::string::npos ||
                file.find("_gtk+.so") != std::string::npos ||
                file.find("_sfml.so") != std::string::npos ||
                file.find("_irrlicht.so") != std::string::npos ||
                file.find("_opengl.so") != std::string::npos ||
                file.find("_vulkan.so") != std::string::npos ||
                file.find("_qt5.so") != std::string::npos) {
                graphics_list.push_back("./lib/" + file);
            }
        }
        return graphics_list;
    }

    void Core::launch_game(const std::string& game_library, const std::string& graphic_library)
    {
        loadGraphicLib(graphic_library);
        loadGameLib(game_library);
        run();
    }

    std::vector<std::string> Core::get_files_in_directory(const std::string& directory)
    {
        std::vector<std::string> files;
        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir(directory.c_str())) != nullptr) {
            while ((ent = readdir(dir)) != nullptr) {
                if (std::string(ent->d_name).find(".so") != std::string::npos) {
                    files.push_back(ent->d_name);
                }
            }
            closedir(dir);
        } else {
            std::cerr << "Unable to open directory: " << directory << std::endl;
        }
        return files;
    }

    void Core::set_scores_list(std::string infoname)
    {
        std::ofstream file("scores.txt", std::ios::app);
        file << infoname << ", " << graphic->getName() << ", " << game->getName() << " SCORE: " << game->getScore() << std::endl;
        file.close();
    }

    std::vector<std::string> Core::get_scores_list()
    {
        return scores_list;
    }

    void Core::create_scores_list()
    {
        std::ifstream fileread("scores.txt");
        std::string line;

        scores_list.clear();
        while (std::getline(fileread, line)) {
            scores_list.push_back(line);
        }
        fileread.close();
    }

    void Core::select_game_and_graphical()
    {
        Keys key;
        selected_game = 0;
        selected_graphical = 0;
        bool game_selected = false;
        bool graphical_selected = false;

        create_scores_list();
        while (!game_selected || !graphical_selected) {
            key = graphic->getEvents();
            if (!game_selected) {
                switch(key) {
                    case Keys::UP:
                        if (selected_game > 0)
                            selected_game--;
                        break;
                    case Keys::DOWN:
                        if (selected_game < games_list.size() - 1)
                            selected_game++;
                        break;
                    case Keys::ENTER:
                        game_selected = true;
                        break;
                    default:
                        break;
                }
            } else if (!graphical_selected) {
                switch(key) {
                    case Keys::UP:
                        if (selected_graphical > 0)
                            selected_graphical--;
                        break;
                    case Keys::DOWN:
                        if (selected_graphical < graphics_list.size() - 1)
                            selected_graphical++;
                        break;
                    case Keys::ENTER:
                        graphical_selected = true;
                        break;
                    default:
                        break;
                }
            }
            if (game_selected && graphical_selected) {
                player_name = graphic->get_player_name();
            }
            graphic->drawMenu(games_list, graphics_list, selected_game, selected_graphical, get_scores_list());
        }
        launch_game(games_list[selected_game], graphics_list[selected_graphical]);
    }
}
