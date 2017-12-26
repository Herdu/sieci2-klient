CC = g++
CFLAGS = -Wall -std=c++11

all: server.o game.o player.o
	$(CC) ${CFLAGS} server.o player.o game.o -o server

server.o: server.cpp
	$(CC) ${CFLAGS} server.cpp -c -o server.o

game.o: src/Game.h src/Game.cpp
	$(CC) ${CFLAGS} src/Game.cpp -c -o game.o

player.o: src/Player.h src/Player.cpp
	$(CC) ${CFLAGS} src/Player.cpp -c -o player.o


clean:
	rm *.o
	rm server
