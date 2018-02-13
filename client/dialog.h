#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFutureWatcher>
#include <QMovie>
#include <QLabel>
#include <QGraphicsScene>
#include <QMainWindow>
using namespace std;

namespace Ui {
class MainWindow;
}


class Dialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    void setMessage(QString msg);
    ~Dialog();


private:
    Ui::MainWindow *ui;
};

#endif // DIALOG_H
