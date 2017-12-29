#include "game.h"

Game::Game()
{

}


void Game::setNewPassword(QString password){

   qDebug() << password ;
   this->currentPassword = password;


    char* mask = password.toUtf8().data();

    for(int i=0; i< password.length(); i++){

        if(mask[i] != ' '){
            mask[i] = '_';
        }
    }
    this->currentMask = QString::fromUtf8(mask);

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
