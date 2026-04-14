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

}

