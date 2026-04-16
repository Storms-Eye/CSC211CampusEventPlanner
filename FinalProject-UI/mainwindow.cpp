#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonDocument>
#include <QJsonArray>
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
bool MainWindow::checkSort(const QJsonObject& obj)
{
    QString check = ui->identifierBox->toPlainText();
    if(ui->nameButton->isEnabled())
    {

        if(obj["name"] == check)
        {
            return true;
        }
        else return false;
    }
    else if(ui->IDButton->isEnabled())
    {
        if(obj["EventId"] == check)
        {
            return true;
        }
        else return false;
    }
    return true;
}
void MainWindow::on_listButton_clicked()
{
    QUrl url1("http://localhost:18080/approvedEvents");
    QUrl url2("http://localhost:18080/eventWaitList");
    QNetworkRequest request1(url1);
    QNetworkRequest request2(url2);
    request1.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request2.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");


    QString returnText = "";

    QNetworkReply *reply1 = manager->sendCustomRequest(request1, "GET"); //again, maybe json
    connect(reply1, &QNetworkReply::finished, this, [=]() mutable{
        if(reply1->error() == QNetworkReply::NoError)
        {
            QByteArray responseData = reply1->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
            if (jsonDoc.isArray()) {
                QJsonArray jsonArray = jsonDoc.array();
                for (const QJsonValue &value : jsonArray) {
                    if (value.isObject()) {
                        QJsonObject obj = value.toObject();
                        if(checkSort(obj))
                        {
                            returnText += obj["Name"].toString() + ", Capacity:  " + obj["Capacity"].toString() + ") ";
                            //if(role == "student") returnText += "[Approved] "
                            returnText += obj["Description"].toString() + "\n";
                            ui->outputBox->setPlainText(returnText);
                        }
                    }
                }
            }
        }
        else
        {
            QMessageBox::warning(this, "POST Failed", reply1->errorString());
        }
        reply1->deleteLater();
    });

 //   if(role.equals("student"))
  //  {
        QNetworkReply *reply2 = manager->sendCustomRequest(request2, "GET"); //again, maybe json
        connect(reply2, &QNetworkReply::finished, this, [=]() mutable{
            if(reply2->error() == QNetworkReply::NoError){
                QByteArray responseData2 = reply2->readAll();
                QJsonDocument jsonDoc2 = QJsonDocument::fromJson(responseData2);
                if (jsonDoc2.isArray()) {
                    QJsonArray jsonArray2 = jsonDoc2.array();
                    for (const QJsonValue &value : jsonArray2) {
                        if (value.isObject()) {
                            QJsonObject obj = value.toObject();
                            if(checkSort(obj))
                            {
                                returnText += obj["Name"].toString() + ", Capacity:  " + obj["Capacity"].toString() + ") [In Queue] " +  obj["Description"].toString() + "\n";

                            }
                        }
                    }
                }

            }
            else
            {
                QMessageBox::warning(this, "POST Failed", reply2->errorString());
            }
            reply2->deleteLater();
        });

  //  }

        return;

}

