#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QTcpSocket>
#include <QHostAddress>

#include "commands.h"
#include "game.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    bool connectTcp(QString address, QString port, QString nick);
    void init();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTcpSocket * pSocket;
    QObjectList letterButtons;
    void resetKeyboard();
    void drawImage();
    Game game;

    void processMessage(int command);
    void processMessage(int command, QString argument);
    void prepareNewGame();


private slots:
    void letterPressed();
    void letterSelected();
    void readTcpData();
    void readyRead();
    void disconnected();
    bool writeData(COMMAND command, QString data);
};

#endif // MAINWINDOW_H
