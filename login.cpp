#include "login.h"
#include "ui_login.h"

#include"iteminfo.h"
#include"order.h"
#include "createaccount.h"
#include<QStatusBar>

#include <QMessageBox>

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
}

Login::~Login()
{
    delete ui;
}


void Login::on_pushButton_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    if(username ==  "a" && password == "a") {
        //QMessageBox::information(this, "Login", "Username and password is correct");

        this->hide();                   // hide information dialog.
        ItemInfo iteminfo;
        iteminfo.setModal(true);
        iteminfo.exec();

    }
    else {
        ui->statusbar->showMessage("Login error!");
         }

}
void Login::on_actionView_Inventory_triggered()
{
    //ItemInfo iteminfo;
     ItemInfo* iteminfo  =   new ItemInfo(this);
     iteminfo->setAttribute(Qt::WA_DeleteOnClose);
    iteminfo->setModal(true);
    iteminfo->exec();
}
void Login::on_pushButton_2_clicked()
{
    CreateAccount createaccount;
    createaccount.setModal(true);
    createaccount.exec();
}

void Login::on_pushButton_3_clicked()
{
    Order order;
    order.setModal(true);
    order.exec();
}
