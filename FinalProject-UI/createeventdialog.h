#ifndef CREATEEVENTDIALOG_H
#define CREATEEVENTDIALOG_H

#include <QDialog>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QNetworkAccessManager>
namespace Ui {
class CreateEventDialog;
}

class CreateEventDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateEventDialog(QWidget *parent = nullptr, const QString &userID = QString(), const QString &pin = QString());
    ~CreateEventDialog();

private slots:
    void on_eventSubmitButton_clicked();

private:
    Ui::CreateEventDialog *ui;
    QNetworkAccessManager *manager;
    QString userID;
    QString pin;
};

#endif // CREATEEVENTDIALOG_H
