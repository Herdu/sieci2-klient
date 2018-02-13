#include "loadingwindow.h"
#include "ui_loadingwindow.h"

LoadingWindow::LoadingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoadingWindow)
{
    ui->setupUi(this);
}

LoadingWindow::~LoadingWindow()
{
    delete ui;
}
