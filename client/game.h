#ifndef GAME_H
#define GAME_H
#include <QApplication>
#include <QMainWindow>
#include <qdebug.h>
#include <iostream>
#include <string>

using namespace std;

class Game
{
private:
    QString currentPassword;
    QString currentMask;
    int numberOfPieces;
    int tourId;

public:
    Game();
    void setNewPassword(QString password);
    QString getMask() { return this->currentMask; }
    QString getPassword();
    int getNumberOfPieces(){return this->numberOfPieces; }
    void setMask(QString mask){this->currentMask = mask;}
    void addPiece(){this->numberOfPieces++;}
    void setPieces(int pieces){this->numberOfPieces = pieces;}
    void setTourId(int tourId) {this->tourId = tourId;}
    int getTourId(){return this->tourId;}

};

#endif // GAME_H
