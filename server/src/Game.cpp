//
// Created by root on 26.12.17.
//

#include "Game.h"
#include <vector>




Game::Game(){

    this->port = 12345;

    // create socket
    int servFd = socket(AF_INET, SOCK_STREAM, 0);

    if(servFd == -1) {
        error(1, errno, "socket failed");
    }


    this->fd = servFd;


    // prevent dead sockets from throwing pipe errors on write
    signal(SIGPIPE, SIG_IGN);
    this->setReuseAddr();

    // bind to any address and port provided in arguments
    sockaddr_in serverAddr{.sin_family=AF_INET, .sin_port=htons((short)port), .sin_addr={INADDR_ANY}};

    int res = bind(this->fd, (sockaddr*) &serverAddr, sizeof(serverAddr));

    if(res) {
        error(1, errno, "bind failed");
    }

    // enter listening mode
    res = listen(this->fd, 1);

    if(res) {
        error(1, errno, "listen failed");
    }

}


void Game::addPlayer(int fd){

    Player _player(fd);

    this->player.push_back(_player);
    cout <<"[GAME] player with fd= " << fd << " added to the game" <<endl;
}

void Game::removePlayer(int fd){

    for(vector<Player>::iterator it = this->player.begin(); it != this->player.end();) {
        if (it->getFd() == fd){

            //remove player from vector
            it = this->player.erase(it);
            //close socket
            close(fd);

            cout << "[GAME] Player with fd=" << fd << " has been removed." << endl;
            return;
        }
        else
            ++it;
    }

}


void Game::processMessage(int clientFd){
    // read a message
    char buffer[255];
    int count = read(clientFd, buffer, 255);
    if(count < 1) {
        this->removePlayer(clientFd);
    } else {
        // broadcast the message
        this->sendToAll(clientFd, buffer, count);
    }



}


void Game::sendToAll(int fd, char buffer[], int count){

    printf("[PLAYER fd=%d] sent: ",fd);
    for (int i=0; i<count; i++){
        printf("%c", buffer[i]);
    }
    printf("\n");

    /*
    int res;
    decltype(clientFds) bad;
    for(int clientFd : clientFds){
        if(clientFd == fd) continue;
        res = write(clientFd, buffer, count);
        if(res!=count)
            bad.insert(clientFd);
    }
    for(int clientFd : bad){
        printf("removing %d\n", clientFd);
        clientFds.erase(clientFd);
        close(clientFd);
    }
     */
}



void Game::acceptConnection(int epollHandler){
    // prepare placeholders for client address
    sockaddr_in clientAddr{0};
    socklen_t clientAddrSize = sizeof(clientAddr);

    // accept new connection
    auto clientFd = accept(this->fd, (sockaddr*) &clientAddr, &clientAddrSize);
    if(clientFd == -1) error(1, errno, "accept failed");

    // tell who has connected
    printf("[SERVER] new connection from: %s:%hu (fd = %d)\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), clientFd);

    this->addPlayer(clientFd);

    epoll_event event;
    event.events = EPOLLIN || EPOLLET;
    event.data.fd = clientFd;

    epoll_ctl(epollHandler, EPOLL_CTL_ADD, clientFd, &event);
}


void Game::setReuseAddr(){
    const int one = 1;
    int res = setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    if(res) error(1,errno, "setsockopt failed");
}

void Game::assignToEpoll(int epollHandler) {

    epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = this->fd;

    epoll_ctl(epollHandler, EPOLL_CTL_ADD, this->fd, &event);

}

void Game::setGameInterval(int epollHandler, int length){
    int tfd;//timer fd
    this->intervalLength = length;

    if((tfd= timerfd_create(CLOCK_MONOTONIC,TFD_NONBLOCK)) < 0)
        cout<<"timerfd create error"<<endl;

    this->timeFd = tfd;

    struct itimerspec newValue;
    struct itimerspec oldValue;
    bzero(&newValue,sizeof(newValue));
    bzero(&oldValue,sizeof(oldValue));
    struct timespec ts;

    ts.tv_sec = length;
    ts.tv_nsec = 0;

    //both interval and value have been set
    newValue.it_value = ts;
    newValue.it_interval = ts;
    if( timerfd_settime(this->timeFd,0,&newValue,&oldValue) <0)
    {
        cout<<"settime error"<<strerror(errno)<<endl;
    }


    epoll_event event;
    event.data.fd = tfd;
    event.events = EPOLLIN;

    if( epoll_ctl(epollHandler,EPOLL_CTL_ADD,this->timeFd,&event) < 0)
        cout<<"epoll_ctl error"<<endl;
}

void Game::processTimeInterval() {
    uint64_t value;
    read(this->timeFd, &value, 8);
    cout<<"[GAME] " << this->intervalLength << "secs have passed. End of round."<<endl;
}