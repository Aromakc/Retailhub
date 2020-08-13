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

protected slots:
    void on_create_order_clicked();

private slots:


    void on_comboBox_user_currentIndexChanged(const QString &arg1);

    void on_comboBox_prod_currentIndexChanged(const QString &arg1);

    void on_pushButton_clicked();



private:
    Ui::Order *ui;
    Login conn;
};

#endif // ORDER_H
