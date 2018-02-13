#include "loading.h"
#include "ui_loading.h"

Loading::Loading(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Loading)
{
    ui->setupUi(this);
}

Loading::~Loading()
{
    delete ui;
}
