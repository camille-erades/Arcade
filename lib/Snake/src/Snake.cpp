/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-arcade-camille.erades
** File description:
** Snake
*/

#include "Snake.hpp"
namespace Arcade {
    Snake::Snake() : data(Matrix<Entities>(Entities::nothing, 30, 30))
    {
        std::size_t maxRow = data.getMaxRow();
        std::size_t maxCol = data.getMaxCol();
        for (std::size_t i = 0; i < maxRow; i++)
            for (std::size_t j = 0; j < maxCol; j++)
                if (i == 0 || j == 0 || i == (maxRow - 1) || j == (maxCol - 1))
                    data[i][j] = Entities::wall;
        _snake.clear();
        score = 0;
        for (std::size_t i = 2; i <= 5; i++) {
            data[maxRow / 2][i] = Entities::player;
            _snake.push_back(std::make_pair(maxRow / 2, i));
        }
        randomApple();
    }

    Snake::~Snake()
    {
    }

    void Snake::updateMatrix(Keys &key)
    {
        std::pair<int, int> coord = getDirection(key);
        std::size_t y = _snake[_snake.size() - 1].first + coord.first;
        std::size_t x = _snake[_snake.size() - 1].second + coord.second;
    
        if (data[y][x] == Entities::player || data[y][x] == Entities::wall)
        {
            _isOver = true;
            return;
        }
        if (data[y][x] == food) {
            randomApple();
            score++;
            _snake.push_back(std::make_pair(y,x));
        } else {
            data[_snake[0].first][_snake[0].second] = Entities::nothing;
            for(std::size_t i = 0; i < _snake.size() -1; i++)
                _snake[i] = _snake[i+1];
            _snake[_snake.size() - 1] = std::make_pair(y,x);
        }
        data[y][x] = player;
    }

    std::size_t Snake::getScore() const
    {
        return score;
    }

    std::string Snake::getName() const
    {
        return "Snake";
    }

    Matrix<Entities> Snake::getMatrix() const
    {
        return data;
    }

    bool Snake::randomApple()
    {
        std::vector<std::pair<size_t, size_t>> nothingList;
        std::size_t row = data.getMaxRow();
        std::size_t col = data.getMaxRow();
        std::size_t index;

        for (std::size_t i = 0; i < row; i++)
            for (std::size_t j = 0; j < col; j++)
                if (data[i][j] == Entities::nothing)
                    nothingList.emplace_back(i, j);
        if (nothingList.empty())
            return false;
        
        index = rand() % nothingList.size();
        data[nothingList[index].first][nothingList[index].second] = Entities::food;
        return true;
    }

    Direction Snake::keyToDirection(const Keys &key)
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

    std::pair<int, int> Snake::getDirection(const Keys &key)
    {
        Direction direction = keyToDirection(key);
        int x = 0;
        int y = 0;
    
        if ((_direction * -1) != direction)
            _direction = direction;
        switch (_direction) {
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
        return std::make_pair(y, x);
    }

    bool Snake::isOver()
    {
        return _isOver;
    }
}
