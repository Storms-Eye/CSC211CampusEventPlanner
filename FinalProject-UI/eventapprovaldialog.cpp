#include "eventapprovaldialog.h"
#include "ui_eventapprovaldialog.h"
#include "mainwindow.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QMessageBox>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <QJsonObject>
EventApprovalDialog::EventApprovalDialog(QWidget *parent, const QString &userID, const QString &pin)
    : QDialog(parent)
    , ui(new Ui::EventApprovalDialog)
    , manager(new QNetworkAccessManager(this))
    , userID(userID)
    , pin(pin)
{
    ui->setupUi(this);
}

EventApprovalDialog::~EventApprovalDialog()
{
    delete ui;
}

void EventApprovalDialog::on_approveButton_clicked()
{

    QJsonObject approved_event;
    approved_event["approved"] = true;
    approved_event["user_id"] = userID;
    approved_event["pin"] = pin;
    QByteArray body = QJsonDocument(approved_event).toJson();
    QUrl url("http://localhost:18080/events/" + QString::number(ui->idInput->toPlainText().toInt()));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("X-User-ID", userID.toUtf8());
    request.setRawHeader("X-User-Pin", pin.toUtf8());
    QNetworkReply *reply = manager->sendCustomRequest(request, "PATCH", body);
    connect(reply, &QNetworkReply::finished, this, [=]() {
        if(reply->error() == QNetworkReply::NoError)
        {
            QMessageBox::information(this, "Success", "Event Approved");
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


void EventApprovalDialog::on_denyButton_clicked()
{

    QJsonObject denied_event;
    denied_event["user_id"] = userID;
    denied_event["pin"] = pin;
    denied_event["approved"] = false;
    QByteArray body = QJsonDocument(denied_event).toJson();
    QUrl url("http://localhost:18080/events/" + QString::number(ui->idInput->toPlainText().toInt()));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("X-User-ID", userID.toUtf8());
    request.setRawHeader("X-User-Pin", pin.toUtf8());
    QNetworkReply *reply = manager->sendCustomRequest(request, "PATCH", body);
    connect(reply, &QNetworkReply::finished, this, [=]() {
        if(reply->error() == QNetworkReply::NoError)
        {
            QMessageBox::information(this, "Success", "Event Approved");
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

