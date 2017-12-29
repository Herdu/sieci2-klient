#ifndef GAME_H
#define GAME_H
#include <QApplication>
#include <QMainWindow>
#include <qdebug.h>

class Game
{
private:
    QString currentPassword;
    QString currentMask;
    int numberOfPieces;

public:
    Game();
    void setNewPassword(QString password);
    QString getMask() { return this->currentMask; }
    QString getPassword();
    int getNumberOfPieces(){return this->numberOfPieces; }
    void setMask(QString mask){this->currentMask = mask;}
    void addPiece(){this->numberOfPieces++;}
};

#endif // GAME_H
