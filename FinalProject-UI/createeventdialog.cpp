#include "createeventdialog.h"
#include "ui_createeventdialog.h"
#include "mainwindow.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QMessageBox>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <QJsonObject>
CreateEventDialog::CreateEventDialog(QWidget *parent, const QString &userID, const QString &pin)
    : QDialog(parent)
    , ui(new Ui::CreateEventDialog)
    , manager(new QNetworkAccessManager(this))
    , userID(userID)
    , pin(pin)
{
    ui->setupUi(this);
}

CreateEventDialog::~CreateEventDialog()
{
    delete ui;
}

void CreateEventDialog::on_eventSubmitButton_clicked()
{
    QUrl url("http://localhost:18080/createEvent");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("X-User-ID", userID.toUtf8());
    request.setRawHeader("X-User-Pin", pin.toUtf8());
    QJsonObject event_event;
    event_event["name"] = ui->nameInput->toPlainText();
    event_event["capacity"] = ui->capacityInput->toPlainText().toInt();
    event_event["description"] = ui->descriptionInput->toPlainText();
    event_event["user_id"] = userID.toInt();
    event_event["date"] = ui->dateInput->toPlainText();
    QByteArray body = QJsonDocument(event_event).toJson();
    QNetworkReply *reply = manager->post(request, body);
    connect(reply, &QNetworkReply::finished, this, [=]() {
        if(reply->error() == QNetworkReply::NoError)
        {
            QMessageBox::information(this, "Success", "Event Created, Waiting for Approval");
            accept();
        }
        else
        {
            QMessageBox::warning(this, "GET Approved Failed", reply->errorString());
            close();
        }
        reply->deleteLater();
    });
}

