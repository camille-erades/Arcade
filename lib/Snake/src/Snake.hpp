/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-arcade-camille.erades
** File description:
** Snake
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#include "../../../src/IGame.hpp"
#include <cstdlib>
#include <ctime>
#include "utility"
#include "vector"
#include "thread"
#include <chrono>

namespace Arcade {

    enum Direction {
        up = 1,
        down = -1,
        right = 2,
        left = -2
    };
    class Snake : public IGame {
        public:
            Snake();
            ~Snake();
            void updateMatrix(Keys &) override;
            std::size_t getScore() const override;
            std::string getName() const override;
            Matrix<Entities> getMatrix() const override;
            bool isOver() override;

        protected:
        private:
            Matrix<Entities> data;
            std::size_t score;
            Direction _direction = right;
            std::vector<std::pair<size_t, size_t>> _snake;
            std::pair<std::size_t, std::size_t> headPos;
            bool _isOver = false;
            bool randomApple();
            std::pair<int, int> getDirection(const Keys &);
            Direction keyToDirection(const Keys &);
    };
};
#endif /* !SNAKE_HPP_ */
