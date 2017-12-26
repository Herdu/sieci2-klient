/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label_player_name;
    QLabel *label_2;
    QPushButton *pushButton_select_letter;
    QWidget *letter_buttons_container;
    QPushButton *pushButton_letter_z;
    QPushButton *pushButton_letter_n;
    QPushButton *pushButton_letter_y;
    QPushButton *pushButton_letter_d;
    QPushButton *pushButton_letter_h;
    QPushButton *pushButton_letter_f;
    QPushButton *pushButton_letter_q;
    QPushButton *pushButton_letter_m;
    QPushButton *pushButton_letter_r;
    QPushButton *pushButton_letter_s;
    QPushButton *pushButton_letter_c;
    QPushButton *pushButton_letter_i;
    QPushButton *pushButton_letter_t;
    QPushButton *pushButton_letter_a;
    QPushButton *pushButton_letter_w;
    QPushButton *pushButton_letter_o;
    QPushButton *pushButton_letter_k;
    QPushButton *pushButton_letter_u;
    QPushButton *pushButton_letter_l;
    QPushButton *pushButton_letter_g;
    QPushButton *pushButton_letter_b;
    QPushButton *pushButton_letter_x;
    QPushButton *pushButton_letter_p;
    QPushButton *pushButton_letter_v;
    QPushButton *pushButton_letter_j;
    QPushButton *pushButton_letter_e;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(960, 540);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(960, 540));
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label_player_name = new QLabel(centralWidget);
        label_player_name->setObjectName(QString::fromUtf8("label_player_name"));
        label_player_name->setGeometry(QRect(370, 10, 131, 21));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(150, 60, 67, 17));
        pushButton_select_letter = new QPushButton(centralWidget);
        pushButton_select_letter->setObjectName(QString::fromUtf8("pushButton_select_letter"));
        pushButton_select_letter->setGeometry(QRect(130, 400, 221, 31));
        letter_buttons_container = new QWidget(centralWidget);
        letter_buttons_container->setObjectName(QString::fromUtf8("letter_buttons_container"));
        letter_buttons_container->setGeometry(QRect(10, 160, 451, 211));
        letter_buttons_container->setStyleSheet(QString::fromUtf8("#letter_buttons_container{\n"
"	background-color: gray;\n"
"}\n"
"\n"
"#letter_buttons_container  *{\n"
"	background-color: yellow;\n"
"}\n"
"\n"
"#letter_buttons_container *[class=\"active\"]{\n"
"	border: 5px solid blue;\n"
"}"));
        pushButton_letter_z = new QPushButton(letter_buttons_container);
        pushButton_letter_z->setObjectName(QString::fromUtf8("pushButton_letter_z"));
        pushButton_letter_z->setGeometry(QRect(230, 160, 40, 40));
        pushButton_letter_n = new QPushButton(letter_buttons_container);
        pushButton_letter_n->setObjectName(QString::fromUtf8("pushButton_letter_n"));
        pushButton_letter_n->setGeometry(QRect(280, 60, 40, 40));
        pushButton_letter_y = new QPushButton(letter_buttons_container);
        pushButton_letter_y->setObjectName(QString::fromUtf8("pushButton_letter_y"));
        pushButton_letter_y->setGeometry(QRect(180, 160, 40, 40));
        pushButton_letter_d = new QPushButton(letter_buttons_container);
        pushButton_letter_d->setObjectName(QString::fromUtf8("pushButton_letter_d"));
        pushButton_letter_d->setGeometry(QRect(180, 10, 40, 40));
        pushButton_letter_h = new QPushButton(letter_buttons_container);
        pushButton_letter_h->setObjectName(QString::fromUtf8("pushButton_letter_h"));
        pushButton_letter_h->setGeometry(QRect(380, 10, 40, 40));
        pushButton_letter_f = new QPushButton(letter_buttons_container);
        pushButton_letter_f->setObjectName(QString::fromUtf8("pushButton_letter_f"));
        pushButton_letter_f->setGeometry(QRect(280, 10, 40, 40));
        pushButton_letter_q = new QPushButton(letter_buttons_container);
        pushButton_letter_q->setObjectName(QString::fromUtf8("pushButton_letter_q"));
        pushButton_letter_q->setGeometry(QRect(30, 110, 40, 40));
        pushButton_letter_m = new QPushButton(letter_buttons_container);
        pushButton_letter_m->setObjectName(QString::fromUtf8("pushButton_letter_m"));
        pushButton_letter_m->setGeometry(QRect(230, 60, 40, 40));
        pushButton_letter_r = new QPushButton(letter_buttons_container);
        pushButton_letter_r->setObjectName(QString::fromUtf8("pushButton_letter_r"));
        pushButton_letter_r->setGeometry(QRect(80, 110, 40, 40));
        pushButton_letter_s = new QPushButton(letter_buttons_container);
        pushButton_letter_s->setObjectName(QString::fromUtf8("pushButton_letter_s"));
        pushButton_letter_s->setGeometry(QRect(130, 110, 40, 40));
        pushButton_letter_c = new QPushButton(letter_buttons_container);
        pushButton_letter_c->setObjectName(QString::fromUtf8("pushButton_letter_c"));
        pushButton_letter_c->setGeometry(QRect(130, 10, 40, 40));
        pushButton_letter_i = new QPushButton(letter_buttons_container);
        pushButton_letter_i->setObjectName(QString::fromUtf8("pushButton_letter_i"));
        pushButton_letter_i->setGeometry(QRect(30, 60, 40, 40));
        pushButton_letter_t = new QPushButton(letter_buttons_container);
        pushButton_letter_t->setObjectName(QString::fromUtf8("pushButton_letter_t"));
        pushButton_letter_t->setGeometry(QRect(180, 110, 40, 40));
        pushButton_letter_a = new QPushButton(letter_buttons_container);
        pushButton_letter_a->setObjectName(QString::fromUtf8("pushButton_letter_a"));
        pushButton_letter_a->setGeometry(QRect(30, 10, 40, 40));
        pushButton_letter_w = new QPushButton(letter_buttons_container);
        pushButton_letter_w->setObjectName(QString::fromUtf8("pushButton_letter_w"));
        pushButton_letter_w->setGeometry(QRect(330, 110, 40, 40));
        pushButton_letter_o = new QPushButton(letter_buttons_container);
        pushButton_letter_o->setObjectName(QString::fromUtf8("pushButton_letter_o"));
        pushButton_letter_o->setGeometry(QRect(330, 60, 40, 40));
        pushButton_letter_k = new QPushButton(letter_buttons_container);
        pushButton_letter_k->setObjectName(QString::fromUtf8("pushButton_letter_k"));
        pushButton_letter_k->setGeometry(QRect(130, 60, 40, 40));
        pushButton_letter_u = new QPushButton(letter_buttons_container);
        pushButton_letter_u->setObjectName(QString::fromUtf8("pushButton_letter_u"));
        pushButton_letter_u->setGeometry(QRect(230, 110, 40, 40));
        pushButton_letter_l = new QPushButton(letter_buttons_container);
        pushButton_letter_l->setObjectName(QString::fromUtf8("pushButton_letter_l"));
        pushButton_letter_l->setGeometry(QRect(180, 60, 40, 40));
        pushButton_letter_g = new QPushButton(letter_buttons_container);
        pushButton_letter_g->setObjectName(QString::fromUtf8("pushButton_letter_g"));
        pushButton_letter_g->setGeometry(QRect(330, 10, 40, 40));
        pushButton_letter_b = new QPushButton(letter_buttons_container);
        pushButton_letter_b->setObjectName(QString::fromUtf8("pushButton_letter_b"));
        pushButton_letter_b->setGeometry(QRect(80, 10, 40, 40));
        pushButton_letter_x = new QPushButton(letter_buttons_container);
        pushButton_letter_x->setObjectName(QString::fromUtf8("pushButton_letter_x"));
        pushButton_letter_x->setGeometry(QRect(380, 110, 40, 40));
        pushButton_letter_p = new QPushButton(letter_buttons_container);
        pushButton_letter_p->setObjectName(QString::fromUtf8("pushButton_letter_p"));
        pushButton_letter_p->setGeometry(QRect(380, 60, 40, 40));
        pushButton_letter_v = new QPushButton(letter_buttons_container);
        pushButton_letter_v->setObjectName(QString::fromUtf8("pushButton_letter_v"));
        pushButton_letter_v->setGeometry(QRect(280, 110, 40, 40));
        pushButton_letter_j = new QPushButton(letter_buttons_container);
        pushButton_letter_j->setObjectName(QString::fromUtf8("pushButton_letter_j"));
        pushButton_letter_j->setGeometry(QRect(80, 60, 40, 40));
        pushButton_letter_e = new QPushButton(letter_buttons_container);
        pushButton_letter_e->setObjectName(QString::fromUtf8("pushButton_letter_e"));
        pushButton_letter_e->setGeometry(QRect(230, 10, 40, 40));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 960, 25));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        label_player_name->setText(QApplication::translate("MainWindow", "Player name", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "label2", 0, QApplication::UnicodeUTF8));
        pushButton_select_letter->setText(QApplication::translate("MainWindow", "Wybierz", 0, QApplication::UnicodeUTF8));
        pushButton_letter_z->setText(QApplication::translate("MainWindow", "Z", 0, QApplication::UnicodeUTF8));
        pushButton_letter_n->setText(QApplication::translate("MainWindow", "N", 0, QApplication::UnicodeUTF8));
        pushButton_letter_y->setText(QApplication::translate("MainWindow", "Y", 0, QApplication::UnicodeUTF8));
        pushButton_letter_d->setText(QApplication::translate("MainWindow", "D", 0, QApplication::UnicodeUTF8));
        pushButton_letter_h->setText(QApplication::translate("MainWindow", "H", 0, QApplication::UnicodeUTF8));
        pushButton_letter_f->setText(QApplication::translate("MainWindow", "F", 0, QApplication::UnicodeUTF8));
        pushButton_letter_q->setText(QApplication::translate("MainWindow", "Q", 0, QApplication::UnicodeUTF8));
        pushButton_letter_m->setText(QApplication::translate("MainWindow", "M", 0, QApplication::UnicodeUTF8));
        pushButton_letter_r->setText(QApplication::translate("MainWindow", "R", 0, QApplication::UnicodeUTF8));
        pushButton_letter_s->setText(QApplication::translate("MainWindow", "S", 0, QApplication::UnicodeUTF8));
        pushButton_letter_c->setText(QApplication::translate("MainWindow", "C", 0, QApplication::UnicodeUTF8));
        pushButton_letter_i->setText(QApplication::translate("MainWindow", "I", 0, QApplication::UnicodeUTF8));
        pushButton_letter_t->setText(QApplication::translate("MainWindow", "T", 0, QApplication::UnicodeUTF8));
        pushButton_letter_a->setText(QApplication::translate("MainWindow", "A", 0, QApplication::UnicodeUTF8));
        pushButton_letter_w->setText(QApplication::translate("MainWindow", "W", 0, QApplication::UnicodeUTF8));
        pushButton_letter_o->setText(QApplication::translate("MainWindow", "O", 0, QApplication::UnicodeUTF8));
        pushButton_letter_k->setText(QApplication::translate("MainWindow", "K", 0, QApplication::UnicodeUTF8));
        pushButton_letter_u->setText(QApplication::translate("MainWindow", "U", 0, QApplication::UnicodeUTF8));
        pushButton_letter_l->setText(QApplication::translate("MainWindow", "L", 0, QApplication::UnicodeUTF8));
        pushButton_letter_g->setText(QApplication::translate("MainWindow", "G", 0, QApplication::UnicodeUTF8));
        pushButton_letter_b->setText(QApplication::translate("MainWindow", "B", 0, QApplication::UnicodeUTF8));
        pushButton_letter_x->setText(QApplication::translate("MainWindow", "X", 0, QApplication::UnicodeUTF8));
        pushButton_letter_p->setText(QApplication::translate("MainWindow", "P", 0, QApplication::UnicodeUTF8));
        pushButton_letter_v->setText(QApplication::translate("MainWindow", "V", 0, QApplication::UnicodeUTF8));
        pushButton_letter_j->setText(QApplication::translate("MainWindow", "J", 0, QApplication::UnicodeUTF8));
        pushButton_letter_e->setText(QApplication::translate("MainWindow", "E", 0, QApplication::UnicodeUTF8));
        pushButton_letter_e->setProperty("class", QVariant(QString()));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
