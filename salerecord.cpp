#include "salerecord.h"
#include "ui_salerecord.h"

SaleRecord::SaleRecord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaleRecord)
{
    ui->setupUi(this);
}

SaleRecord::~SaleRecord()
{
    delete ui;
}
void SaleRecord::setdates()
{
    ui->from_dateEdit->setDate(QDate::currentDate().addMonths(-1));
    ui->to_dateEdit->setDate(QDate::currentDate());
}
