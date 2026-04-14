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

private slots:
    void on_loginButton_clicked();

private:
    Ui::LoginPageDialog *ui;
    QNetworkAccessManager *manager;
};

#endif // LOGINPAGEDIALOG_H
