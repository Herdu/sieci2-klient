#include "mainwindow.h"
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



int main(int argc, char *argv[])
{

    QString nick = "Albert Einstein";
    QString port = "12345";
    QString address = "127.0.0.1";


    QApplication a(argc, argv);
    MainWindow window;
    if(window.connectTcp(address,port, nick)){
        window.show();
    }
    else{
        cout <<"couldn't connect to the server" <<endl;
    }
    return a.exec();
}
