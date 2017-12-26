#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
#include <unistd.h>


QByteArray IntToArray(qint32 source) //Use qint32 to ensure that the number have 4 bytes
{
    //Avoid use of cast, this is the Qt way to serialize objects
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data << source;
    return temp;
}


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
    this->resetKeyboard();

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

    this->writeData(LETTER_VOTE, letter);

    this->resetKeyboard();

    qDebug() << letter;
}

void MainWindow::resetKeyboard()
{
    //remove active class from all letter buttons
    for(int i=0; i < this->letterButtons.length(); i++){
        QPushButton* button = qobject_cast<QPushButton*>(this->letterButtons[i]);
        button->setProperty( "class", QString::fromStdString(""));
    }

    QWidget* container = ui->letter_buttons_container;
    container->setStyleSheet(container->styleSheet());
}


bool MainWindow::connectTcp (QString address, QString port, QString nick)
{
    //convert port to quint16
    QTextStream ts(&port);
    quint16 num = 0;
    ts >> num;

    QHostAddress _address(address);
    quint16 _port(num);

    QByteArray data; // <-- fill with data
    this->pSocket = new QTcpSocket( this );
    connect( this->pSocket, SIGNAL(readyRead()), SLOT(readTcpData()));
    qDebug() << "przed polaczeniem";

    this->pSocket->connectToHost(_address, _port);


        if(this->pSocket->waitForConnected(3000))
        {
            qDebug() << "Connected!";
            sleep(1);
            qDebug() << "Nickname sent: "<< this->writeData(SET_NICKNAME, nick);

            return true;

        }
        else
        {
            qDebug() << "Not connected!";
            return false;
        }


}

void MainWindow::readTcpData()
{
    QByteArray data = this->pSocket->readAll();
    qDebug() << data;
}

bool MainWindow::writeData(COMMAND command, QString data)
{
    if(this->pSocket->state() == QAbstractSocket::ConnectedState)
    {

        QString temp, com;


        switch(command){
            case SET_NICKNAME:
                    com += "SET_NICKNAME:";
                break;

            case LETTER_VOTE:
                    com+= "LETTER_VOTE:";
                break;

            case PASSWORD_GUESS:
                    com+= "PASSWORD_GUESS:";
                break;

            default:
                qDebug() << "wrong command" <<endl;
                return false;
        }


        temp =  com + data + "\0";

        QByteArray _data = temp.toUtf8();


        //this->pSocket->write(IntToArray(_data.size())); //write size of data
        //this->pSocket->write(IntToArray(255)); //write size of data
        this->pSocket->write(_data); //write the data itself
        return this->pSocket->waitForBytesWritten();
    }
    else
        return false;
}



