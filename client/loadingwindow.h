#ifndef LOADINGWINDOW_H
#define LOADINGWINDOW_H

#include <QMainWindow>

namespace Ui {
class LoadingWindow;
}

class LoadingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoadingWindow(QWidget *parent = 0);
    ~LoadingWindow();

private:
    Ui::LoadingWindow *ui;
};

#endif // LOADINGWINDOW_H
