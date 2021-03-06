#include "game.h"

using namespace std;

Game::Game()
{
    this->numberOfPieces = 0;
}


void Game::setNewPassword(QString password){

   this->currentPassword = password;
   QString mask = "";

    for(int i=0; i< password.length(); i++){

        if(password.at(i) != QChar(' ')){
            mask+="_";
        }else{
            mask+=" ";
        }
    }
    this->currentMask = mask;
}


QString Game::getPassword(){

    QString _mask = this->currentMask;
    QString password = this->currentPassword;
    int length = password.length();
    QString _password = "";

    for(int i=0; i< length; i++){


        if(_mask.at(i) == QChar('_')){
            _password += "_ ";
        }else{
            _password += password.at(i);
            _password += " ";
        }
    }

    return  _password;
}


