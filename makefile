CC=g++
N=main
F=*.cpp

compile:
	$(CC) -o $(N) $(F) `sdl2-config --cflags --libs` -lSDL2_ttf

link:
