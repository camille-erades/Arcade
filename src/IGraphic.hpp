/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-arcade-camille.erades
** File description:
** IGraphic
*/

#ifndef IGRAPHIC_HPP_
#define IGRAPHIC_HPP_

#include "../src/Keys.hpp"
#include "Matrix.hpp"

namespace Arcade {
    class IGraphic {
        public:
            virtual ~IGraphic() = default;
            virtual bool isOpen() = 0;
            virtual Keys getEvents() = 0;
            virtual void draw(const Matrix<Entities> &, int score) = 0;
            virtual std::string getName() const = 0;
            virtual void drawMenu(std::vector<std::string> &, std::vector<std::string> &, size_t, size_t, std::vector<std::string>) = 0;
            virtual void drawGover() = 0;
            virtual std::string get_player_name() = 0;
            virtual void open() = 0;
            virtual void close() = 0;
    };
}

#endif /* !IGRAPHIC_HPP_ */
