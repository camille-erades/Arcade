/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-arcade-camille.erades
** File description:
** lib
*/

#include "../include/LibNcurses.hpp"

Arcade::IGraphic *ret = nullptr;

__attribute__((constructor))
void create()
{
    ret = new Arcade::LibNcurses;
}

__attribute__((destructor))
void destroy()
{
    delete ret;
}

extern "C" Arcade::IGraphic *createGraphic()
{
    return ret;
}