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
    explicit registerDialog(QWidget *parent = nullptr);
    ~registerDialog();

private slots:
    void on_registerButton_clicked();

private:
    Ui::registerDialog *ui;
    QNetworkAccessManager *manager;
};

#endif // REGISTERDIALOG_H
