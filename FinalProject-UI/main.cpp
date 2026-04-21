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
        w.acceptCredentials(loginDialog.getUserID(), loginDialog.getPin(), loginDialog.getUserRole(), loginDialog.getUserName());
        w.show();
        return a.exec();
    }
}
