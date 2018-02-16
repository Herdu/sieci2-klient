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
#include <sstream>
#include <regex>
#include <cstdlib>
#include <ctime>

#include "Player.h"
#include "commands.h"
#include "struct.h"

using namespace std;



struct Alphabet{
    char character;
    int votes;
    bool isVisible;
};


class Game{

private:
    string currentPassword;
    string currentMask;

    int tourId;
    int playerLimit = 10;

    int fd; //server socket id
    int timeFd; //time id
    COMMAND timeoutCommand;
    int timeoutLength;
    uint16_t port;
    vector<string> dictionary;
    vector<Player> player;
    vector<Alphabet> alphabet;
    int numberOfPieces;

    void removePlayer(int fd);
    void sendToAll(CMD_STRUCT cmdStruct);
    void sendToAll(vector <CMD_STRUCT> args);
    void sendToPlayer(int clientFd, CMD_STRUCT cmdStruct);
    void sendToPlayer(int clientFd, vector <CMD_STRUCT> args);
    void processCommand(int clientFd, int command, string argument, int roundId);
    void showLetter(char letter);
    void endOfRound();
    void endOfTour();
    void roundLost();
    void sendAlphabet();
    void resetAlphabet();
    string getAlphabet();
    void sendAlphabetToPlayer(int clientFd);
    void passwordGuess(int clientFd, string password);
    void makeVote(string argument);

    void sendListOfPlayers();
    void setNickname(int clientFd, string nickname);
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
    bool readConfigFile(const char* filename);

    void processGameTimeout();
    void getDictionaryFromFile(string filename);

    void start();

    Game();

};

#endif //CLIENT_GAME_H
