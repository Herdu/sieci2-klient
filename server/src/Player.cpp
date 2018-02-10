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




bool Player::writeData(string message) {

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

bool Player::writeData(COMMAND command){
    return this->writeData(to_string(command) + ";");
}

bool Player::writeData(COMMAND command, string argument){
    return this->writeData( to_string(command) + ":" + argument +";");
}

bool Player::writeData(string argument, COMMAND command){
    return this->writeData(command, argument);
}



