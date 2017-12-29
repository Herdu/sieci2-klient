//
// Created by root on 26.12.17.
//

#include "Game.h"
#include <vector>

using namespace std;


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

    int res = bind(this->fd, (sockaddr*)&serverAddr, sizeof(serverAddr));

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
    char buffer[1024];
    int count = read(clientFd, buffer, 1024);

    cout << "reading buffer" << endl;

    if(count < 1) {
        this->removePlayer(clientFd);
    } else {
        char* command_array = strtok(buffer, ";");

        while(command_array)
        {
            char* temp = command_array;
            command_array = strtok(NULL, ";");

            int command_index;
            string command_argument;
            int i = 0;

            char* single_cmd_array = strtok(temp, ":");

            while(single_cmd_array) {

                char *temp = single_cmd_array;
                single_cmd_array = strtok(NULL, ":");

                if (i == 0) {
                    sscanf(temp, "%d", &command_index);
                } else if (i == 1) {
                    command_argument = string(temp);
                } else {
                    break;
                }
                i++;

            }


            cout << "processing command " << command_index << "  " << command_argument << endl;
            this->processCommand(clientFd, command_index, command_argument);

        }
    }

}


void Game::sendToAll(COMMAND command, string argument){
    for(vector<Player>::iterator it = this->player.begin(); it != this->player.end(); ++it) {
        it->writeData(command, argument);
    }
}

void Game::sendToPlayer(int clientFd, COMMAND command, string argument){
    for(vector<Player>::iterator it = this->player.begin(); it != this->player.end(); ++it) {
        if(it->getFd() == clientFd){
            it->writeData(command, argument);
            return;
        }
    }
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
    event.events = EPOLLIN;
    event.data.fd = clientFd;

    epoll_ctl(epollHandler, EPOLL_CTL_ADD, clientFd, &event);
}


void Game::setReuseAddr(){
    const int one = 1;
    int res = setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    if(res) {
        error(1,errno, "setsockopt failed");
    }
}

void Game::assignToEpoll(int epollHandler) {

    epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = this->fd;

    epoll_ctl(epollHandler, EPOLL_CTL_ADD, this->fd, &event);

}

void Game::initTimeout(int epollHandler){
    int tfd;//timer fd

    if((tfd= timerfd_create(CLOCK_MONOTONIC,TFD_NONBLOCK)) < 0)
        cout<<"timerfd create error"<<endl;

    this->timeFd = tfd;

    epoll_event event;
    event.data.fd = tfd;
    event.events = EPOLLIN;

    if( epoll_ctl(epollHandler,EPOLL_CTL_ADD,this->timeFd,&event) < 0)
        cout<<"epoll_ctl error"<<endl;
}


void Game::processGameTimeout() {

    uint64_t value;
    read(this->timeFd, &value, 8);

    switch(this->timeoutCommand){
        case END_OF_ROUND:
            cout << "[TIMEOUT] End of round." << endl;
            this->timeoutCommand = NOTHING;
            //TODO PRZELICZENIE GLOSOW
            this->sendToAll(END_OF_ROUND," ");
            break;

        case NEW_PASSWORD:
            cout<< "[GAME] setting new password" <<endl;
            this->start();
            break;
        case NEXT_TOUR:
            cout<<"[GAME] next tour" << endl;
            this->sendToAll(NEXT_TOUR, " ");
            break;

        default:
            cout << "[TIMEOUT] No matching command " << endl;
            //this->setGameTimeout(5, END_OF_ROUND);
    }
}


void Game::processCommand(int clientFd, int command, string argument) {

    COMMAND cmd = static_cast<COMMAND>(command);

    switch (cmd){
        case GET_PASSWORD:
            cout << "[GAME] player " << clientFd <<" asked for password with mask" << endl;
            this->sendToPlayer(clientFd, NEW_PASSWORD, this->currentPassword);
            this->sendToPlayer(clientFd, SEND_MASK, this->currentMask);
            break;
        case SET_NICKNAME:
            cout << "[GAME] Set nickname '" <<  argument <<"' for player with fd = "<< clientFd << endl;
            break;
        case LETTER_VOTE:
            cout << "vote for letter" << endl;
            this->showLetter(argument);
            break;
        default:
            cout << "[SERVER] Unknown command from player";
            break;
    }
}


void Game::getDictionaryFromFile(string filename) {
    string line;
    ifstream myfile (filename);
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            this->dictionary.push_back( (string)line );
        }
        myfile.close();
        cout<<"[SERVER] " << dictionary.size() << " word(s) read from " << filename << endl;

    }
    else{
        cout << "Unable to open file";
    }
}

void Game::setGameTimeout(int length, COMMAND command) {

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
        cout<<"settime error "<<strerror(errno)<<endl;
    }


    this->timeoutCommand = command;
    this->timeoutLength = length;

}


void Game::start(){
    //Begin of round
    this->numberOfPieces = 0;

    //prepare password and mask
    int temp = rand() % this->dictionary.size();
    this->currentPassword = dictionary[temp];
    string currentMask = this->currentPassword;

    for(int i=0; i<this->currentPassword.length(); i++){
        if(this->currentPassword[i] == ' ')
        {
            currentMask[i] = ' ';
        }else{
            currentMask[i] = '_';
        }
    }
    this->currentMask = currentMask;

    cout << "[GAME] Current password is: " << currentPassword << endl;

    //new_password means begin of first tour in the round
    this->sendToAll(NEW_PASSWORD, currentPassword);

    //next tour every 15sec
    this->setGameTimeout(15, NEXT_TOUR);

}

void Game::showLetter(string argument) {
    cout << "[GAME] Checking password for letter "<< argument << endl;
    int count = 0;
    int hiddenCount = 0;
    string password = this->currentPassword;
    string mask = this->currentMask;
    if(argument.size() < 1){
        return;
    }
    char letter = tolower(argument[0]);

    for (int i = 0; i < password.size(); i++)
    {
        if (tolower(password[i]) == letter){
            mask[i] = ' ';
            count++;
        }

        if(mask[i] != '_'){
            hiddenCount ++;
        }
    }


    if(count > 0){
        cout << "[GAME] Letter " << letter << " is in password! "<< endl;
        this->currentMask = mask;
        this->sendToAll(SEND_MASK, this->currentMask);
    }else{
        cout << "[GAME] Letter " << letter << " is not in password."<< endl;
    }

    if(hiddenCount == password.size()){
        this->endOfRound();
    }

}

void Game::endOfRound(){
    this->setGameTimeout(3, NEW_PASSWORD);
}