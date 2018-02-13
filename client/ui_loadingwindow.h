/********************************************************************************
** Form generated from reading UI file 'loadingwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADINGWINDOW_H
#define UI_LOADINGWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loadingWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *loadingWindow)
    {
        if (loadingWindow->objectName().isEmpty())
            loadingWindow->setObjectName(QString::fromUtf8("loadingWindow"));
        loadingWindow->resize(746, 320);
        centralwidget = new QWidget(loadingWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(30, 40, 99, 27));
        loadingWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(loadingWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 746, 25));
        loadingWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(loadingWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        loadingWindow->setStatusBar(statusbar);

        retranslateUi(loadingWindow);

        QMetaObject::connectSlotsByName(loadingWindow);
    } // setupUi

    void retranslateUi(QMainWindow *loadingWindow)
    {
        loadingWindow->setWindowTitle(QApplication::translate("loadingWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("loadingWindow", "PushButton", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class loadingWindow: public Ui_loadingWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADINGWINDOW_H
