//
// Created by root on 26.12.17.
//

#include "Game.h"
#include <vector>

using namespace std;

bool Game::readConfigFile(const char* filename) {

    string line, dummyLine;
    int port;

    ifstream myfile (filename);
    if (myfile.is_open())
    {
        try{
            getline (myfile,dummyLine); //skip first line
            getline (myfile,line);
            port = std::stoi( line );
            cout << "port: " << port << endl;

            this->port = port;
            myfile.close();

            return true;

        }catch(int e){
            return false;
        };
    }
    else
        return false;

}

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



    //init alphabet

    char tab [] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p','q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    for( int i=0; i< 26; i++){
        Alphabet a;
        a.character = tab[i];
        a.votes = 0;
        a.isVisible = false;
        this->alphabet.push_back(a);
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
            this->sendListOfPlayers();

            return;
        }
        else
            ++it;
    }

}


void Game::processMessage(int clientFd){
    // read a message
    char buffer[1024];
    int tempCount = 0;
    std::stringstream ss;

    int sizeOfBuffer =  sizeof(buffer) - 1;

    tempCount = read(clientFd, buffer, sizeOfBuffer);

    if(tempCount == -1){
        return;
    }
    if(tempCount == 0){
        this->removePlayer(clientFd);
        return;
    }

    string input = string(buffer);
    std::regex rgx("[:;]");
    std::sregex_token_iterator iter(input.begin(), input.end(), rgx, -1);

    int lengthOfMessage = stoi(*iter++);

    int lengthOfMessageLength = to_string(lengthOfMessage).length();

    lengthOfMessage += lengthOfMessageLength;

    while(lengthOfMessage > (sizeOfBuffer) && tempCount > 0){
        tempCount = read(clientFd, buffer, sizeOfBuffer);
        input.append(string(buffer));
        lengthOfMessage -= (sizeOfBuffer);
    }

    // structure of message
    // {length_of_message_in_bytes} : {round_id} : {command} : {argument} ;

    std::sregex_token_iterator iter2(input.begin(), input.end(), rgx, -1);
    *iter2++; //skip message length
    int tourId = stoi(string(*iter2++));
    int cmd = stoi(*iter2++);
    string argument = *iter2;

    cout << "round id: " <<tourId << endl;
    cout << "command: " << cmd << endl;
    cout << "argument: " << argument << endl;

    this->processCommand(clientFd, cmd, argument, tourId );

}


void Game::sendToAll(COMMAND command, string argument){
    for(vector<Player>::iterator it = this->player.begin(); it != this->player.end(); ++it) {
        if(!it->writeData(this->tourId, command, argument)){
            cout << "[Warning] could not send data to player with fd = " << it->getFd() << endl;
        };
    }

}

void Game::sendToAll(COMMAND command, int argument) {
    this->sendToAll(command, to_string(argument));
}

void Game::sendToPlayer(int clientFd, COMMAND command, string argument){
    for(vector<Player>::iterator it = this->player.begin(); it != this->player.end(); ++it) {
        if(it->getFd() == clientFd){
            if(!it->writeData(this->tourId, command, argument)){
                cout << "[Warning] could not send data to player with fd = " << it->getFd() << endl;
            };
            return;
        }
    }
}

void Game::sendToPlayer(int clientFd, COMMAND command, int argument){
    this->sendToPlayer(clientFd, command, to_string(argument));
}


void Game::acceptConnection(int epollHandler){
    // prepare placeholders for client address
    sockaddr_in clientAddr{0};
    socklen_t clientAddrSize = sizeof(clientAddr);

    // accept new connection
    auto clientFd = accept(this->fd, (sockaddr*) &clientAddr, &clientAddrSize);
    if(clientFd == -1) return; //error(1, errno, "accept failed");

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
            this->endOfTour();
            break;

        default:
            cout << "[TIMEOUT] No matching command " << endl;
    }
}


