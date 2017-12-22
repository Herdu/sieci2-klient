#include "mainwindow.h"
#include "game.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    string nick = "Albert Einstein";
    string port = "13";
    string address = "127.0.0.1";
    Game game(nick);

    bool connectionResult = game.connection(address, port);


    if(!connectionResult){
        cout << "Couldn't connect to " << address << ":" << port << endl;
        exit(1);
    }else{
        cout << "Connected to " << address << ":" << port << endl;
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();
    }



}
