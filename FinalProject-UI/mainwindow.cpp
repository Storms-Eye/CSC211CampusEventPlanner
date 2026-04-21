#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginpagedialog.h"
#include "registerdialog.h"
#include "eventapprovaldialog.h"
#include "createeventdialog.h"
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

void MainWindow::acceptCredentials(const QString &acceptedID, const QString &acceptedPin, const QString &acceptedRole, const QString &acceptedName)
{
    userID = acceptedID;
    pin = acceptedPin;
    role = acceptedRole;
    name = acceptedName;
    
    ui->roleLabel->setText(role);
    ui->nameLabel->setText(name);
    
    if (role == "student")
    {
        ui->functionButton->setText("Register for Event");
    }
    else if (role == "moderator")
    {
        ui->functionButton->setText("Create Event");
    }
    else if (role == "admin")
    {
        ui->functionButton->setText("Approve/Deny Event");
    }
}

bool MainWindow::checkSort(const QJsonObject& obj)
{
    QString check = ui->outputBox->toPlainText();
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

    if(!(role == "student"))
    {
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

    }
        return;
}

void MainWindow::on_functionButton_clicked()
{
    // these dialogs/classes have not been created yet
    if (role == "student")
    {
        registerDialog r;
        r.show();
    }
    else if (role == "moderator")
    {
        CreateEventDialog c;
        c.show();
    }
    else if (role == "admin")
    {
        EventApprovalDialog e;
        e.show();
    }
}

void MainWindow::on_usersButton_clicked()
{
    //if admin, display all users
    //if student, display current user
}

void MainWindow::on_allButton_clicked()
{
    ui->allButton->setChecked(true);
    ui->nameButton->setChecked(false);
    ui->IDButton->setChecked(false);
}


void MainWindow::on_nameButton_clicked()
{
    ui->allButton->setChecked(false);
    ui->nameButton->setChecked(true);
    ui->IDButton->setChecked(false);
}


void MainWindow::on_IDButton_clicked()
{
    ui->allButton->setChecked(false);
    ui->nameButton->setChecked(false);
    ui->IDButton->setChecked(true);
}

