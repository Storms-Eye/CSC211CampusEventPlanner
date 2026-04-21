#ifndef LOGINPAGEDIALOG_H
#define LOGINPAGEDIALOG_H

#include <QDialog>
#include <QNetworkAccessManager>

namespace Ui {
class LoginPageDialog;
}

class LoginPageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginPageDialog(QWidget *parent = nullptr);
    ~LoginPageDialog();
    QString getUserID();
    QString getUserRole();
    QString getUserName();
    QString getPin();

private slots:
    void on_loginButton_clicked();

private:
    Ui::LoginPageDialog *ui;
    QNetworkAccessManager *manager;

    QString user_id;
    QString user_role;
    QString user_name;
    QString user_pin;
signals:
    void loginResponse(const QString &response);
};

#endif // LOGINPAGEDIALOG_H
