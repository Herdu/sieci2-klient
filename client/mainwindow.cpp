#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
#include <unistd.h>

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
    if(this->isKeyboardBlocked){
        return;
    }

    this->resetKeyboard();

    QPushButton* button = qobject_cast<QPushButton*>(sender()); //return a pointer to button that emitted event
   button->setProperty("class", "active");

    QWidget* container = ui->letter_buttons_container;
    container->setStyleSheet(container->styleSheet());
}

void MainWindow::letterSelected()
{
    if(this->isKeyboardBlocked){
        return;
    }

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
    this->isKeyboardBlocked = true;
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
    connect(this->pSocket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(this->pSocket, SIGNAL(readyRead()),this, SLOT(readyRead()));


    this->pSocket->connectToHost(_address, _port);


        if(this->pSocket->waitForConnected(3000))
        {
            qDebug() << "Connected to server";
            sleep(1);
            this->writeData(SET_NICKNAME, nick);

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

        QString temp;

        if(data == nullptr){
            temp =  QString::fromStdString(to_string(command)) + ":;";
        }else{
            temp =  QString::fromStdString(to_string(command)) + ":" + data + ";";

        }

        temp =  QString::fromStdString(to_string(command)) + ":" + data + ";";
        qDebug() << "writing to buffer: " << temp;
        QByteArray _data = temp.toUtf8();


        this->pSocket->write(_data); //write the data itself
        //return this->pSocket->waitForBytesWritten();


    }
    else
        return false;
}


void MainWindow::disconnected()
{
    qDebug() << "disconnected...";
    exit(1);
}

void MainWindow::readyRead()
{
    qDebug() << "reading message from server";

    QString message;

    message = this->pSocket->readAll();

    QStringList splitted = message.split(";");

    for(int i=0; i<splitted.length(); i++){

        if(splitted[i] != ""){
            QStringList splitted2 = splitted[i].split(":");

            int len =  splitted2.length();

            int command;
            QString argument;

            if(len > 0){
                command = splitted2[0].toInt();
            }

            if(len > 1){
                argument = splitted2[1];
            }

            if(argument == ""){
                this->processMessage(command);
            }else{
                this->processMessage(command, argument);
            }
        }

    }

}

void MainWindow::processMessage(int command){
    auto cmd = static_cast<COMMAND>(command);

    switch(cmd){
    case END_OF_ROUND:
            qDebug() << "End of round";
        break;

    default:
            qDebug() << "Unknown command without argument";
        break;
    }




}
void MainWindow::processMessage(int command, QString argument){
    auto cmd = static_cast<COMMAND>(command);

    switch(cmd){
    case NEW_PASSWORD:
            qDebug() << "NEW PASSWORD: ";
            this->game.setNewPassword(argument);
            this->prepareNewGame();
        break;
    case SEND_MASK:
        this->game.setMask(argument);
        this->ui->label_password->setText(this->game.getPassword());
        break;

    case SEND_LETTER:
        this->hideLetter(argument);
        break;

    case NEXT_TOUR:
       qDebug() << "NEXT TOUR ";
       this->resetKeyboard();

       //remove active class from all letter buttons
       for(int i=0; i < this->letterButtons.length(); i++){
           QPushButton* button = qobject_cast<QPushButton*>(this->letterButtons[i]);
           button->setProperty( "class", QString::fromStdString(""));
           button->setStyleSheet("");
       }

       this->drawImage();
       this->isKeyboardBlocked = false;
        break;

    case SEND_ALPHABET:
        qDebug() << "Alphabet: " << argument;
        this->processAlphabet(argument);
        break;

    case SEND_PIECES:
        this->game.setPieces(argument.toInt());
        this->drawImage();
        break;
    default:

            qDebug() << "Unknown command: "<< cmd << " : " << argument;
        break;
    }

}

void MainWindow::prepareNewGame(){
   this->ui->label_password->setText(this->game.getPassword());

    for(int i=0; i < this->letterButtons.length(); i++){
        QPushButton* button = qobject_cast<QPushButton*>(this->letterButtons[i]);
        button->setVisible(true);
    }


   this->isKeyboardBlocked = false;
}


void MainWindow::init(){
    this->writeData(GET_PASSWORD, nullptr);
    this->drawImage();
}

void MainWindow::drawImage(){

    int num = this->game.getNumberOfPieces();
    QString url = "files/";
    url += QString::number(num);
    url += ".jpg";


    QPixmap img(url);
    this->ui->label_image->clear();
    this->ui->label_image->setPixmap(img);
}

void MainWindow::processAlphabet(QString data){

    char tab [] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p','q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    QStringList pieces = data.split( "," );

    if(pieces.length() <26 ){
        qDebug() << "Wrong alphabet data";
        return;
    }

    float  colors[26] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    float max = 0;

    for(int i=0; i<26; i++){
        float tmp = pieces[i].toFloat();
        colors[i] = tmp;
        if (tmp > 0){



            if(tmp > max){
                max = tmp;
            }
        }


    }


    for(int i=0; i<26; i++){
        string x;
        x+= tab[i];
        QString buttonName = "pushButton_letter_";
        QString buttonLetter = QString::fromStdString(x);
        QPushButton* button = ui->letter_buttons_container->findChild<QPushButton*>(buttonName+buttonLetter);

        if(colors[i] > 0){

            //stylesheet += QString::number();
            float color = 200 - (colors[i]/max) * 80;
            int iColor = (int)color;
            QColor qColor;
            qDebug() << iColor << ", ";
            qColor.setRgb(iColor, iColor, iColor);
            QString stylesheet = "background-color: "+ qColor.name() + ";";
            button->setStyleSheet(stylesheet);
        }else{
            if(colors[i] < 0){
                button->setVisible(false);
            }
        }


    }
}

void MainWindow::hideLetter(QString letter){
    if(letter.length() < 1){
        return;
    }
    QString buttonName = "pushButton_letter_";
    QPushButton* button = ui->letter_buttons_container->findChild<QPushButton*>(buttonName+letter);

    if(button){
        button->setVisible(false);
    }


}



