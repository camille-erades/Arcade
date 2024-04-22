/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-arcade-camille.erades
** File description:
** Nibbler
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_

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
    class Nibbler : public IGame {
        public:
            Nibbler();
            ~Nibbler();
            void updateMatrix(Keys &) override;
            std::size_t getScore() const override;
            std::string getName() const override;
            Matrix<Entities> getMatrix() const override;
            bool isOver() override;

        protected:
        private:
            Matrix<Entities> data;
            std::size_t score = 0;
            Direction _direction = right;
            std::vector<std::pair<size_t, size_t>> _Nibbler;
            std::pair<int, int> getDirection(const Keys &);
            bool _isOver = false;
            Direction keyToDirection(const Keys &);
            void slide();
    };
};
#endif /* !NIBBLER_HPP_ */
