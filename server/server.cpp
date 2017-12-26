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


#include "src/GameTime.h"

using namespace std;

// server socket
int servFd;

// client sockets
std::unordered_set<int> clientFds;

// handles SIGINT
void ctrl_c(int);

// sends data to clientFds excluding fd
void sendToAllBut(int fd, char * buffer, int count);

// converts cstring to port
uint16_t readPort(char * txt);

// sets SO_REUSEADDR
void setReuseAddr(int sock);

void acceptConnection(int epollHandler){
    // prepare placeholders for client address
    sockaddr_in clientAddr{0};
    socklen_t clientAddrSize = sizeof(clientAddr);

    // accept new connection
    auto clientFd = accept(servFd, (sockaddr*) &clientAddr, &clientAddrSize);
    if(clientFd == -1) error(1, errno, "accept failed");

    // add client to all clients set
    clientFds.insert(clientFd);



    // tell who has connected
    printf("new connection from: %s:%hu (fd: %d)\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), clientFd);

    epoll_event event;
    event.events = EPOLLIN || EPOLLET;
    event.data.fd = clientFd;

    epoll_ctl(epollHandler, EPOLL_CTL_ADD, clientFd, &event);
}

void sendMessage(int clientFd){
    // read a message
    char buffer[255];
    int count = read(clientFd, buffer, 255);
    if(count < 1) {
        printf("removing %d\n", clientFd);
        clientFds.erase(clientFd);
        close(clientFd);
    } else {
        // broadcast the message
        sendToAllBut(clientFd, buffer, count);
    }
}


int main(int argc, char ** argv){
    // get and validate port number
    //if(argc != 2) error(1, 0, "Need 1 arg (port)");
    auto port = readPort("12345"/*argv[1]*/);


    /********************************timer part */
    int tfd;//timer fd
    if((tfd= timerfd_create(CLOCK_MONOTONIC,TFD_NONBLOCK)) < 0)
        cout<<"timerfd create error"<<endl;
    struct itimerspec newValue;
    struct itimerspec oldValue;
    bzero(&newValue,sizeof(newValue));
    bzero(&oldValue,sizeof(oldValue));
    struct timespec ts;

    int czas = 15;

    ts.tv_sec = czas;
    ts.tv_nsec = 0;
    //both interval and value have been set
    newValue.it_value = ts;
    newValue.it_interval = ts;
    if( timerfd_settime(tfd,0,&newValue,&oldValue) <0)
    {
        cout<<"settime error"<<strerror(errno)<<endl;
    }




    /********************************timer part END */


    // create socket
    servFd = socket(AF_INET, SOCK_STREAM, 0);
    if(servFd == -1) error(1, errno, "socket failed");

    // graceful ctrl+c exit
    signal(SIGINT, ctrl_c);
    // prevent dead sockets from throwing pipe errors on write
    signal(SIGPIPE, SIG_IGN);

    setReuseAddr(servFd);

    // bind to any address and port provided in arguments
    sockaddr_in serverAddr{.sin_family=AF_INET, .sin_port=htons((short)port), .sin_addr={INADDR_ANY}};
    int res = bind(servFd, (sockaddr*) &serverAddr, sizeof(serverAddr));
    if(res) error(1, errno, "bind failed");

    // enter listening mode
    res = listen(servFd, 1);
    if(res) error(1, errno, "listen failed");

/****************************/

    int epollHandler = epoll_create1(0);

    epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = servFd;

    epoll_ctl(epollHandler, EPOLL_CTL_ADD, servFd, &event);


    /*** time ***/

    event.data.fd = tfd;
    event.events = EPOLLIN | EPOLLET;

    if( epoll_ctl(epollHandler,EPOLL_CTL_ADD,tfd,&event) < 0)
        cout<<"epoll_ctl error"<<endl;

    /******/



    int resultCount;
    while((resultCount = epoll_wait(epollHandler, &event, 1, -1)) != -1){
        if( event.events == EPOLLIN && event.data.fd == servFd ){
            acceptConnection(epollHandler);
        }

        if( (event.events == EPOLLIN) && event.data.fd != servFd && event.data.fd != tfd){
            sendMessage(event.data.fd);
        }

        if( event.events == EPOLLIN  && event.data.fd == tfd){
            uint64_t value;
            read(tfd, &value, 8);
            cout<<"minelo "<<czas << " sekund."<<endl;
        }

    }
}

uint16_t readPort(char * txt){
    char * ptr;
    auto port = strtol(txt, &ptr, 10);
    if(*ptr!=0 || port<1 || (port>((1<<16)-1))) error(1,0,"illegal argument %s", txt);
    return port;
}

void setReuseAddr(int sock){
    const int one = 1;
    int res = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    if(res) error(1,errno, "setsockopt failed");
}

void ctrl_c(int){
    for(int clientFd : clientFds)
        close(clientFd);
    close(servFd);
    printf("Closing server\n");
    exit(0);
}

void sendToAllBut(int fd, char buffer[], int count){
    printf("Player with fd=%d sent: ",fd);
    for (int i=0; i<count; i++){
        printf("%c", buffer[i]);
    }
    printf("\n");


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
}