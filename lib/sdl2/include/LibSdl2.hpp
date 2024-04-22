/*
** EPITECH PROJECT, 2024
** sem1
** File description:
** LibSDL
*/

#ifndef LIBSDL2_HPP_
#define LIBSDL2_HPP_

#include "../../../src/IGraphic.hpp"
#include "../../../src/Keys.hpp"
#include "../../../src/Matrix.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace Arcade {
    class LibSdl2 : public IGraphic {
        public:
            LibSdl2();
            ~LibSdl2();
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
            SDL_Window *window;
            SDL_Renderer *renderer;
            SDL_Color playerColor;
            SDL_Color foodColor;
            SDL_Color wallColor;
            SDL_Color nothingColor;
            SDL_Color doorColor;
            SDL_Color powerUpColor;
            SDL_Color ennemyColor;
            TTF_Font *font;
            SDL_Rect textRect;
            SDL_Texture* texture;
            bool _isOpen;
        private:
            void drawFood(int i, int j);
            void drawPlayer(int i, int j);
            void drawNothing(int i, int j);
            void drawWall(int i, int j);
            void drawDoor(int i, int j);
            void drawPup(int i, int j);
            void drawEnnemy(int i, int j);
            void display_label(const std::string& label, int x);
            void display_list(const std::vector<std::string>& list, size_t selected_index, int x);
            void display_score(const std::vector<std::string>& scores_list, int x);
    };
};
#endif /* !LIBSDL2_HPP_ */
