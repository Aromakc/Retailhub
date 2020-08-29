#include "login.h"
#include "ui_login.h"

#include"iteminfo.h"
#include"order.h"
#include"salerecord.h"
#include "createaccount.h"

#include<QStatusBar>
#include <QMessageBox>
#include<QDateTime>
#include<QTimer>
#include<time.h>

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    // QPixmap pix("Location...");
    // ui->label_pic....labelofpic's_objname....->setPixmap("pix");

    //QSqlDatabase mydb=QSqlDatabase::addDatabase("QSQLITE");                    // old one
    //mydb.setDatabaseName("C:/Users/suwas/Documents/Sqlite_DB/items.db");

    /*if(!connOpen())
        ui->statusBar->setMessage("Failed to locate database!");
    else
        ui->statusBar->setText("Connected...");*/


    QDate date= QDate::currentDate();
    QString date_text=date.toString("dd MMM yyyy");

    //ui->label->setText(currentdate());
    ui->label->setText(date_text);
}

Login::~Login()
{
    delete ui;
}

QString Login::currentdate() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%d-%m-%Y", &tstruct);

    return buf;
}
void Login::on_pushButton_clicked()
{
        ItemInfo iteminfo;
        iteminfo.setModal(true);
        iteminfo.exec();
}

void Login::on_pushButton_2_clicked()
{
    CreateAccount createaccount;
    createaccount.setModal(true);
    createaccount.exec();
}

void Login::on_pushButton_3_clicked()
{
    SaleRecord order;
    order.setModal(true);
    order.exec();
}

void Login::on_pushButton_4_clicked()
{
    Order order;
    order.setModal(true);
    order.exec();
}
