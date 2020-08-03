#include "login.h"
#include"iteminfo.h"
#include "ui_login.h"
#include "createaccount.h"

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

    if(!connOpen())
        ui->label->setText("Failed to locate database!");
    else
        ui->label->setText("Connected...");
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

        //this->close();                   // hide information dialog.
        ItemInfo iteminfo(username);
        iteminfo.setModal(true);
        iteminfo.exec();

    }
    else {
        QMessageBox::warning(this,"Login", "Username and password is not correct");
    }

}

void Login::on_pushButton_2_clicked()
{
    CreateAccount createaccount;
    createaccount.setModal(true);
    createaccount.exec();
}
