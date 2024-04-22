/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-arcade-camille.erades
** File description:
** IGame
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include "Keys.hpp"
#include "Matrix.hpp"
namespace Arcade {
    class IGame {
        public:
            virtual ~IGame() = default;
            virtual void updateMatrix(Keys &) = 0;
            virtual std::size_t getScore() const = 0;
            virtual std::string getName() const = 0;
            virtual Matrix<Entities> getMatrix() const = 0;
            virtual bool isOver() = 0;

        protected:
        private:
    };
}

#endif /* !IGAME_HPP_ */
