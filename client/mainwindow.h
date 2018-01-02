#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QTcpSocket>
#include <QHostAddress>
#include <QColor>
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

    bool isKeyboardBlocked;

    void processMessage(int command);
    void processMessage(int command, QString argument);
    void prepareNewGame();
    void processAlphabet(QString data);
    void hideLetter(QString letter);


private slots:
    void letterPressed();
    void letterSelected();
    void readTcpData();
    void readyRead();
    void disconnected();
    void passwordGuess();
    bool writeData(COMMAND command, QString data);
};

#endif // MAINWINDOW_H
