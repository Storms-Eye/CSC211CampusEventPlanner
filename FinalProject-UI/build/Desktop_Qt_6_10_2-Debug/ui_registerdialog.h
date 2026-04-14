/********************************************************************************
** Form generated from reading UI file 'registerdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERDIALOG_H
#define UI_REGISTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_registerDialog
{
public:
    QPushButton *registerButton;
    QLabel *label;
    QLineEdit *pinInput;
    QLabel *label_2;
    QLineEdit *eventNameInput;

    void setupUi(QDialog *registerDialog)
    {
        if (registerDialog->objectName().isEmpty())
            registerDialog->setObjectName("registerDialog");
        registerDialog->resize(457, 344);
        registerButton = new QPushButton(registerDialog);
        registerButton->setObjectName("registerButton");
        registerButton->setGeometry(QRect(120, 210, 221, 71));
        QFont font;
        font.setPointSize(14);
        registerButton->setFont(font);
        label = new QLabel(registerDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 70, 181, 31));
        label->setFont(font);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        pinInput = new QLineEdit(registerDialog);
        pinInput->setObjectName("pinInput");
        pinInput->setGeometry(QRect(240, 70, 161, 31));
        label_2 = new QLabel(registerDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 130, 181, 41));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);
        eventNameInput = new QLineEdit(registerDialog);
        eventNameInput->setObjectName("eventNameInput");
        eventNameInput->setGeometry(QRect(240, 140, 161, 31));

        retranslateUi(registerDialog);

        QMetaObject::connectSlotsByName(registerDialog);
    } // setupUi

    void retranslateUi(QDialog *registerDialog)
    {
        registerDialog->setWindowTitle(QCoreApplication::translate("registerDialog", "Dialog", nullptr));
        registerButton->setText(QCoreApplication::translate("registerDialog", "Register for Event", nullptr));
        label->setText(QCoreApplication::translate("registerDialog", "Enter Student Pin:", nullptr));
        label_2->setText(QCoreApplication::translate("registerDialog", "Enter Event Name:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class registerDialog: public Ui_registerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERDIALOG_H
