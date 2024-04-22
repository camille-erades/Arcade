##
## EPITECH PROJECT, 2024
## B-OOP-400-LYN-4-1-arcade-camille.erades
## File description:
## Makefile
##

CC = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++20 -I ./include -fPIC
LDFLAGS = -shared -lncurses

SRC_DIR = ./src
SRC = $(SRC_DIR)/LibNcurses.cpp \
	$(SRC_DIR)/lib.cpp

BUILDDIR = ./obj
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(BUILDDIR)/%.o, $(SRC))

LIB = arcade_ncurses.so

$(BUILDDIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) -o $@ -MD -c $< $(CXXFLAGS)

all: $(LIB)

$(LIB): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf $(BUILDDIR)

fclean: clean
	rm -rf $(LIB)

re: fclean all

-include $(OBJ:%.o=%.d)

.PHONY: clean fclean re
