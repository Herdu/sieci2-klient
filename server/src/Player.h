//
// Created by root on 26.12.17.
//

#ifndef CLIENT_PLAYER_H
#define CLIENT_PLAYER_H


#include <iostream>

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
};




#endif //CLIENT_PLAYER_H
