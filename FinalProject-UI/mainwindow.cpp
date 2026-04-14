#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <QJsonObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , manager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_approveButton_clicked()
{
    bool isApproved = true;
    QString eventIdText = ui->eventIdInput->text().trimmed();

    if(eventIdText.isEmpty())
    {
        QMessageBox::warning(this, "No ID Given", "Please enter an event ID");
        return;
    }
    QUrl url("http://localhost:18080/events/" + eventIdText);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject obj;
    obj["isApproved"] = isApproved;
    QJsonDocument doc(obj);
    QByteArray data = doc.toJson();

    QNetworkReply *reply = manager->sendCustomRequest(request, "POST", data);

    connect(reply, &QNetworkReply::finished, this, [=](){
        if(reply->error() == QNetworkReply::NoError)
        {
            QMessageBox::information(this, "Event Approved", "Event has been added to list of approved events", QMessageBox::Ok);
            return;
        }
        else
        {
            QMessageBox::warning(this, "POST Failed", reply->errorString());
        }
        reply->deleteLater();
    });
}


void MainWindow::on_denyButton_clicked()
{
    bool isApproved = false;
    QString eventIdText = ui->eventIdInput->text().trimmed();

    if(eventIdText.isEmpty())
    {
        QMessageBox::warning(this, "No ID Given", "Please enter an event ID");
        return;
    }
    QUrl url("http://localhost:18080/register/" + eventIdText);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject obj;
    obj["isApproved"] = isApproved;
    QJsonDocument doc(obj);
    QByteArray data = doc.toJson();

    QNetworkReply *reply = manager->sendCustomRequest(request, "POST", data);

    connect(reply, &QNetworkReply::finished, this, [=](){
        if(reply->error() == QNetworkReply::NoError)
        {
            QMessageBox::information(this, "Event Denied", "Event has been added to event history", QMessageBox::Ok);
            return;
        }
        else
        {
            QMessageBox::warning(this, "POST Failed", reply->errorString());
        }
        reply->deleteLater();
    });
}


void MainWindow::on_listButton_clicked()
{
    QUrl url("http://localhost:18080/isAdmin");
    QUrl url1("http://localhost:18080/approvedEvents");
    QUrl url2("http://localhost:18080/eventWaitList");
    QNetworkRequest request(url);
    QNetworkRequest request1(url1);
    QNetworkRequest request2(url2);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request1.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request2.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->sendCustomRequest(request, "GET", data); //maybe this is a json object, I lost my folder that contained this... I don't know how. This happens a lot. Hopefully it's fixed when I removed all the excess files from my root folder.

    connect(reply, &QNetworkReply::finished, this, [=](){
        if(reply->error() == QNetworkReply::NoError)
        {

            return;
        }
        else
        {
            QMessageBox::warning(this, "POST Failed", reply->errorString());
        }
        reply->deleteLater();
    });
    QNetworkReply *reply1 = manager->sendCustomRequest(request1, "GET", data); //again, maybe json
    connect(reply1, &QNetworkReply::finished, this, [=](){
        if(reply1->error() == QNetworkReply::NoError)
        {
            ui->textBrowser->text() = "HI";//json object goes here
            return;
        }
        else
        {
            QMessageBox::warning(this, "POST Failed", reply->errorString());
        }
        reply->deleteLater();
    });
    QNetworkReply *reply2 = manager->sendCustomRequest(request2, "GET", data); //again, maybe json




}

