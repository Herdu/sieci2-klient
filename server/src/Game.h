//
// Created by root on 26.12.17.
//

#ifndef CLIENT_GAME_H
#define CLIENT_GAME_H

#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <error.h>
#include <netdb.h>
#include <sys/epoll.h>
#include <poll.h>
#include <thread>
#include <unordered_set>
#include <signal.h>
#include <sys/epoll.h>
#include <sys/timerfd.h>
#include <iostream>
#include <strings.h>
#include <string.h>
#include <vector>


#include "Player.h"

using namespace std;

class Game{

private:
    int fd; //server socket id
    int timeFd; //time id
    int intervalLength;
    uint16_t port;

    vector<Player> player;

    void removePlayer(int fd);
    void sendToAll(int fd, char buffer[], int count);

    //init stuff
    void setReuseAddr();

public:
    int getFd(){return this->fd;};
    int getTimeFd(){return this->timeFd;};
    void addPlayer(int fd);
    void processMessage(int fd);
    void acceptConnection(int epollHandler);
    void assignToEpoll(int epollHandler);
    void setGameInterval(int epollHandler, int length);
    void processTimeInterval();
    Game();

};

#endif //CLIENT_GAME_H
