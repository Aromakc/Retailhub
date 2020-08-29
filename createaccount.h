#ifndef CREATEACCOUNT_H
#define CREATEACCOUNT_H

#include <QDialog>
#include "login.h"

namespace Ui {
class CreateAccount;
}

class CreateAccount : public QDialog
{
    Q_OBJECT

public:
    explicit CreateAccount(QWidget *parent = nullptr);
    ~CreateAccount();

private:
    //helper
    void resetForm();
    bool addaccount();

private slots:
    void on_pushButton_create_clicked();

    void on_pushButton_vinv_clicked();

    void on_sales_order_clicked();

private:
    Ui::CreateAccount *ui;
    Login conn;
};

#endif // CREATEACCOUNT_H
