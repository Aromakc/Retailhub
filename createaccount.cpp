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
/*{

        QString name,address,password,username,gender;
        qint64 phone;
        username=ui->line_username->text();
        password=ui->line_password->text();
        name=ui->line_name->text();
        address=ui->line_address->text();
        phone=ui->line_phone->text().toInt();
        if(ui->radioButton_M->isChecked())
        { gender='M';}
        if(ui->radioButton_F->isChecked())
        { gender='F';}



        QSqlQuery query;
        query.prepare("INSERT into Users (username,password,Name,Gender,Address,Phone_Number) values ('"+username+"','"+password+"','"+name+"','"+gender+"','"+address+"',"+phone+")");

        /*query.prepare("INSERT into Users (username,password,Name,Gender,Address,Phone_Number) VALUES(?, ?, ?, ?, ? ,?)");

        query.addBindValue(username);
        query.addBindValue(password);
        query.addBindValue(name);
        query.addBindValue(gender);
        query.addBindValue(address);
        query.addBindValue(phone);


        if(query.exec()){
             QMessageBox::information(this,tr("Save"),tr("Saved"));}
        else
        {
            QMessageBox::critical(this,tr("Error."),query.lastError().text());
        }
}*/
{
    QString name,address,password,username,gender;
    qint64 phone;
    bool ok;
    username=ui->line_username->text();
    password=ui->line_password->text();
    name=ui->line_name->text();
    address=ui->line_address->text();
    phone=ui->line_phone->text().toInt(&ok);
    if(ui->radioButton_M->isChecked())
    { gender='M';}
    if(ui->radioButton_F->isChecked())
    { gender='F';}

    if(ok){

        QSqlQuery query;
       //query.prepare("INSERT into Users (username,password,Name,Gender,Address,Phone_Number) values ('"+username+"','"+password+"','"+name+"','"+gender+"','"+address+"','"+phone+"')");

        query.prepare("INSERT into Users (username,password,Name,Gender,Address,Phone_Number) VALUES(:u.:p,:n,:g,:a,:c)");

        query.bindValue(":u",username);
        query.bindValue(":p",password);
        query.bindValue(":n",name);
        query.bindValue(":g",gender);
        query.bindValue(":a",address);
        query.bindValue(":c",phone);
        qDebug()<< query.lastQuery();
    if(query.exec()){
        QMessageBox::information(this,tr("Save"),tr("Saved"));
       /* ui->line_name->clear();
        ui->line_username->clear();
        ui->line_password->clear();
        ui->line_address->clear();
        ui->line_phone->clear();*/
        }
    else
    {
        QMessageBox::critical(this,tr("Error."),query.lastError().text());         //?????????
    }
    }
     else
    {
        QMessageBox::information(this, "Invalid Input", "Enter Proper Number");
    }
}


