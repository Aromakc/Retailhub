#include "order.h"
#include "ui_order.h"
#include <QMessageBox>
#include<iostream>
#include<QDebug>
#include<QtMath>
Order::Order(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Order)
{
    ui->setupUi(this);
    conn.connOpen();

    QSqlQueryModel *modal=new QSqlQueryModel();
    QSqlQuery *qry= new QSqlQuery;

    qry->prepare("SELECT username from Users");
    qry->exec();
    modal->setQuery(*qry);
    ui->comboBox_user->setModel(modal);
    QString username=ui->comboBox_user->currentText();


    QSqlQueryModel *modal2=new QSqlQueryModel();
    qry->prepare("SELECT items from Inventory");

    qry->exec();
    modal2->setQuery(*qry);
    ui->comboBox_prod->setModel(modal2);
    QString product_input=ui->comboBox_user->currentText();

    ui->le_vat->setText("13");

}

Order::~Order()
{
    delete ui;
    conn.connClose();
}


void Order::on_create_order_clicked()
{
    QString name,phone;
    qint64 total;
    QString usernames=ui->comboBox_user->currentText();
    QString products=ui->comboBox_user->currentText();


    name=ui->le_name->text();
    phone=ui->le_phone->text();
    total=ui->le_total->text().toInt();



    QSqlQuery query;
    QString input_order="INSERT into Orders (username,Name,Sold_Item,Total_Price) values ('"+usernames+"','"+name+"','"+products+"','"+total+"')";

      if(query.exec(input_order)){
         QMessageBox::information(this,tr("Save"),tr("Saved"));
         qDebug()<<query.executedQuery();
        }
    else
    {

        QMessageBox::critical(this,tr("Error."),query.lastError().text());
    }

}
void Order::on_pushButton_clicked()
{
    qfloat16 rate,vat,discount,qty;
    qfloat16 cal2,cal3,cal1;

    rate=ui->le_rate->text().toInt();
    qty=ui->le_qty->text().toInt();
    vat=ui->le_vat->text().toInt();
    discount=ui->le_discount->text().toInt();

    cal1=qty*rate;

    cal2=(cal1-((discount/100)*cal1));
    cal3=(cal2+((vat/100)*cal2));


    QString amount= QString::number(cal1);
    QString total= QString::number(cal3);


    ui->le_amount->setText(amount);
    ui->le_gross->setText(amount);
    ui->le_total->setText(total);


    qDebug()<<cal1 <<cal2 <<cal3;

}



void Order::on_comboBox_user_currentIndexChanged(const QString &username)
{
   QString uservar=username;
    QSqlQuery qry;
    qry.prepare("SELECT name,phone from Users where username='"+uservar+"'");

    if(qry.exec())
    {
        while (qry.next())
        {
            ui->le_name->setText(qry.value(0).toString());
            ui->le_phone->setText(qry.value(1).toString());
        }
        qDebug()<< qry.lastQuery();

    }
    else
    {
        QMessageBox::critical(this,tr("error"),qry.lastError().text());
    }
}


void Order::on_comboBox_prod_currentIndexChanged(const QString &product_input)
{
    QString product=product_input;
    QSqlQuery qry;
    qry.prepare("SELECT Price from Inventory where Items='"+product+"'");

    if(qry.exec())
    {
        while (qry.next())
        {
            ui->le_rate->setText(qry.value(0).toString());
        }
        qDebug()<< qry.lastQuery();
    }
    else
    {
        QMessageBox::critical(this,tr("error"),qry.lastError().text());
   }
}

