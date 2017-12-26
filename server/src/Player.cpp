//
// Created by root on 23.12.17.
//
#include "Player.h"

using namespace std;



Player::Player(int fd) {
    this->name = "Anonymous";
    this->points = 0;
    this->fd = fd;
}


