#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->letterButtons = ui->letter_buttons_container->children();



    connect(ui->pushButton_letter_a, SIGNAL(released()), this, SLOT(letterPressed()));
    connect(ui->pushButton_letter_b, SIGNAL(released()), this, SLOT(letterPressed()));
    connect(ui->pushButton_letter_c, SIGNAL(released()), this, SLOT(letterPressed()));
    connect(ui->pushButton_letter_d, SIGNAL(released()), this, SLOT(letterPressed()));
    connect(ui->pushButton_letter_e, SIGNAL(released()), this, SLOT(letterPressed()));
    connect(ui->pushButton_letter_f, SIGNAL(released()), this, SLOT(letterPressed()));
    connect(ui->pushButton_letter_g, SIGNAL(released()), this, SLOT(letterPressed()));
    connect(ui->pushButton_letter_h, SIGNAL(released()), this, SLOT(letterPressed()));
    connect(ui->pushButton_letter_i, SIGNAL(released()), this, SLOT(letterPressed()));
    connect(ui->pushButton_letter_j, SIGNAL(released()), this, SLOT(letterPressed()));
    connect(ui->pushButton_letter_k, SIGNAL(released()), this, SLOT(letterPressed()));
    connect(ui->pushButton_letter_l, SIGNAL(released()), this, SLOT(letterPressed()));
    connect(ui->pushButton_letter_m, SIGNAL(released()), this, SLOT(letterPressed()));
    connect(ui->pushButton_letter_n, SIGNAL(released()), this, SLOT(letterPressed()));
    connect(ui->pushButton_letter_o, SIGNAL(released()), this, SLOT(letterPressed()));
    connect(ui->pushButton_letter_p, SIGNAL(released()), this, SLOT(letterPressed()));
    connect(ui->pushButton_letter_q, SIGNAL(released()), this, SLOT(letterPressed()));
    connect(ui->pushButton_letter_r, SIGNAL(released()), this, SLOT(letterPressed()));
    connect(ui->pushButton_letter_s, SIGNAL(released()), this, SLOT(letterPressed()));
    connect(ui->pushButton_letter_t, SIGNAL(released()), this, SLOT(letterPressed()));
    connect(ui->pushButton_letter_u, SIGNAL(released()), this, SLOT(letterPressed()));
    connect(ui->pushButton_letter_v, SIGNAL(released()), this, SLOT(letterPressed()));
    connect(ui->pushButton_letter_w, SIGNAL(released()), this, SLOT(letterPressed()));
    connect(ui->pushButton_letter_x, SIGNAL(released()), this, SLOT(letterPressed()));
    connect(ui->pushButton_letter_y, SIGNAL(released()), this, SLOT(letterPressed()));
    connect(ui->pushButton_letter_z, SIGNAL(released()), this, SLOT(letterPressed()));

    connect(ui->pushButton_select_letter, SIGNAL(released()), this, SLOT(letterSelected()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::letterPressed()
{
    //remove active class from all letter buttons
    for(int i=0; i < this->letterButtons.length(); i++){
        QPushButton* button = qobject_cast<QPushButton*>(this->letterButtons[i]);
        button->setProperty( "class", QString::fromStdString(""));
    }

    QPushButton* button = qobject_cast<QPushButton*>(sender()); //return a pointer to button that emitted event
    ui->label_player_name->setText(button->text());
    button->setProperty("class", "active");

    QWidget* container = ui->letter_buttons_container;
    container->setStyleSheet(container->styleSheet());
}

void MainWindow::letterSelected()
{
    QString letter;
    //get Selected letter
    QObjectList buttonList = ui->letter_buttons_container->children();
    for(int i=0; i<buttonList.length(); i++){
        if(buttonList[i]->property("class") == "active"){
            letter = (qobject_cast<QPushButton*>(buttonList[i]))->text();
        }
    }

    qDebug() << letter;

}
