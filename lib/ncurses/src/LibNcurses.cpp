/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-arcade-camille.erades
** File description:
** LibNcurses
*/

#include "../include/LibNcurses.hpp"

namespace Arcade {
    LibNcurses::LibNcurses()
    {
		initscr();
		curs_set(0);
		start_color();
		cbreak();
		noecho();
        nodelay(stdscr, TRUE);
		keypad(stdscr, true);
        this->player = ACS_CKBOARD;
        this->food = ACS_CKBOARD;
        this->wall = ACS_CKBOARD;
        this->nothing = ' ';
        this->ennemy = ACS_CKBOARD;
        this->powerup = ACS_CKBOARD;
        this->door = ACS_CKBOARD;
        this->window = stdscr;
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        init_pair(2, COLOR_RED, COLOR_BLACK);
        init_pair(3, COLOR_WHITE, COLOR_BLACK);
        init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(5, COLOR_CYAN, COLOR_BLACK);
        init_pair(6, COLOR_YELLOW, COLOR_BLACK);
    }

    LibNcurses::~LibNcurses()
    {
        this->close();
    }

    Keys LibNcurses::getEvents()
    {
        int key = getch();
        if (key == KEY_LEFT)
            return Keys::LEFT;
        else if (key == KEY_RIGHT)
            return Keys::RIGHT;
        else if (key == KEY_UP)
            return Keys::UP;
        else if (key == KEY_DOWN)
            return Keys::DOWN;
        else if (key == 27)
            return Keys::ESC;
        else if (key == '\n')
            return Keys::ENTER;
        else if (key >= 'a' && key <= 'z')
            return static_cast<Keys>(key - 96);
        return Keys::NONE;
    }

    std::string LibNcurses::getName() const
    {
        return "Ncurses";
    }

    void LibNcurses::drawFood(int i, int j)
    {
        attron(COLOR_PAIR(2));
        mvwaddch(window, j, i, this->food);
        mvwaddch(window, j, i + 1, this->food);
        attroff(COLOR_PAIR(2));
    }

    void LibNcurses::drawPlayer(int i, int j)
    {
        attron(COLOR_PAIR(1));
        mvwaddch(window, j, i, this->player);
        mvwaddch(window, j, i + 1, this->player);
        attroff(COLOR_PAIR(1));
    }

    void LibNcurses::drawNothing(int i, int j)
    {
        mvwaddch(window, j, i, this->nothing);
        mvwaddch(window, j, i + 1, this->nothing);
    }

    void LibNcurses::drawWall(int i, int j)
    {
        attron(COLOR_PAIR(3));
        mvwaddch(window, j, i, this->wall);
        mvwaddch(window, j, i + 1, this->wall);
        attroff(COLOR_PAIR(3));
    }

    void LibNcurses::drawDoor(int i, int j)
    {
        attron(COLOR_PAIR(4));
        mvwaddch(window, j, i, this->door);
        mvwaddch(window, j, i + 1, this->door);
        attroff(COLOR_PAIR(4));
    }

    void LibNcurses::drawPup(int i, int j)
    {
        attron(COLOR_PAIR(5));
        mvwaddch(window, j, i, this->powerup);
        mvwaddch(window, j, i + 1, this->powerup);
        attroff(COLOR_PAIR(5));
    }

    void LibNcurses::drawEnnemy(int i, int j)
    {
        attron(COLOR_PAIR(6));
        mvwaddch(window, j, i, this->ennemy);
        mvwaddch(window, j, i + 1, this->ennemy);
        attroff(COLOR_PAIR(6));
    }

    void LibNcurses::draw(const Matrix<Entities> &mat, int score)
    {
        clear();
        int col = COLS / 2 - mat.getMaxCol();
        int row = LINES / 2 - mat.getMaxRow() / 2;
        mvprintw(row - 2, col, "Score: %d", score);
        for (std::size_t i = 0; i < mat.getMaxCol(); i++) {
            for (std::size_t j = 0; j < mat.getMaxRow(); j++) {
                if (mat[j][i] == Entities::nothing)
                    drawNothing(col + i * 2, row + j);
                if (mat[j][i] == Entities::wall)
                    drawWall(col + i * 2, row + j);
                if (mat[j][i] == Entities::door)
                    drawDoor(col + i * 2, row + j);
                if (mat[j][i] == Entities::food)
                    drawFood(col + i * 2, row + j);
                if (mat[j][i] == Entities::powerUp)
                    drawPup(col + i * 2, row + j);
                if (mat[j][i] == Entities::enemy)
                    drawEnnemy(col + i * 2, row + j);
                if (mat[j][i] == Entities::player)
                    drawPlayer(col + i * 2, row + j);
            }
        }
        refresh();
    }

    bool LibNcurses::isOpen()
    {
        return this->window != nullptr;
    }

    void LibNcurses::close()
    {
        endwin();
	    this->window = nullptr;
    }

    void LibNcurses::open()
    {
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        curs_set(0);
    }

    void LibNcurses::display_list(const std::vector<std::string>& list, size_t selected_index)
    {
        init_pair(8, COLOR_BLACK, COLOR_YELLOW);
        for (size_t i = 0; i < list.size(); ++i) {
            if (i == selected_index) {
                attron(COLOR_PAIR(8));
                printw("%s\n", list[i].c_str());
                attroff(COLOR_PAIR(8));
            } else {
                printw("%s\n", list[i].c_str());
            }
        }
    }

    void LibNcurses::drawMenu(std::vector<std::string> &games_list, std::vector<std::string> &graphics_list, size_t selected_game, size_t selected_graphical, std::vector<std::string> scores_list)
    {
        clear();
        printw("Games lists:\n");
        display_list(games_list, selected_game);

        printw("\nGraphicals list:\n");
        display_list(graphics_list, selected_graphical);

        printw("\nscores list:\n");
        display_list(scores_list, 10);

        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::string LibNcurses::get_player_name()
    {
        printw("\nUsername: ");
        refresh();
        echo();
        char input[100];
        int ch;
        int i = 0;
        while ((ch = getch()) != '\n') {
            if (i < 99 && isprint(ch)) {
                input[i++] = ch;
                refresh();
            }
        }
        input[i] = '\0';
        return input;
    }

    void LibNcurses::drawGover()
    {
        clear();
        start_color();
        init_pair(7, COLOR_WHITE, COLOR_BLACK);
        attron(COLOR_PAIR(7));
        int maxY, maxX;
        getmaxyx(stdscr, maxY, maxX);
        int startY = maxY / 2 - 3;
        int startX = (maxX - 58) / 2;
        mvprintw(startY, startX, "   ____                           ___                   _ ");
        mvprintw(startY + 1, startX, "  / ___| __ _ _ __ ___   ___     / _ \\__   _____ _ __  | |");
        mvprintw(startY + 2, startX, " | |  _ / _` | '_ ` _ \\ / _ \\   | | | \\ \\ / / _ \\ '__| | |");
        mvprintw(startY + 3, startX, " | |_| | (_| | | | | | |  __/   | |_| |\\ V /  __/ |    |_|");
        mvprintw(startY + 4, startX, "  \\____|\\__,_|_| |_| |_|\\___|    \\___/  \\_/ \\___|_|    (_)");
        mvprintw(startY + 5, startX, "                                                          ");
        refresh();
        attroff(COLOR_PAIR(7));
    }

};
