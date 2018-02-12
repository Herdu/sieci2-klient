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




bool Player::writeData(int tourId, string message) {

    message = to_string(tourId) + ":" + message;

    ssize_t count = message.length();
    char buffer[1024];
    strcpy(buffer, message.c_str());

    auto ret = write(this->fd, buffer, count);

    if(ret==-1) {
        //error(1, errno, "write failed on descriptor %d", fd);
        return false;
    }
    if(ret!=count) {
        //error(0, errno, "wrote less than requested to descriptor %d (%ld/%ld)", fd, count, ret);
        return false;
    }

    return ret;
}

bool Player::writeData(int tourId, COMMAND command){
    return this->writeData(tourId, to_string(command) + ";");
}

bool Player::writeData(int tourId, COMMAND command, string argument){
    return this->writeData(tourId, to_string(command) + ":" + argument +";");
}

bool Player::writeData(int tourId, string argument, COMMAND command){
    return this->writeData(tourId, command, argument);
}



