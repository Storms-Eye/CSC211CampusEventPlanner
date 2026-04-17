#include "eventapprovaldialog.h"
#include "ui_eventapprovaldialog.h"

EventApprovalDialog::EventApprovalDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EventApprovalDialog)
{
    ui->setupUi(this);
}

EventApprovalDialog::~EventApprovalDialog()
{
    delete ui;
}
