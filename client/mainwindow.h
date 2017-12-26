#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QTcpSocket>
#include <QHostAddress>

#include "commands.h"


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
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTcpSocket * pSocket;
    QObjectList letterButtons;
    void resetKeyboard();


private slots:
    void letterPressed();
    void letterSelected();
    void readTcpData();
    bool writeData(COMMAND command, QString data);
};

#endif // MAINWINDOW_H
