/*
** EPITECH PROJECT, 2024
** sem1
** File description:
** LibSfml
*/

#ifndef LIBSFML_HPP_
#define LIBSFML_HPP_

#include "../../../src/IGraphic.hpp"
#include "../../../src/Keys.hpp"
#include "../../../src/Matrix.hpp"
#include <SFML/Graphics.hpp>
#include <unistd.h>

namespace Arcade {
    class LibSfml : public IGraphic {
        public:
            LibSfml();
            ~LibSfml();
            Keys getEvents() override;
            std::string getName() const override;
            void draw(const Matrix<Entities> &, int score) override;
            void drawMenu(std::vector<std::string> &games_list, std::vector<std::string> &graphics_list, size_t selected_game, size_t selected_graphical, std::vector<std::string> scores_list) override;
            void drawGover() override;
            bool isOpen() override;
            void close() override;
            void open() override;
            std::string get_player_name() override;

        private:
            sf::CircleShape player;
            sf::CircleShape ennemy;
            sf::RectangleShape food;
            sf::RectangleShape powerup;
            sf::RectangleShape wall;
            sf::RectangleShape door;
            sf::RectangleShape nothing;
            sf::Font menuFont;
            sf::Font goverFont;
            sf::Text menu;
            sf::Text gover;
            sf::RenderWindow window;

            void displayList(std::vector<std::string> games_list, size_t selected_game, size_t j);
            void drawFood(int i, int j);
            void drawPlayer(int i, int j);
            void drawNothing(int i, int j);
            void drawWall(int i, int j);
            void drawDoor(int i, int j);
            void drawPup(int i, int j);
            void drawEnnemy(int i, int j);
    };
};
#endif /* !LIBSFML_HPP_ */
