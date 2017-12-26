CC = g++
CFLAGS = -Wall -std=c++11

all: server.o gametime.o player.o
	$(CC) ${CFLAGS} server.o gametime.o player.o -o server

server.o: server.cpp
	$(CC) ${CFLAGS} server.cpp -c -o server.o

gametime.o: src/GameTime.h src/GameTime.cpp
	$(CC) ${CFLAGS} src/GameTime.cpp -c -o gametime.o

player.o: src/Player.h src/Player.cpp
	$(CC) ${CFLAGS} src/Player.cpp -c -o player.o


clean:
	rm *.o
	rm server
