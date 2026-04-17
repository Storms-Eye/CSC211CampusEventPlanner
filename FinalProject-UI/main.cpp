#include "mainwindow.h"
#include "loginpagedialog.h"

#include <QApplication>
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginPageDialog loginDialog;
    MainWindow w;

    if (loginDialog.exec() == QDialog::Accepted)
    {
        // userID and pin will be acquired from what is entered into their respective fields
        QString userID = loginDialog.getUserID();
        QString pin = loginDialog.getPin();
        // we also declare the name and role that we will use later
        QString name;
        QString role;

        // we want to read from the user.json file so that when we log in, we will display name, ID, and role
        // first, check if the user.json file exists
        QFile file("user.json");
        if (!file.open(QIODevice::ReadOnly))
        {
            qDebug() << "Failed to open file";
            return 0;
        }

        // next, read all the information from the file and then close it.
        QByteArray data = file.readAll();
        file.close();

        // Save the data into a QJsonDocument object, then save to an array of users
        // essentially the opposite of the AddItemDialog process from MainWindow
        // instead of writing to the document, we are reading from the document
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonArray users = doc.array();

        // use what userID and pin was entered to retreive the appropriate information from user.json
        for (const QJsonValue &value : users)
        {
            QJsonObject obj = value.toObject();

            if (obj["id"].toString() == userID && obj["pin"].toString() == pin)
            {
                name = obj["name"].toString();
                role = obj["role"].toString();

                // check if the user is the student
                if (role == "student")
                {
                    QMessageBox::information(&loginDialog, "Login", "Logged in user: " + name + "\nUser ID: " + userID + "\nRole: " + role, QMessageBox::Ok);
                    w.acceptCredentials(userID, pin, role, name);
                    w.show();
                    return a.exec();
                }
                // check if the user is the faculty member
                else if (role == "faculty")
                {
                    QMessageBox::information(&loginDialog, "Login", "Logged in user: " + name + "\nUser ID: " + userID + "\nRole: " + role, QMessageBox::Ok);
                    w.acceptCredentials(userID, pin, role, name);
                    w.show();
                    return a.exec();
                }
                // check if the user is the admin
                else if (role == "admin")
                {
                    QMessageBox::information(&loginDialog, "Login", "Logged in user: " + name + "\nUser ID: " + userID + "\nRole: " + role, QMessageBox::Ok);
                    w.acceptCredentials(userID, pin, role, name);
                    w.show();
                    return a.exec();
                }
            }
        }
    return a.exec();
    }
}
