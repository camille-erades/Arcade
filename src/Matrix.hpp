/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-arcade-camille.erades
** File description:
** Matrix
*/

#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#include <exception>
#include <iostream>
#include <algorithm>
#include "vector"
// #include "Entities.hpp"

namespace Arcade {
    enum Entities {
        nothing, player, enemy, food, powerUp, wall, door
    };
    template<typename T>
    class Matrix {
        public:
            explicit Matrix(const T& value, size_t row, size_t col) : _defaultValue(value), _rows(row), _cols(col), data(row, std::vector<T>(col))
            {
                for (auto& row : data) {
                    for (auto& col : row) {
                        col = value;
                    }
                }
            }

            void resizeAndFill(size_t newRows, size_t newCols)
            {
                _rows = newRows;
                _cols = newCols;
                data.assign(newRows, std::vector<T>(newCols, _defaultValue));
            }

            void fill(const T &value)
            {
                for (auto &row : data) {
                    std::fill(row.begin(), row.end(), value);
                }
            }

            std::size_t getMaxRow() const { return _rows; }
            std::size_t getMaxCol() const { return _cols; }

            std::vector<T>& operator[](std::size_t index) { return data[index]; }
            const std::vector<T>& operator[](std::size_t index) const { return data[index]; }

        protected:
        private:
            T _defaultValue;
            std::size_t _rows;
            std::size_t _cols;
            std::vector<std::vector<T>> data;
    };
};
#endif /* !MATRIX_HPP_ */
