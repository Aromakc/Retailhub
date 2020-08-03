#include "createaccount.h"
#include "ui_createaccount.h"
#include "QMessageBox"

CreateAccount::CreateAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateAccount)
{
    ui->setupUi(this);
    if(!conn.connOpen())
        ui->label_status->setText("Failed to locate database!");
    else
        ui->label_status->setText("Connected...");
    //conn.connOpen();
}

CreateAccount::~CreateAccount()
{
    conn.connClose();
    delete ui;
}

void CreateAccount::on_pushButton_create_clicked()
{

        QString name,address,password,phone,username,gender;

        username=ui->line_username->text();
        password=ui->line_password->text();
        name=ui->line_name->text();
        address=ui->line_address->text();
        phone=ui->line_phone->text().toInt();
        if(ui->radioButton_M->isChecked())
        { gender='M';}
        if(ui->radioButton_F->isChecked())
        { gender='F';}



        QSqlQuery qry;
        //qry.prepare("INSERT into Users (username,password,Name,Gender,Address,Phone_Number) values ('"+username+"','"+password+"','"+name+"','"+gender+"','"+address+"',"+phone+")");

        qry.prepare("INSERT into Users (username,password,Name,Gender,Address,Phone_Number) VALUES(?, ?, ?, ?, ? ,?)");

        qry.addBindValue(username);
        qry.addBindValue(password);
        qry.addBindValue(name);
        qry.addBindValue(gender);
        qry.addBindValue(address);
        qry.addBindValue(phone);


        if(qry.exec()){
             QMessageBox::information(this,tr("Save"),tr("Saved"));}
        else
        {
            QMessageBox::critical(this,tr("Error."),qry.lastError().text());
        }
}

