#ifndef EVENTAPPROVALDIALOG_H
#define EVENTAPPROVALDIALOG_H

#include <QDialog>

namespace Ui {
class EventApprovalDialog;
}

class EventApprovalDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EventApprovalDialog(QWidget *parent = nullptr);
    ~EventApprovalDialog();

private:
    Ui::EventApprovalDialog *ui;
};

#endif // EVENTAPPROVALDIALOG_H
