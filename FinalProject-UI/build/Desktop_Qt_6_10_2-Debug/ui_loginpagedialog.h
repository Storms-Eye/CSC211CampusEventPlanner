/********************************************************************************
** Form generated from reading UI file 'loginpagedialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINPAGEDIALOG_H
#define UI_LOGINPAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoginPageDialog
{
public:
    QLineEdit *idInput;
    QLineEdit *pinInput;
    QLabel *label;
    QLabel *label_2;
    QPushButton *loginButton;
    QComboBox *comboBox;

    void setupUi(QDialog *LoginPageDialog)
    {
        if (LoginPageDialog->objectName().isEmpty())
            LoginPageDialog->setObjectName("LoginPageDialog");
        LoginPageDialog->resize(400, 300);
        idInput = new QLineEdit(LoginPageDialog);
        idInput->setObjectName("idInput");
        idInput->setGeometry(QRect(190, 60, 113, 25));
        pinInput = new QLineEdit(LoginPageDialog);
        pinInput->setObjectName("pinInput");
        pinInput->setGeometry(QRect(190, 120, 113, 25));
        label = new QLabel(LoginPageDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(70, 60, 101, 31));
        QFont font;
        font.setPointSize(14);
        label->setFont(font);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_2 = new QLabel(LoginPageDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(80, 120, 91, 21));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);
        loginButton = new QPushButton(LoginPageDialog);
        loginButton->setObjectName("loginButton");
        loginButton->setGeometry(QRect(90, 190, 191, 61));
        loginButton->setFont(font);
        comboBox = new QComboBox(LoginPageDialog);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(290, 230, 71, 21));
        comboBox->setEditable(true);

        retranslateUi(LoginPageDialog);

        QMetaObject::connectSlotsByName(LoginPageDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginPageDialog)
    {
        LoginPageDialog->setWindowTitle(QCoreApplication::translate("LoginPageDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("LoginPageDialog", "User ID:", nullptr));
        label_2->setText(QCoreApplication::translate("LoginPageDialog", "Pin:", nullptr));
        loginButton->setText(QCoreApplication::translate("LoginPageDialog", "Login", nullptr));
        comboBox->setCurrentText(QCoreApplication::translate("LoginPageDialog", "charlie", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginPageDialog: public Ui_LoginPageDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINPAGEDIALOG_H
