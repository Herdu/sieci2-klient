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
#include <vector>

#include "commands.h"
#include "struct.h"

using namespace std;

class Player{
    string name;
    int fd;
    int points;
private:
    bool writeData(string message);

public:
    int getFd(){return this->fd;}
    void setName(string name){this->name = name;};
    Player(int fd);
    string getName(){return this->name;};

    bool writeData(int tourId, CMD_STRUCT);
    bool writeData(int tourId, vector< CMD_STRUCT > args);
};




#endif //CLIENT_PLAYER_H
