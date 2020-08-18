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
