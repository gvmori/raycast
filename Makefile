all:
	g++ -I/usr/include/SDL2 -o raycast.o src/*.cpp -lSDL2 -std=c++11 -Wall
clean:
	rm raycast.o
