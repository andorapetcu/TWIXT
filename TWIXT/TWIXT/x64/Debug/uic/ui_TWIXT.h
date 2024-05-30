/********************************************************************************
** Form generated from reading UI file 'TWIXT.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TWIXT_H
#define UI_TWIXT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TWIXTClass
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TWIXTClass)
    {
        if (TWIXTClass->objectName().isEmpty())
            TWIXTClass->setObjectName("TWIXTClass");
        TWIXTClass->resize(600, 400);
        centralWidget = new QWidget(TWIXTClass);
        centralWidget->setObjectName("centralWidget");
        TWIXTClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TWIXTClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 600, 22));
        TWIXTClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TWIXTClass);
        mainToolBar->setObjectName("mainToolBar");
        TWIXTClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(TWIXTClass);
        statusBar->setObjectName("statusBar");
        TWIXTClass->setStatusBar(statusBar);

        retranslateUi(TWIXTClass);

        QMetaObject::connectSlotsByName(TWIXTClass);
    } // setupUi

    void retranslateUi(QMainWindow *TWIXTClass)
    {
        TWIXTClass->setWindowTitle(QCoreApplication::translate("TWIXTClass", "TWIXT", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TWIXTClass: public Ui_TWIXTClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TWIXT_H
