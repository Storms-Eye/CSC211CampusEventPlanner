#include "loginpagedialog.h"
#include "ui_loginpagedialog.h"

#include <QMessageBox>
#include <QJsonDocument>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <QJsonObject>

LoginPageDialog::LoginPageDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginPageDialog)
    , manager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);
}

LoginPageDialog::~LoginPageDialog()
{
    delete ui;
}

void LoginPageDialog::on_loginButton_clicked()
{
    QString userId = ui->idInput->text().trimmed();
    QString userPin = ui->pinInput->text().trimmed();

    if(userId.isEmpty())
    {
        QMessageBox::warning(this, "No ID Given", "Please enter your user ID");
        return;
    }
    if(userPin.isEmpty())
    {
        QMessageBox::warning(this, "No PIN Given", "Please enter your user PIN");
        return;
    }
    QUrl url("http://localhost:18080/login");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject obj;
    obj["userId"] = userId;
    obj["pin"] = userPin;
    QJsonDocument doc(obj);
    QByteArray data = doc.toJson();

    QNetworkReply *reply = manager->sendCustomRequest(request, "POST", data);

    connect(reply, &QNetworkReply::finished, this, [=](){
        if(reply->error() == QNetworkReply::NoError)
        {
            QMessageBox::information(this, "Login Approved", "Login successful", QMessageBox::Ok);
            return;
        }
        else
        {
            QMessageBox::warning(this, "GET Failed", reply->errorString());
        }
        reply->deleteLater();
    });
}

