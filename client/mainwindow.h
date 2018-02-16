#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QTcpSocket>
#include <QHostAddress>
#include <QColor>
#include <QMessageBox>
#include <fstream>
#include <sstream>
#include <iostream>

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
    bool connectTcp(QString nick);
    bool readConfigFile(const char* filename);
    void init();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTcpSocket * pSocket;
    QObjectList letterButtons;
    void resetKeyboard();
    void drawImage();
    Game game;


    QString port;
    QString address;

    bool isKeyboardBlocked;

    void processMessage(int command);
    void processMessage(int command, QString argument);
    void prepareNewGame();
    void processAlphabet(QString data);
    void hideLetter(QString letter);
    void logMessage(QString message);
    void showListOfPlayers(QString names);

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
