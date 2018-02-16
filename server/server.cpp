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
#include<cstdlib>
#include<ctime>

#include "src/Player.h"
#include "src/Game.h"

using namespace std;


Game game;


int main(int argc, char ** argv){

    std::srand(std::time(0));

    if(!game.readConfigFile("config.txt")){
        cout << "Couldn't read config file" <<endl;
        exit(1);
    };

    cout << "[SERVER]: start" << endl;

    game.getDictionaryFromFile("dictionary.txt");

    int epollHandler = epoll_create1(0);

    game.assignToEpoll(epollHandler);
    game.initTimeout(epollHandler);


    int servFd = game.getFd();
    int tfd = game.getTimeFd();

    int resultCount;

    epoll_event event;

    game.start();

    while((resultCount = epoll_wait(epollHandler, &event, 1, -1)) != -1){

        if(event.events == EPOLLIN){

            if(event.data.fd == servFd){
                game.acceptConnection(epollHandler);

            }else if(event.data.fd == tfd){
                game.processGameTimeout();

            }else{
                game.processMessage(event.data.fd);
            }
        }

    }
}


