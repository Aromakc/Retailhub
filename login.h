#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>

//Header for SQL
#include <QtSql>
#include <QDebug>
#include<QFileInfo>
#include<iostream>
#include<ctime>
#include<QDate>
#include<string.h>

#include<QStatusBar>
#include <QMessageBox>
#include<QDateTime>
#include<QTimer>
#include<time.h>
#include<QCompleter>
#include<QPrinter>
#include<QPrintDialog>
#include<qtrpt.h>
#include<QtWidgets>
#include<QTableView>
#include<QTableWidget>
#include<QtMath>

#include <QApplication>
#include<QObject>
#include <QWindow>

//Header for iteminfo
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT
public:
    QDateTime datetime= QDateTime::currentDateTime();      //accessing date from QDatetime

    QSqlDatabase mydb;    // default connection    
    void connClose(){
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection); //closing db and removing any connection
    }
    bool connOpen()
    {
         QSqlDatabase mydb=QSqlDatabase::addDatabase("QSQLITE");
         mydb.setDatabaseName("../Retailhub/items.db");
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
private:
    //dashboard
    void display_dash();

    //create account
    void resetForm();
    bool addaccount();

    //view inventory
    void refresh_table();
    void inv_clear();

    //view record
    void customernamecompleter();
    void itemnamecompleter();
    void companynamecompleter();
    void setdates_record();
    void takequery();



private slots:


    void on_customers_clicked();

    void showtime();


    void on_pushButton_create_clicked();


    void on_Inventory_clicked();

    void on_insert_sw3_clicked();

    void on_update_sw3_clicked();

    void on_delete_sw3_clicked();

    void on_Sale_clicked();

    void on_Record_clicked();

    void on_Proceed_Cal_clicked();

    void on_comboBox_user_currentIndexChanged(const QString &arg1);

    void on_comboBox_prod_currentIndexChanged(const QString &arg1);

    void on_create_order_clicked();

    void on_generate_report_pushbutton_clicked();




    void on_sortcustomerwise_clicked();

    void on_sortbrandwise_clicked();

    void on_sortitemwise_clicked();

    void on_dashboard_clicked();

    void on_pushButton_showcustomerinfo_clicked();

    void on_cancel_order_clicked();


    void on_le_qty_textEdited(const QString &arg1);


    void on_cart_clicked();

    //pdf
    void setDSInfo(DataSetInfo &dsInfo);


    void on_clear_balance_clicked();

private:
    enum{
        PRODUCT,
        QTY,
        RATE,
        AMOUNT,
    };
    Ui::Login *ui;

};
#endif // LOGIN_H
