/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-arcade-camille.erades
** File description:
** main
*/

#include "Core.hpp"

int main(int argc, char **argv)
{
    Arcade::Core coreGame;
    if (argc != 2)
        return 84;

    try {
        coreGame.loadGraphicLib(argv[1]);
        coreGame.select_game_and_graphical();
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        return 84;
    }
    return 0;
}
