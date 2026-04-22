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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *functionButton;
    QTextBrowser *outputBox;
    QPushButton *listButton;
    QLabel *roleLabel;
    QLabel *nameLabel;
    QPushButton *usersButton;
    QLabel *label;
    QRadioButton *allButton;
    QRadioButton *nameButton;
    QRadioButton *IDButton;
    QPlainTextEdit *inputBox;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(798, 712);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        functionButton = new QPushButton(centralwidget);
        functionButton->setObjectName("functionButton");
        functionButton->setGeometry(QRect(300, 600, 181, 51));
        QFont font;
        font.setPointSize(14);
        functionButton->setFont(font);
        outputBox = new QTextBrowser(centralwidget);
        outputBox->setObjectName("outputBox");
        outputBox->setGeometry(QRect(40, 210, 701, 361));
        listButton = new QPushButton(centralwidget);
        listButton->setObjectName("listButton");
        listButton->setGeometry(QRect(70, 60, 191, 51));
        listButton->setFont(font);
        roleLabel = new QLabel(centralwidget);
        roleLabel->setObjectName("roleLabel");
        roleLabel->setGeometry(QRect(240, 20, 121, 31));
        roleLabel->setFont(font);
        roleLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        nameLabel = new QLabel(centralwidget);
        nameLabel->setObjectName("nameLabel");
        nameLabel->setEnabled(true);
        nameLabel->setGeometry(QRect(370, 20, 401, 31));
        nameLabel->setFont(font);
        nameLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        usersButton = new QPushButton(centralwidget);
        usersButton->setObjectName("usersButton");
        usersButton->setGeometry(QRect(70, 130, 191, 51));
        usersButton->setFont(font);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(330, 70, 81, 31));
        label->setFont(font);
        allButton = new QRadioButton(centralwidget);
        allButton->setObjectName("allButton");
        allButton->setGeometry(QRect(330, 100, 95, 22));
        allButton->setChecked(true);
        nameButton = new QRadioButton(centralwidget);
        nameButton->setObjectName("nameButton");
        nameButton->setGeometry(QRect(330, 130, 95, 22));
        IDButton = new QRadioButton(centralwidget);
        IDButton->setObjectName("IDButton");
        IDButton->setGeometry(QRect(330, 160, 95, 22));
        inputBox = new QPlainTextEdit(centralwidget);
        inputBox->setObjectName("inputBox");
        inputBox->setGeometry(QRect(410, 70, 111, 111));
        inputBox->setFont(font);
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
        functionButton->setText(QCoreApplication::translate("MainWindow", "Function Button", nullptr));
        listButton->setText(QCoreApplication::translate("MainWindow", "View Events", nullptr));
        roleLabel->setText(QCoreApplication::translate("MainWindow", "Role:", nullptr));
        nameLabel->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        usersButton->setText(QCoreApplication::translate("MainWindow", "View Users", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Find  by", nullptr));
        allButton->setText(QCoreApplication::translate("MainWindow", "All", nullptr));
        nameButton->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        IDButton->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        inputBox->setPlaceholderText(QCoreApplication::translate("MainWindow", "Input", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
