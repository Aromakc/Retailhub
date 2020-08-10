#include "order.h"
#include "ui_order.h"

Order::Order(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Order)
{
    ui->setupUi(this);
    conn.connOpen();
    QSqlQueryModel *modal=new QSqlQueryModel();
    QSqlQuery *qry=new QSqlQuery;
    qry->prepare("SELECT username from Users ORDER BY username ASC");

    qry->exec();
    modal->setQuery(*qry);
    ui->comboBox_user->setModel(modal);

    QSqlQueryModel *modal2=new QSqlQueryModel();
    qry->prepare("SELECT items from Inventory");

    qry->exec();
    modal2->setQuery(*qry);
    ui->comboBox_prod->setModel(modal2);


}

Order::~Order()
{
    delete ui;
    conn.connClose();
}


void Order::on_create_order_clicked()
{
    QString name,phone,rate,amount,gross,vat,discount,scharge,qty,total;
    name=ui->le_name->text();
    phone=ui->le_phone->text();
    rate=ui->le_rate->text();
    qty=ui->le_qty->text();
    amount=ui->le_qty->text();
    gross=ui->le_gross->text();
    scharge=ui->le_scharge->text();
    total=ui->le_total->text();
    vat=ui->le_vat->text();
    discount=ui->le_discount->text();

    QSqlQuery *qry=new QSqlQuery;
  }
