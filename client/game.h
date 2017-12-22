#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <QString>
#include <QStringList>
#include <QObject>
#include <QTcpSocket>
#include <QPointer>
#include <QAuthenticator>
#include <QSslSocket>

using namespace std;


class Game : QTcpSocket
{
public:
    Game(string nick);
    bool connection(string address, string port);


private:
    QTcpSocket *tcpSocket = nullptr;
};

#endif // GAME_H
