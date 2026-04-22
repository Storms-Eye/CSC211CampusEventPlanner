#include "registerdialog.h"
#include "ui_registerdialog.h"
#include <QMessageBox>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>

registerDialog::registerDialog(QWidget *parent, const QString &userID, const QString &pin)
    : QDialog(parent)
    , ui(new Ui::registerDialog)
    , manager(new QNetworkAccessManager(this))
    , userID(userID)
    , pin(pin)
{
    ui->setupUi(this);
}

registerDialog::~registerDialog()
{
    delete ui;
}

void registerDialog::on_registerButton_clicked()
{
    QString eventID = ui->eventNameInput->text().trimmed();

    if (eventID.isEmpty())
    {
        QMessageBox::warning(this, "Missing Info", "Please enter an Event ID.");
        return;
    }

    QUrl url("http://localhost:18080/events/" + eventID + "/register");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("X-User-ID", userID.toUtf8());
    request.setRawHeader("X-User-Pin", pin.toUtf8());

    QNetworkReply *reply = manager->sendCustomRequest(request, "PATCH", QByteArray());

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError)
        {
            QMessageBox::information(this, "Success", "Successfully registered for event!");
            accept();
        }
        else
        {
            QByteArray responseData = reply->readAll();
            QString errMsg = responseData.isEmpty() ? reply->errorString() : QString(responseData);
            QMessageBox::warning(this, "Registration Failed", errMsg);
        }
        reply->deleteLater();
    });
}
