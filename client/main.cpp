#include "mainwindow.h"
#include "loading.h"
#include "commands.h"
#include <QApplication>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <error.h>
#include <netdb.h>
#include <sys/epoll.h>
#include <QMessageBox>
#include <QProgressDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //VALIDATE NICKANAME PASSED IN ARGUMENT
    if(argc < 2){
        QMessageBox msgBox;
        msgBox.setText("Please provide your nickname as first argument of the program");
        msgBox.exec();
        return 1;
    }
    QString nick = QString::fromUtf8(argv[1]).replace(";", "").replace(":", "").replace("%", "");
    if(nick.length() < 3 || nick.length() > 16){
        QMessageBox msgBox;
        msgBox.setText("Nickname length must be between 3 and 16 characters!");
        msgBox.exec();
        return 1;
    }

    MainWindow window;

    if(!window.readConfigFile("config.txt")){ //read address and port from config file
        QMessageBox msgBox;
        msgBox.setText("Could not properly read config file!");
        msgBox.exec();
        return 1;
    }


    if(window.connectTcp(nick)){
        window.init();
        window.show();
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Could not connect to the server. Please try again later.");
        msgBox.exec();
    }
    return a.exec();
}
