/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-arcade-camille.erades
** File description:
** LibNcurses
*/

#ifndef LIBNCURSES_HPP_
#define LIBNCURSES_HPP_

#include <ncurses.h>
#include "../../../src/IGraphic.hpp"
#include "../../../src/Keys.hpp"
#include "../../../src/Matrix.hpp"
#include <chrono>
#include <thread>

namespace Arcade {
    class LibNcurses : public IGraphic {
        public:
            LibNcurses();
            ~LibNcurses();
            Keys getEvents() override;
            std::string getName() const override;
            void draw(const Matrix<Entities> &, int score) override;
            bool isOpen() override;
            void close() override;
            void open() override;
            void drawMenu(std::vector<std::string> &games_list, std::vector<std::string> &graphics_list, size_t selected_game, size_t selected_graphical, std::vector<std::string> scores_list) override;
            std::string get_player_name() override;
            void drawGover() override;
        protected:
            int player;
            int ennemy;
            int food;
            int powerup;
            int wall;
            int door;
            int nothing;
            WINDOW *window;
        private:
            void drawFood(int i, int j);
            void drawPlayer(int i, int j);
            void drawNothing(int i, int j);
            void drawWall(int i, int j);
            void drawDoor(int i, int j);
            void drawPup(int i, int j);
            void drawEnnemy(int i, int j);
            void display_list(const std::vector<std::string>& list, size_t selected_index);
    };
};

#endif /* !LIBNCURSES_HPP_ */