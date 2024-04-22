##
## EPITECH PROJECT, 2024
## B-OOP-400-LYN-4-1-arcade-camille.erades
## File description:
## Makefile
##

CC = g++
CXXFLAGS = -Wall -Wextra -Werror -fno-gnu-unique -std=c++20 -I ./include -fPIC

SRC_DIR = ./src
SRC = $(SRC_DIR)/Core.cpp \
	$(SRC_DIR)/Menu.cpp \
	$(SRC_DIR)/main.cpp \

BUILDDIR = ./obj
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(BUILDDIR)/%.o, $(SRC))

EXEC = arcade

$(BUILDDIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) -o $@ -MD -c $< $(CXXFLAGS)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^
	$(MAKE) -C lib

clean:
	rm -rf $(BUILDDIR)
	$(MAKE) -C lib clean

fclean: clean
	rm -rf $(EXEC)
	$(MAKE) -C lib fclean

re: fclean all

core:	$(OBJ)
	$(CC) -o $(EXEC) $^

games:
	$(MAKE) -C lib games

graphicals:
	$(MAKE) -C lib graphicals

-include $(OBJ:%.o=%.d)

.PHONY: clean fclean re core games graphicals
