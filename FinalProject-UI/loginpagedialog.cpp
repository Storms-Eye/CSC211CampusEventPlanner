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
    request.setRawHeader("X-User-ID", userId.toUtf8());
    request.setRawHeader("X-User-Pin", userPin.toUtf8());

    QByteArray info;
    QNetworkReply *reply = manager->post(request, info);

    connect(reply, &QNetworkReply::finished, this, [=](){
        if(reply->error() == QNetworkReply::NoError)
        {
            QByteArray responseData = reply->readAll();
            QJsonParseError parseError;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData, &parseError);

            if (parseError.error != QJsonParseError::NoError) {
                QMessageBox::warning(this, "Parse Error", "Received invalid data from server.");
                reply->deleteLater();
                return;
            }

            if (jsonDoc.isObject()) {
                QJsonObject jsonObj = jsonDoc.object();
                bool success = jsonObj["success"].toBool();

                if (success) {
                    int returnedId = jsonObj["user_id"].toInt();
                    QString name = jsonObj["name"].toString();
                    QString role = jsonObj["role"].toString();

                    user_id = userId;
                    user_name = name;
                    user_role = role;
                    user_pin = userPin;

                    QString welcomeMessage = QString("Welcome, %1! Your role is: %2").arg(name, role);
                    QMessageBox::information(this, "Login Approved", welcomeMessage, QMessageBox::Ok);

                    this->accept();
                } else {
                    QMessageBox::warning(this, "Login Failed", "Invalid credentials.");
                }
            }
        }
        else
        {
            QMessageBox::warning(this, "POST Failed", reply->errorString());
        }

        reply->deleteLater();
    });
}

QString LoginPageDialog::getUserID()
{
    return user_id;
}

QString LoginPageDialog::getPin()
{
    return user_pin;
}

QString LoginPageDialog::getUserRole()
{
    return user_role;
}

QString LoginPageDialog::getUserName()
{
    return user_name;
}