void Game::processCommand(int clientFd, int command, string argument, int tourId) {

    COMMAND cmd = static_cast<COMMAND>(command);
    switch (cmd){
        case GET_PASSWORD:
            cout << "[PLAYER] player " << clientFd <<" asked for password with mask" << endl;
            this->sendToPlayer(clientFd, NEW_PASSWORD, this->currentPassword);
            this->sendToPlayer(clientFd, SEND_MASK, this->currentMask);
            this->sendAlphabetToPlayer(clientFd);
            this->sendToPlayer(clientFd, SEND_PIECES, this->numberOfPieces);
            break;
        case SET_NICKNAME:
            cout << "[PLAYER] Set nickname '" <<  argument <<"' for player with fd = "<< clientFd << endl;
            this->setNickname(clientFd, argument);
            this->sendListOfPlayers();
            break;
        case LETTER_VOTE:
            if(tourId != this->tourId){
                cout << "[PLAYER] Wrong tour id: '" <<  tourId <<"' for player with fd = "<< clientFd << ". Current tour id is : " << this->tourId << endl;
                return;
            }
            cout << "[PLAYER] vote for letter" << endl;
            this->makeVote(argument);
            break;
        case PASSWORD_GUESS:
            if(tourId != this->tourId){
                cout << "[PLAYER] Wrong tour id: '" <<  tourId <<"' for player with fd = "<< clientFd << ". Current tour id is : " << this->tourId << endl;
                return;
            }
            cout << "[PLAYER] password guess" << endl;
            this->passwordGuess(clientFd, argument);
            break;

        default:
            cout << "[SERVER] Unknown command from player "<<clientFd << endl;
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
    this->resetAlphabet();

    //prepare password and mask
    int temp = rand() % this->dictionary.size();
    this->currentPassword = dictionary[temp];
    string currentMask = this->currentPassword;

    for(unsigned i=0; i<this->currentPassword.length(); i++){
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

void Game::showLetter(char letter) {
    int count = 0;
    unsigned hiddenCount = 0;
    string password = this->currentPassword;
    string mask = this->currentMask;

    for (unsigned i = 0; i < password.size(); i++)
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
        this->numberOfPieces++;

        if(this->numberOfPieces>9){
            this->roundLost();
        }

    }
    if(letter){
        string l = "";
        l += letter;

        if(l.length() > 0){



            this->sendToAll(SEND_LETTER, l);
        }
    }
    this->sendToAll(SEND_PIECES, this->numberOfPieces);


    if(hiddenCount == password.size()){
        this->endOfRound();
    }


    for(vector<Alphabet>::iterator it = this->alphabet.begin(); it != this->alphabet.end(); ++it) {
        if(it->character == letter){
            it->isVisible = false;
            break;
        }
    }

}

void Game::endOfRound(){
    cout << "[GAME] End of round! " << endl;
    this->setGameTimeout(3, NEW_PASSWORD);
    this->sendToAll(SEND_PIECES, this->numberOfPieces);
    this->resetAlphabet();


}

void Game::makeVote(string argument) {
    if(argument.length() > 0){
        char letter = tolower(argument.at(0));
        for(vector<Alphabet>::iterator it = this->alphabet.begin(); it != this->alphabet.end(); ++it) {
            if(it->character == letter){
                it->votes++;
                this->sendAlphabet();
                return;
            }
        }
    }

}


void Game::endOfTour() {

    //calc votes

    Alphabet winner;
    int max = 0;

    for(vector<Alphabet>::iterator it = this->alphabet.begin(); it != this->alphabet.end(); ++it) {
        if((it->isVisible) && it->votes >= max){
            winner = (*it);
            max = it->votes;
        }
        if(it->votes > 0){
            it->votes = 0;
        }
    }

    cout << "[GAME] vote winner: "<< winner.character << endl;

    this->showLetter(winner.character);

    cout<<"[GAME] next tour" << endl;

    this->tourId = rand() % 1000;

    this->setGameTimeout(15, NEXT_TOUR);
    this->sendToAll(NEXT_TOUR, " ");

}


string Game::getAlphabet(){
    string data = "";

    for(vector<Alphabet>::iterator it = this->alphabet.begin(); it != this->alphabet.end(); ++it) {
        if((!it->isVisible)){
            data += "-1,";
        }else{
            data += to_string(it->votes) + ",";
        }
    }

    return data;
}


void Game::sendAlphabetToPlayer(int clientFd){
    string data = this->getAlphabet();
    this->sendToPlayer(clientFd, SEND_ALPHABET, data);
}

void Game::sendAlphabet(){
    string data = this->getAlphabet();
    this->sendToAll(SEND_ALPHABET, data);
}

void Game::resetAlphabet() {
    for(vector<Alphabet>::iterator it = this->alphabet.begin(); it != this->alphabet.end(); ++it) {
        it->isVisible = true;
        it->votes = 0;
    }
    this->sendAlphabet();
}

void Game::roundLost(){
    this->start();
}

void Game::passwordGuess(int clientFd, string password) {


    if(password == this->currentPassword){
        cout << "password guessed!" << endl;
        this->sendToPlayer(clientFd, PASSWORD_GUESS_SUCCESS, "");
        this->endOfRound();
    }else{
        cout << "bad password" << endl;
        this->sendToPlayer(clientFd, PASSWORD_GUESS_FAILURE, "");
    }
}

void Game::sendListOfPlayers() {
    string names = "";
    for(vector<Player>::iterator it = this->player.begin(); it != this->player.end(); it++) {
        names += it->getName() + ",";
    };

    this->sendToAll(LIST_OF_PLAYERS, names);
}

void Game::setNickname(int clientFd, string nickname) {
    for(vector<Player>::iterator it = this->player.begin(); it != this->player.end(); ++it) {
        if(it->getFd() == clientFd){
            it->setName(nickname);
            return;
        }
    }
}
