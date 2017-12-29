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

public:
    Game();
    void setNewPassword(QString password);
    QString getMask() { return this->currentMask; }
    QString getPassword();
};

#endif // GAME_H
