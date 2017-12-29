#include "game.h"

Game::Game()
{

}


void Game::setNewPassword(QString password){

   qDebug() << "password: "<< password;
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
     qDebug() << "mask    " << this->currentMask;
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
