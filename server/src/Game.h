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
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>

#include "Player.h"
#include "commands.h"

using namespace std;

class Game{

private:
    string currentPassword;
    string currentMask;

    int fd; //server socket id
    int timeFd; //time id
    COMMAND timeoutCommand;
    int timeoutLength;
    uint16_t port;
    vector<string> dictionary;
    vector<Player> player;
    int numberOfPieces;

    void removePlayer(int fd);
    void sendToAll(COMMAND command, string argument);
    void sendToPlayer(int clientFd,COMMAND command, string argument );
    void processCommand(int clientFd, int command, string argument);
    void showLetter(string argument);
    void endOfRound();
    //init stuff
    void setReuseAddr();

public:
    int getFd(){return this->fd;};
    int getTimeFd(){return this->timeFd;};
    void addPlayer(int fd);
    void processMessage(int fd);
    void acceptConnection(int epollHandler);
    void assignToEpoll(int epollHandler);
    void initTimeout(int epollHandler);
    void setGameTimeout(int length, COMMAND command);

    void processGameTimeout();
    void getDictionaryFromFile(string filename);

    void start();

    Game();

};

#endif //CLIENT_GAME_H
