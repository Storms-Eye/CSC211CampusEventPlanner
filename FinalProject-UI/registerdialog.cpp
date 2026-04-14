#include "registerdialog.h"
#include "ui_registerdialog.h"

#include <QMessageBox>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <QJsonObject>

registerDialog::registerDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::registerDialog)
    , manager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);
}

registerDialog::~registerDialog()
{
    delete ui;
}

void registerDialog::on_registerButton_clicked()
{
    QString studentPin = ui->pinInput->text().trimmed();
}

