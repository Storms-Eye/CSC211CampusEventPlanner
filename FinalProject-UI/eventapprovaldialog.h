#ifndef EVENTAPPROVALDIALOG_H
#define EVENTAPPROVALDIALOG_H

#include <QDialog>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QNetworkAccessManager>

namespace Ui {
class EventApprovalDialog;
}

class EventApprovalDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EventApprovalDialog(QWidget *parent = nullptr, const QString &userID = QString(), const QString &pin = QString());
    ~EventApprovalDialog();

private slots:
    void on_approveButton_clicked();

    void on_denyButton_clicked();

private:
    Ui::EventApprovalDialog *ui;
    QNetworkAccessManager *manager;
    QString userID;
    QString pin;
};

#endif // EVENTAPPROVALDIALOG_H
