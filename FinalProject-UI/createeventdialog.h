#ifndef CREATEEVENTDIALOG_H
#define CREATEEVENTDIALOG_H

#include <QDialog>

namespace Ui {
class CreateEventDialog;
}

class CreateEventDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateEventDialog(QWidget *parent = nullptr);
    ~CreateEventDialog();

private:
    Ui::CreateEventDialog *ui;
};

#endif // CREATEEVENTDIALOG_H
