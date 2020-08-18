#include "createaccount.h"
#include "ui_createaccount.h"
#include "QMessageBox"

#include"iteminfo.h"
#include"order.h"

CreateAccount::CreateAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateAccount)
{
    ui->setupUi(this);
    conn.connOpen();
}

CreateAccount::~CreateAccount()
{
    conn.connClose();
    delete ui;
}
bool CreateAccount::addaccount()
{
    // add customers acccount to database(Table:Users)
    // receive information

    QString name,address,password,username,gender,phone;
    username=ui->line_username->text();
    //password=ui->line_password->text();
    name=ui->line_name->text();
    address=ui->line_address->text();
    phone=ui->line_phone->text();
    if(ui->radioButton_M->isChecked())
    { gender="Male";}
    if(ui->radioButton_F->isChecked())
    { gender="Female";}

    QSqlQuery query;
    query.prepare("INSERT into Users(username,name,gender,address,phone) "
                  "values ('"+username+"','"+name+"','"+gender+"','"+address+"',"+phone+")");
    //execute the query
    if(!query.exec()){
        QMessageBox::critical(this, "Error", query.lastError().text()
                              + "\n" + query.lastQuery());
        return false;
    }
    return true;

}
void CreateAccount::resetForm()
{
    ui->line_username->clear();
    //ui->line_password->clear();
    ui->line_name->clear();
    ui->line_phone->clear();
    ui->line_address->clear();
    ui->line_username->setFocus();
}
void CreateAccount::on_pushButton_create_clicked()
{

    if(addaccount()){
        QMessageBox::information(this, "Succesfull", "Account Created!");
        resetForm();
    }
}



void CreateAccount::on_pushButton_vinv_clicked()
{
    this->close();
    ItemInfo iteminfo;
    iteminfo.setModal(true);
    iteminfo.exec();
}

void CreateAccount::on_sales_order_clicked()
{
     this->close();
    Order order;
    order.setModal(true);
    order.exec();
}
