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
    
    ui->roleLabel->setText(role + ":");
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

    if(role != "admin")
    {
        ui->usersButton->setVisible(false);
    }
}

bool MainWindow::checkSort(const QJsonObject& obj)
{
    QString check = ui->inputBox->toPlainText().trimmed();
    if(ui->allButton->isChecked() || check.isEmpty())
    {
        return true;
    }

    if(ui->nameButton->isChecked())
    {
        if(obj["Name"].toString() == check)
        {
            return true;
        }
        return false;
    }
    else if(ui->IDButton->isChecked())
    {
        if(QString::number(obj["EventId"].toInt()) == check)
        {
            return true;
        }
        return false;
    }
    return true;
}

void MainWindow::on_listButton_clicked()
{
    ui->outputBox->clear();

    QUrl url1("http://localhost:18080/approvedEvents");
    QNetworkRequest request1(url1);
    request1.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request1.setRawHeader("X-User-ID", userID.toUtf8());
    request1.setRawHeader("X-User-Pin", pin.toUtf8());

    QNetworkReply *reply1 = manager->get(request1);
    connect(reply1, &QNetworkReply::finished, this, [=]() {
        if(reply1->error() == QNetworkReply::NoError)
        {
            QByteArray responseData = reply1->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);

            QString approvedText = "";

            if (jsonDoc.isArray()) {
                QJsonArray jsonArray = jsonDoc.array();
                for (const QJsonValue &value : jsonArray) {
                    if (value.isObject()) {
                        QJsonObject obj = value.toObject();
                        if(checkSort(obj))
                        {
                            approvedText += obj["Name"].toString() + ", Capacity:  " + QString::number(obj["Capacity"].toInt()) + ", ";
                            if(!(role == "student")) approvedText += "[Approved],  ";
                            approvedText += obj["Description"].toString() + ", ID: " + QString::number(obj["EventId"].toInt()) + "\n";
                        }
                    }
                }
            }
            ui->outputBox->setPlainText(approvedText);
        }
        else
        {
            QMessageBox::warning(this, "GET Approved Failed", reply1->errorString());
        }

        if(role != "student")
        {
            QUrl url2("http://localhost:18080/eventWaitlist");
            QNetworkRequest request2(url2);
            request2.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
            request2.setRawHeader("X-User-ID", userID.toUtf8());
            request2.setRawHeader("X-User-Pin", pin.toUtf8());

            QNetworkReply *reply2 = manager->get(request2);
            connect(reply2, &QNetworkReply::finished, this, [=]() {
                if(reply2->error() == QNetworkReply::NoError)
                {
                    QString waitlistText = "";
                    QByteArray responseData2 = reply2->readAll();
                    QJsonDocument jsonDoc2 = QJsonDocument::fromJson(responseData2);

                    if (jsonDoc2.isArray()) {
                        QJsonArray jsonArray2 = jsonDoc2.array();
                        for (const QJsonValue &value : jsonArray2) {
                            if (value.isObject()) {
                                QJsonObject obj = value.toObject();
                                if(checkSort(obj))
                                {
                                    waitlistText += obj["Name"].toString() + ", Capacity:  " + QString::number(obj["Capacity"].toInt()) + ", [In Queue], " +  obj["Description"].toString() + ", ID: " + QString::number(obj["EventId"].toInt()) + "\n";
                                }
                            }
                        }
                    }
                    ui->outputBox->append(waitlistText);
                }
                else
                {
                    QMessageBox::warning(this, "GET Waitlist Failed", reply2->errorString());
                }
                reply2->deleteLater();
            });
        }
        reply1->deleteLater();
    });
}

void MainWindow::on_functionButton_clicked()
{
    // these dialogs/classes have not been created yet
    if (role == "student")
    {
        registerDialog r;
        r.exec();
    }
    else if (role == "moderator")
    {
        CreateEventDialog c;
        c.exec();
    }
    else if (role == "admin")
    {
        EventApprovalDialog e;
        e.exec();
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

