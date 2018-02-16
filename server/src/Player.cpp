//
// Created by root on 23.12.17.
//
#include "Player.h"
#include "struct.h"

using namespace std;



Player::Player(int fd) {
    this->name = "Anonymous";
    this->points = 0;
    this->fd = fd;
}




bool Player::writeData(string message) {
    message = message + "%"; //end of msg sign

    ssize_t count = message.length();
    char buffer[message.size()];
    strcpy(buffer, message.c_str());

    int total = 0;        // how many bytes we've sent
    int bytesleft = count; // how many we have left to send
    int n, bytesToWriteNow;


    while(total < count) {

        if(count - total <  512){
            bytesToWriteNow = count - total;
        }else{
            bytesToWriteNow = 512;
        }

        n = send(this->fd, buffer + total, bytesToWriteNow, MSG_CONFIRM);


        if (n == -1) { break; }
        total += n;
        bytesleft -= n;
    }

    return n !=-1; // return -1 on failure, 0 on success


}

bool Player::writeData(int tourId, CMD_STRUCT cmdStruct){
    return this->writeData(to_string(tourId) + ":" + to_string(cmdStruct.cmd) + ":" + cmdStruct.arg + ";");
}

bool Player::writeData(int tourId, vector< CMD_STRUCT > args){

    string message = "";

    for(vector<CMD_STRUCT>::iterator it = args.begin(); it != args.end(); ++it) {

        message = message + to_string(tourId) + ":" + to_string(it->cmd) + ":" + it->arg + ";";
    }

    return this->writeData(message);
};



