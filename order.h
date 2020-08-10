#ifndef ORDER_H
#define ORDER_H

#include <QDialog>
#include"login.h"

namespace Ui {
class Order;
}

class Order : public QDialog
{
    Q_OBJECT

public:
    explicit Order(QWidget *parent = nullptr);
    ~Order();

private slots:

    void on_create_order_clicked();


private:
    Ui::Order *ui;
    Login conn;
};

#endif // ORDER_H
