//
// Created by root on 23.12.17.
//

using namespace std;

#include "Player.h"


Player::Player(int fd) {
    this->name = "Anonymous";
    this->points = 0;
    this->fd = fd;

    cout << "[SERVER] Created player with fd = " << fd <<endl;
}


