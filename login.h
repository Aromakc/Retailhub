#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>

//Header for SQL
#include <QtSql>
#include <QDebug>
#include<QFileInfo>

//Header for iteminfo

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT
public:
    QSqlDatabase mydb;    // default connection
    void connClose(){
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection); //closing db and removing any connection
    }
    bool connOpen()
    {
         QSqlDatabase mydb=QSqlDatabase::addDatabase("QSQLITE");
         mydb.setDatabaseName("D:\\Retailhub\\Retailhub\\items.db");
        if(!mydb.open()){
            qDebug()<<("Failed to locate database!");
            return false;
        }
        else {
            qDebug()<<("Connected..."); // qDebug("Connected");
            return true;
        }
    }

public:
    Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Login *ui;

};
#endif // LOGIN_H
