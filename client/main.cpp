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
    QString nick = "Albert Einstein";
    QString port = "12345";
    QString address = "127.0.0.1";

    MainWindow window;

    if(window.connectTcp(address,port, nick)){
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
