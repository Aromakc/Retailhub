#ifndef ORDER_H
#define ORDER_H

#include <QDialog>

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

private:
    Ui::Order *ui;
};

#endif // ORDER_H
