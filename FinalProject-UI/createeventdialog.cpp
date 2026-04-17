#include "createeventdialog.h"
#include "ui_createeventdialog.h"

CreateEventDialog::CreateEventDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateEventDialog)
{
    ui->setupUi(this);
}

CreateEventDialog::~CreateEventDialog()
{
    delete ui;
}
