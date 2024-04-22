/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-arcade-camille.erades
** File description:
** LibSdl2
*/

#include "../include/LibSdl2.hpp"
#include <boost/lexical_cast.hpp>

namespace Arcade {
    LibSdl2::LibSdl2()
    {
        this->_isOpen = true;
        SDL_Init(SDL_INIT_VIDEO);
        TTF_Init();
        this->window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_SHOWN);
        this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
        this->playerColor = {0, 255, 0, 255};
        this->foodColor = {255, 0, 0, 255};
        this->wallColor = {255, 255, 255, 255};
        this->nothingColor = {0, 0, 0, 255};
        this->doorColor = {255, 0, 255, 255};
        this->powerUpColor = {0, 255, 255, 255};
        this->ennemyColor = {255, 255, 0, 255};
        this->font = TTF_OpenFont("./lib/sdl2/arial.ttf", 24);
    }

    LibSdl2::~LibSdl2()
    {
        SDL_DestroyRenderer(this->renderer);
        SDL_DestroyWindow(this->window);
        SDL_Quit();
    }

    Keys LibSdl2::getEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                this->close();
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_UP)
                    return Keys::UP;
                if (event.key.keysym.sym == SDLK_DOWN)
                    return Keys::DOWN;
                if (event.key.keysym.sym == SDLK_LEFT)
                    return Keys::LEFT;
                if (event.key.keysym.sym == SDLK_RIGHT)
                    return Keys::RIGHT;
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    return Keys::ESC;
                if (event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z)
                    return static_cast<Keys>(event.key.keysym.sym - 96);
                if (event.key.keysym.sym == SDLK_RETURN)
                    return Keys::ENTER;
            }
        }
        return Keys::NONE;
    }

    std::string LibSdl2::getName() const
    {
        return "SDL2";
    }

    void LibSdl2::drawFood(int i, int j)
    {
        SDL_Rect foodRect = {i, j, 20, 20};
        SDL_SetRenderDrawColor(this->renderer, this->foodColor.r, this->foodColor.g, this->foodColor.b, this->foodColor.a);
        SDL_RenderFillRect(this->renderer, &foodRect);
    }

    void LibSdl2::drawPlayer(int i, int j)
    {
        SDL_Rect playerRect = {i, j, 20, 20};
        SDL_SetRenderDrawColor(this->renderer, this->playerColor.r, this->playerColor.g, this->playerColor.b, this->playerColor.a);
        SDL_RenderFillRect(this->renderer, &playerRect);
    }

    void LibSdl2::drawNothing(int i, int j)
    {
        SDL_Rect nothingRect = {i, j, 20, 20};
        SDL_SetRenderDrawColor(this->renderer, this->nothingColor.r, this->nothingColor.g, this->nothingColor.b, this->nothingColor.a);
        SDL_RenderFillRect(this->renderer, &nothingRect);
    }

    void LibSdl2::drawWall(int i, int j)
    {
        SDL_Rect wallRect = {i, j, 20, 20};
        SDL_SetRenderDrawColor(this->renderer, this->wallColor.r, this->wallColor.g, this->wallColor.b, this->wallColor.a);
        SDL_RenderFillRect(this->renderer, &wallRect);
    }

    void LibSdl2::drawDoor(int i, int j)
    {
        SDL_Rect doorRect = {i, j, 20, 20};
        SDL_SetRenderDrawColor(this->renderer, this->doorColor.r, this->doorColor.g, this->doorColor.b, this->doorColor.a);
        SDL_RenderFillRect(this->renderer, &doorRect);
    }

    void LibSdl2::drawPup(int i, int j)
    {
        SDL_Rect powerUpRect = {i, j, 20, 20};
        SDL_SetRenderDrawColor(this->renderer, this->powerUpColor.r, this->powerUpColor.g, this->powerUpColor.b, this->powerUpColor.a);
        SDL_RenderFillRect(this->renderer, &powerUpRect);
    }

    void LibSdl2::drawEnnemy(int i, int j)
    {
        SDL_Rect ennemyRect = {i, j, 20, 20};
        SDL_SetRenderDrawColor(this->renderer, this->ennemyColor.r, this->ennemyColor.g, this->ennemyColor.b, this->ennemyColor.a);
        SDL_RenderFillRect(this->renderer, &ennemyRect);
    }

    void LibSdl2::draw(const Matrix<Entities> &mat, int score)
    {
        SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
        SDL_RenderClear(this->renderer);
        int windowWidth, windowHeight;
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
        int col = (windowWidth - (mat.getMaxCol() * 20)) / 2;
        int row = (windowHeight - (mat.getMaxRow() * 20)) / 2;
        SDL_Color textColor = {255, 255, 255, 255};
        std::string scoreStr = "Score: " + boost::lexical_cast<std::string>(score);
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreStr.c_str(), textColor);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_Rect textRect = {col, row - 50, textSurface->w, textSurface->h};
        SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
        for (std::size_t i = 0; i < mat.getMaxCol(); i++) {
            for (std::size_t j = 0; j < mat.getMaxRow(); j++) {
                if (mat[j][i] == Entities::nothing)
                    drawNothing(col + i * 20, row + j * 20);
                if (mat[j][i] == Entities::wall)
                    drawWall(col + i * 20, row + j * 20);
                if (mat[j][i] == Entities::door)
                    drawDoor(col + i * 20, row + j * 20);
                if (mat[j][i] == Entities::food)
                    drawFood(col + i * 20, row + j * 20);
                if (mat[j][i] == Entities::powerUp)
                    drawPup(col + i * 20, row + j * 20);
                if (mat[j][i] == Entities::enemy)
                    drawEnnemy(col + i * 20, row + j * 20);
                if (mat[j][i] == Entities::player)
                    drawPlayer(col + i * 20, row + j * 20);
            }
        }
        (void) score;
        SDL_RenderPresent(this->renderer);
    }

    bool LibSdl2::isOpen()
    {
        if (this->_isOpen)
            return true;
        return false;
    }

    void LibSdl2::close()
    {
        SDL_DestroyRenderer(this->renderer);
        SDL_DestroyWindow(this->window);
        SDL_Quit();
        this->_isOpen = false;
    }

    void LibSdl2::open()
    {
        this->_isOpen = true;
        SDL_Init(SDL_INIT_VIDEO);
        this->window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_SHOWN);
        this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    }

    void LibSdl2::display_label(const std::string& label, int x)
    {
        SDL_Color labelColor = {255, 255, 255, 255};
        SDL_Surface* labelSurface = TTF_RenderText_Solid(font, label.c_str(), labelColor);
        SDL_Texture* labelTexture = SDL_CreateTextureFromSurface(renderer, labelSurface);
        SDL_Rect labelRect = {x, 20, labelSurface->w, labelSurface->h};
        SDL_RenderCopy(renderer, labelTexture, nullptr, &labelRect);
        SDL_FreeSurface(labelSurface);
        SDL_DestroyTexture(labelTexture);
    }

    void LibSdl2::display_list(const std::vector<std::string>& list, size_t selected_index, int x)
    {
        SDL_Color textColor = {255, 255, 255, 255};
        SDL_Color selectedTextColor = {255, 255, 0, 255};
        int y = 50;
        for (size_t i = 0; i < list.size(); ++i) {
            SDL_Surface* surface = TTF_RenderText_Solid(font, list[i].c_str(), (i == selected_index) ? selectedTextColor : textColor);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_Rect textRect = {x, y, surface->w, surface->h};
            SDL_RenderCopy(renderer, texture, nullptr, &textRect);
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
            y += surface->h + 5;
        }
    }


    void LibSdl2::drawMenu(std::vector<std::string> &games_list, std::vector<std::string> &graphics_list, size_t selected_game, size_t selected_graphical, std::vector<std::string> scores_list)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        std::string games_label = "Games list:\n";
        display_label(games_label, 50);
        display_list(games_list, selected_game, 50 + 25);
        std::string graphics_label = "Graphicals list:\n";
        display_label(graphics_label, 400);
        display_list(graphics_list, selected_graphical, 400 + 25);
        std::string username_label = "Username: \n";
        display_label(username_label, 750);
        std::string scores_label = "Scores:\n";
        display_label(scores_label, 1100);
        display_score(scores_list, 1100 + 25);
        SDL_RenderPresent(renderer);
    }

    void LibSdl2::display_score(const std::vector<std::string>& scores_list, int x)
    {
        SDL_Color textColor = {255, 255, 255, 255};
        int y = 150;
        for (const std::string& score : scores_list) {
            SDL_Surface* surface = TTF_RenderText_Solid(font, score.c_str(), textColor);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_Rect textRect = {x, y, surface->w, surface->h};
            SDL_RenderCopy(renderer, texture, nullptr, &textRect);
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
            y += surface->h + 5;
        }
    }

    std::string LibSdl2::get_player_name()
    {
        std::string input;
        bool isgood = false;
        SDL_Event event;
        while (!isgood) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_TEXTINPUT) {
                    input += event.text.text;
                } else if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_RETURN) {
                        isgood = true;
                    }
                }
            }
        }
        return input;
    }

    void LibSdl2::drawGover()
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        TTF_Font* font = TTF_OpenFont("./lib/sdl2/arial.ttf", 200);
        SDL_Color textColor = {255, 255, 255, 255};
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Game Over!", textColor);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        int textWidth = textSurface->w;
        int textHeight = textSurface->h;
        SDL_Rect destRect = {(1920 - textWidth) / 2, (1080 - textHeight) / 2, textWidth, textHeight};
        SDL_RenderCopy(renderer, textTexture, NULL, &destRect);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
        SDL_RenderPresent(renderer);
    }

}
