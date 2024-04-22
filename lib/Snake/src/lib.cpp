/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-arcade-camille.erades
** File description:
** lib
*/

#include "Snake.hpp"

Arcade::IGame *ret = nullptr;

__attribute__((constructor))
void create()
{
    ret = new Arcade::Snake;
}

__attribute__((destructor))
void destroy()
{
    delete ret;
}

extern "C" Arcade::IGame *createGame()
{
    return ret;
}