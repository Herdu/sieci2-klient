//
// Created by root on 26.12.17.
//

#ifndef CLIENT_PLAYER_H
#define CLIENT_PLAYER_H


#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <sys/socket.h>
#include <errno.h>
#include <error.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

#include "commands.h"

using namespace std;

class Player{
    string name;
    int fd;
    int points;
private:


public:
    int getFd(){return this->fd;}
    void setName(string name){this->name = name;};
    Player(int fd);

    bool writeData(string message);
    bool writeData(COMMAND command);
    bool writeData(COMMAND command, string message);
};




#endif //CLIENT_PLAYER_H
