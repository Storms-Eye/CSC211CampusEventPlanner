/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *eventIdInput;
    QLabel *label;
    QPushButton *approveButton;
    QPushButton *denyButton;
    QTextBrowser *textBrowser;
    QPushButton *listButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(798, 712);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        eventIdInput = new QLineEdit(centralwidget);
        eventIdInput->setObjectName("eventIdInput");
        eventIdInput->setGeometry(QRect(392, 40, 141, 31));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(210, 40, 141, 31));
        QFont font;
        font.setPointSize(14);
        label->setFont(font);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        approveButton = new QPushButton(centralwidget);
        approveButton->setObjectName("approveButton");
        approveButton->setGeometry(QRect(160, 110, 181, 51));
        approveButton->setFont(font);
        denyButton = new QPushButton(centralwidget);
        denyButton->setObjectName("denyButton");
        denyButton->setGeometry(QRect(400, 110, 181, 51));
        denyButton->setFont(font);
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(40, 270, 701, 361));
        listButton = new QPushButton(centralwidget);
        listButton->setObjectName("listButton");
        listButton->setGeometry(QRect(270, 190, 191, 51));
        listButton->setFont(font);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 798, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Enter Event ID:", nullptr));
        approveButton->setText(QCoreApplication::translate("MainWindow", "Approve Event", nullptr));
        denyButton->setText(QCoreApplication::translate("MainWindow", "Deny Event", nullptr));
        listButton->setText(QCoreApplication::translate("MainWindow", "List Events", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
