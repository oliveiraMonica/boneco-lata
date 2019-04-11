# Makefile

# Dependências:
# libsdl1.2-dev
# libsdl-mixer1.2

all: mix

mix: mix.c
	gcc -o $@ $< `sdl-config --cflags --libs` -lSDL_mixer
