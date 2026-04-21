#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void acceptCredentials(const QString &acceptedID, const QString &acceptedPin, const QString &acceptedRole, const QString &acceptedName);

private slots:
    bool checkSort(const QJsonObject& obj);
    void on_listButton_clicked();
    void on_functionButton_clicked();
    void on_usersButton_clicked();

    void on_allButton_clicked();

    void on_nameButton_clicked();

    void on_IDButton_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;
    QString userID;
    QString pin;
    QString name;
    QString role;
};
#endif // MAINWINDOW_H
