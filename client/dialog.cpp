#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QMovie* movie = new QMovie("loading.gif");
    if (!movie->isValid())
    {
        QtDebug() << 'smthing wrong';
    }

    QLabel* label = new QLabel(this);
    label->setMovie(movie);
    movie->start();

}

Dialog::~Dialog()
{
    delete ui;
}
