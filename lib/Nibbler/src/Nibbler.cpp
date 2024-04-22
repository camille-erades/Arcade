/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-arcade-camille.erades
** File description:
** Nibbler
*/

#include "Nibbler.hpp"

static const std::vector<std::string> map1 = {
    "5555555555555555555",
    "5003000300030003005",
    "5055505055505055505",
    "5350535000005350535",
    "5055505050505055505",
    "5000005350535000005",
    "5055555050505555505",
    "5350300000000030535",
    "5050555550555550505",
    "5000300000000030005",
    "5055555055505555505",
    "5003000050500003005",
    "5055505055505055505",
    "5050505003005050505",
    "5355535355535355535",
    "5000005050505000005",
    "5355555055505555535",
    "5000000011110000005",
    "5555555555555555555"
};

namespace Arcade {
    Nibbler::Nibbler() : data(Matrix<Entities>(Entities::nothing, map1.size(), map1[0].size()))
    {
        int value; 
        std::size_t maxRow = data.getMaxRow();
        std::size_t maxCol = data.getMaxCol();
        for (std::size_t i = 0; i < maxRow; i++)
            for (std::size_t j = 0; j < maxCol; j++) {
                value = std::stoi(std::string(1, map1[i][j]));
                data[i][j] = static_cast<Entities>(value);
                if (static_cast<Entities>(value) == Entities::player)
                _Nibbler.push_back(std::make_pair(i, j));
            }
    }

    Nibbler::~Nibbler()
    {
    }

    void Nibbler::updateMatrix(Keys &key)
    {
        std::pair<int, int> coord = getDirection(key);
        std::size_t y = _Nibbler[_Nibbler.size() - 1].first + coord.first;
        std::size_t x = _Nibbler[_Nibbler.size() - 1].second + coord.second;
    
        if (data[y][x] == Entities::player) {
            _isOver = true;
            return;
        }
        if (data[y][x] == wall)
            slide();
        else if (data[y][x] == food) {
            score++;
            _Nibbler.push_back(std::make_pair(y,x));
            data[y][x] = player;
        } else {
            data[_Nibbler[0].first][_Nibbler[0].second] = Entities::nothing;
            for(std::size_t i = 0; i < _Nibbler.size() -1; i++)
                _Nibbler[i] = _Nibbler[i+1];
            _Nibbler[_Nibbler.size() - 1] = std::make_pair(y,x);
            data[y][x] = player;
        }
    }

    std::size_t Nibbler::getScore() const
    {
        return score;
    }

    std::string Nibbler::getName() const
    {
        return "Nibbler";
    }

    Matrix<Entities> Nibbler::getMatrix() const
    {
        return data;
    }

    Direction Nibbler::keyToDirection(const Keys &key)
    {
        switch (key) {
            case Keys::UP:
                return Direction::up;
            case Keys::DOWN:
                return Direction::down;
            case Keys::LEFT:
                return Direction::left;
            case Keys::RIGHT:
                return Direction::right;
            default:
                return _direction;
        }
    }

    void Nibbler::slide()
    {
        size_t y = _Nibbler[_Nibbler.size() - 1].first;
        size_t x = _Nibbler[_Nibbler.size() - 1].second;

        if ((_direction * _direction) == 1) {
            if (data[y][x + 1] == wall && data[y][x - 1] != wall && data[y][x - 1] != player)
                _direction = left;
            if (data[y][x - 1] == wall && data[y][x + 1] != wall && data[y][x + 1] != player)
            _direction = right;
        } else {
            if (data[y + 1][x] == wall && data[y - 1][x] != wall && data[y - 1][x] != player)
                _direction = up;
            if (data[y - 1][x] == wall && data[y + 1][x] != wall && data[y + 1][x] != player)
            _direction = down;
        }
    }

    std::pair<int, int> Nibbler::getDirection(const Keys &key)
    {
        Direction direction = keyToDirection(key);
        Direction newDirection = _direction;
        std::pair<size_t, size_t> head = _Nibbler[_Nibbler.size() - 1];
        int x = 0;
        int y = 0;
    
        if ((_direction * -1) != direction)
            newDirection = direction;
        switch (newDirection) {
            case Direction::up:
                y = -1;
                break;
            case Direction::down:
                y = 1;
                break;
            case Direction::left:
                x = -1;
                break;
            case Direction::right:
                x = 1;
                break;
        }
        if (data[head.first + y][head.second + x] != wall)
            _direction = newDirection;
        return std::make_pair(y, x);
    }
    
    bool Nibbler::isOver()
    {
        return _isOver;
    }
}
