#ifndef SALERECORD_H
#define SALERECORD_H

#include <QDialog>
#include <login.h>
#include <QSqlError>
#include <QMessageBox>
#include <QDate>
namespace Ui {
class SaleRecord;
}

class SaleRecord : public QDialog
{
    Q_OBJECT

public:
    explicit SaleRecord(QWidget *parent = nullptr);
    ~SaleRecord();
public:
    void setdates();
private slots:
    void showtime();

    void on_generate_report_pushbutton_clicked();

private:
    Ui::SaleRecord *ui;
    Login conn;
};

#endif // SALERECORD_H
