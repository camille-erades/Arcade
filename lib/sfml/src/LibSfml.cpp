/*
** EPITECH PROJECT, 2024
** sem1
** File description:
** LibSfml
*/

#include "../include/LibSfml.hpp"
#include <boost/lexical_cast.hpp>

namespace Arcade {
    LibSfml::LibSfml()
    {
        player.setFillColor(sf::Color::Green);
        player.setRadius(10.0);
        player.setOrigin(sf::Vector2f(0.f, 20.f));
        ennemy.setFillColor(sf::Color::Yellow);
        ennemy.setRadius(10.0);
        ennemy.setOrigin(sf::Vector2f(0.f, 20.f));
        food.setFillColor(sf::Color::Red);
        food.setSize(sf::Vector2f(20.f, 20.f));
        food.setOrigin(sf::Vector2f(0.f, 20.f));
        powerup.setFillColor(sf::Color::Cyan);
        powerup.setSize(sf::Vector2f(20.f, 20.f));
        powerup.setOrigin(sf::Vector2f(0.f, 20.f));
        wall.setFillColor(sf::Color::White);
        wall.setSize(sf::Vector2f(20.f, 20.f));
        wall.setOrigin(sf::Vector2f(0.f, 20.f));
        door.setFillColor(sf::Color::Magenta);
        door.setSize(sf::Vector2f(20.f, 20.f));
        door.setOrigin(sf::Vector2f(0.f, 20.f));
        nothing.setFillColor(sf::Color::Black);
        nothing.setSize(sf::Vector2f(20.f, 20.f));
        nothing.setOrigin(sf::Vector2f(0.f, 20.f));
        window.create(sf::VideoMode(1920, 1080), "Snake");
        menuFont.loadFromFile("lib/sfml/arial.ttf");
        menu.setFont(this->menuFont);
        menu.setFillColor(sf::Color::White);
        goverFont.loadFromFile("lib/sfml/arial.ttf");
        gover.setFont(this->menuFont);
        gover.setFillColor(sf::Color::White);
    }

    LibSfml::~LibSfml()
    {
    }

    Keys LibSfml::getEvents()
    {
        sf::Event event;
        while (this->window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == 73)
                    return Keys::UP;
                if (event.key.code == 74)
                    return Keys::DOWN;
                if (event.key.code == 71)
                    return Keys::LEFT;
                if (event.key.code == 72)
                    return Keys::RIGHT;
                if (event.key.code == 58)
                    return Keys::ENTER;
                if (event.key.code >= 0 && event.key.code <= 25)
                    return static_cast<Keys>(event.key.code + 1);
            } else
                return Keys::NONE;
        }
        return Keys::NONE;
    }

    std::string LibSfml::getName() const
    {
        return "SFML";
    }

    void LibSfml::drawFood(int i, int j)
    {
        this->food.setPosition(i, j);
        this->window.draw(this->food);
    }
    
    void LibSfml::drawPlayer(int i, int j)
    {
        this->player.setPosition(i, j);
        this->window.draw(this->player);
    }
    
    void LibSfml::drawNothing(int i, int j)
    {
        this->nothing.setPosition(i, j);
        this->window.draw(this->nothing);
    }

    void LibSfml::drawWall(int i, int j)
    {
        this->wall.setPosition(i, j);
        this->window.draw(this->wall);
    }

    void LibSfml::drawDoor(int i, int j)
    {
        this->door.setPosition(i, j);
        this->window.draw(this->door);
    }

    void LibSfml::drawPup(int i, int j)
    {
        this->powerup.setPosition(i, j);
        this->window.draw(this->powerup);
    }

    void LibSfml::drawEnnemy(int i, int j)
    {
        this->ennemy.setPosition(i, j);
        this->window.draw(this->ennemy);
    }
    
    void LibSfml::draw(const Matrix<Entities> &mat, int score)
    {
        this->window.clear(sf::Color::Black);
        int col = (this->window.getSize().x - (mat.getMaxCol() * 20)) / 2;
        int row = (this->window.getSize().y - (mat.getMaxRow() * 20)) / 2;
        std::string scoreStr = "Score: " + boost::lexical_cast<std::string>(score);
        for (std::size_t i = 0; i < mat.getMaxCol(); i++)
            for (std::size_t j = 0; j < mat.getMaxRow(); j++) {
                if (mat[j][i] == Entities::nothing)
                    drawNothing(col + i * 20,row + j * 20);
                if (mat[j][i] == Entities::wall)
                    drawWall(col + i * 20,row + j * 20);
                if (mat[j][i] == Entities::door)
                    drawDoor(col + i * 20,row + j * 20);
                if (mat[j][i] == Entities::food)
                    drawFood(col + i * 20,row + j * 20);
                if (mat[j][i] == Entities::powerUp)
                    drawPup(col + i * 20,row + j * 20);
                if (mat[j][i] == Entities::enemy)
                    drawEnnemy(col + i * 20,row + j * 20);
                if (mat[j][i] == Entities::player)
                    drawPlayer(col + i * 20,row + j * 20);
            }
        this->menu.setPosition(col, row - 70);
        this->menu.setString(scoreStr);
        this->window.draw(this->menu);
        this->window.display();
    }

    void LibSfml::displayList(const std::vector<std::string> games_list, size_t selected_game, size_t j)
    {
        for (std::size_t i = 0; i < games_list.size(); i++) {
            this->menu.setPosition(sf::Vector2f(j*1.f, i*30.f));
            this->menu.setString(games_list[i].c_str());
            if (i == selected_game) {
                this->menu.setFillColor(sf::Color::Yellow);
            } else 
                this->menu.setFillColor(sf::Color::White);
            this->window.draw(this->menu);
        }
        this->menu.setPosition(sf::Vector2f(800.f, 1.f));
        this->menu.setFillColor(sf::Color::White);
        this->menu.setString("name:");
        this->window.draw(this->menu);
    }

    void LibSfml::drawMenu(std::vector<std::string> &games_list, std::vector<std::string> &graphics_list, size_t selected_game, size_t selected_graphical, std::vector<std::string> scores_list)
    {
        this->window.clear(sf::Color::Black);
        displayList(games_list, selected_game, 1);
        displayList(graphics_list, selected_graphical, 400);
        displayList(scores_list, 0, 1000);
        this->window.display();
    }

    void LibSfml::drawGover()
    {
        this->window.clear(sf::Color::Black);
        this->gover.setCharacterSize(100);
        this->gover.setString("Game Over!");
        this->gover.setOrigin(sf::Vector2f((this->gover.getScale().x/2), (this->gover.getScale().y/2)));
        this->gover.setPosition(sf::Vector2f((this->window.getSize().x/2.75), (this->window.getSize().y/2.4)));
        this->window.draw(this->gover);
        this->window.display();
    }

    std::string LibSfml::get_player_name()
    {
        sf::Event event;
        std::string input;
        bool isgood = false;
        while (!isgood) {
            while (this->window.pollEvent(event)) {
                if (event.type == sf::Event::KeyPressed) {
                    const sf::Keyboard::Key keycode = event.key.code;
                    if (keycode >= sf::Keyboard::A && keycode <= sf::Keyboard::Z) {
                        char chr = static_cast<char>(keycode - sf::Keyboard::A + 'a');
                        input.push_back(chr);
                    }
                    if (keycode == sf::Keyboard::Enter)
                        isgood = true;
                }
            }
        }
        return input;
    }

    bool LibSfml::isOpen()
    {
        return this->window.isOpen();
    }

    void LibSfml::close()
    {
        window.close();
    }

    void LibSfml::open()
    {
    }
};
