#include "mainwindow.h"
#include "loginpagedialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginPageDialog l;
    l.show();
    return a.exec();
}
