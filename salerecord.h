#ifndef SALERECORD_H
#define SALERECORD_H

#include <QDialog>

namespace Ui {
class SaleRecord;
}

class SaleRecord : public QDialog
{
    Q_OBJECT

public:
    explicit SaleRecord(QWidget *parent = nullptr);
    ~SaleRecord();

private:
    void setdates();

private:
    Ui::SaleRecord *ui;
};

#endif // SALERECORD_H
