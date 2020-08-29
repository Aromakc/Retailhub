#include "salerecord.h"
#include "ui_salerecord.h"
#include<QDate>
#include<QDateTime>
#include<QTimer>
#include<iostream>

using namespace std;

SaleRecord::SaleRecord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaleRecord)
{
    conn.connOpen();
    ui->setupUi(this);

    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showtime()));
    timer->start();

    setdates();
}

SaleRecord::~SaleRecord()
{
    conn.connClose();
    delete ui;
}
void SaleRecord::setdates()
{
    ui->from_dateEdit->setDate(QDate::currentDate().addMonths(-1));
    ui->to_dateEdit->setDate(QDate::currentDate());

}
void SaleRecord::showtime()
{
    QTime time=QTime::currentTime();
    QString time_text=time.toString("hh : mm : ss");
    ui->label_date->setText(time_text);

}

void SaleRecord::on_generate_report_pushbutton_clicked()
{
    QSqlQueryModel* reportModel= new QSqlQueryModel();
    QSqlQuery *qry=new QSqlQuery();

   QString from=ui->from_dateEdit->date().toString("yyyy-MM-dd");
   QString to =ui->to_dateEdit->date().toString("yyyy-MM-dd");



    QString report="Select * from Orders where DATE >='"+from+"' AND DATE <='"+to+"'";
    qry->prepare(report);
    qry->exec();
    qDebug()<<qry->executedQuery();
    reportModel->setQuery(*qry);
    ui->tableView->setModel(reportModel);

}
