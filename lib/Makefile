##
## EPITECH PROJECT, 2024
## B-OOP-400-LYN-4-1-arcade-camille.erades
## File description:
## Makefile
##

LIBNCURSES = ncurses
LIBSFML = sfml
LIBSDL2 = sdl2
LIBSNAKE = Snake
LIBNIBBLER = Nibbler
LIB = $(LIBNCURSES)/arcade_ncurses.so $(LIBSFML)/arcade_sfml.so $(LIBSNAKE)/arcade_snake.so $(LIBSDL2)/arcade_sdl2.so $(LIBNIBBLER)/arcade_nibbler.so

all: $(LIB)

$(LIB):
	$(MAKE) -C $(LIBNCURSES)
	$(MAKE) -C $(LIBSFML)
	$(MAKE) -C $(LIBSDL2)
	$(MAKE) -C $(LIBSNAKE)
	$(MAKE) -C $(LIBNIBBLER)
	mv $(LIBNCURSES)/arcade_ncurses.so .
	mv $(LIBSFML)/arcade_sfml.so .
	mv $(LIBSDL2)/arcade_sdl2.so .
	mv $(LIBSNAKE)/arcade_snake.so .
	mv $(LIBNIBBLER)/arcade_nibbler.so .

clean:
	$(MAKE) -C $(LIBNCURSES) $@
	$(MAKE) -C $(LIBSFML) $@
	$(MAKE) -C $(LIBSDL2) $@
	$(MAKE) -C $(LIBSNAKE) $@
	$(MAKE) -C $(LIBNIBBLER) $@

fclean: clean
	$(MAKE) -C $(LIBNCURSES) $@
	$(MAKE) -C $(LIBSFML) $@
	$(MAKE) -C $(LIBSDL2) $@
	$(MAKE) -C $(LIBSNAKE) $@
	$(MAKE) -C $(LIBNIBBLER) $@
	rm -f arcade_ncurses.so arcade_sfml.so arcade_snake.so arcade_sdl2.so arcade_nibbler.so

re:
	$(MAKE) -C $(LIBNCURSES) $@
	$(MAKE) -C $(LIBSFML) $@
	$(MAKE) -C $(LIBSDL2) $@
	$(MAKE) -C $(LIBSNAKE) $@
	$(MAKE) -C $(LIBNIBBLER) $@

games:	$(LIBSNAKE) $(LIBNIBBLER)
	$(MAKE) -C $(LIBSNAKE)
	$(MAKE) -C $(LIBNIBBLER)
	mv $(LIBSNAKE)/arcade_snake.so .
	mv $(LIBNIBBLER)/arcade_nibbler.so .

graphicals:	$(LIBNCURSES) $(LIBSFML) $(LIBSDL2)
	$(MAKE) -C $(LIBNCURSES)
	$(MAKE) -C $(LIBSFML)
	$(MAKE) -C $(LIBSDL2)
	mv $(LIBNCURSES)/arcade_ncurses.so .
	mv $(LIBSFML)/arcade_sfml.so .
	mv $(LIBSDL2)/arcade_sdl2.so .

.PHONY: clean fclean re $(LIB) games graphicals
