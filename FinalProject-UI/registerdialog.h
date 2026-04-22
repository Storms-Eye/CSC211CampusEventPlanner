#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QNetworkAccessManager>

namespace Ui {
class registerDialog;
}

class registerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit registerDialog(QWidget *parent = nullptr, const QString &userID = QString(), const QString &pin = QString());
    ~registerDialog();

private slots:
    void on_registerButton_clicked();

private:
    Ui::registerDialog *ui;
    QNetworkAccessManager *manager;
    QString userID;
    QString pin;
};

#endif // REGISTERDIALOG_H
