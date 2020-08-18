﻿#ifndef ITEMINFO_H
#define ITEMINFO_H

#include <QDialog>
#include "login.h"
#include"createaccount.h"
#include"order.h"

namespace Ui {
class ItemInfo;
}

class ItemInfo : public QDialog
{
    Q_OBJECT

public:
    explicit ItemInfo(QWidget *parent = nullptr); //(QString inputUsername,
    ~ItemInfo();

private slots:
    void on_pushButton_vinv_clicked();

    void on_pushButton_clicked();

    void on_update_clicked();

    void on_pushButton_delete_clicked();

    void on_sales_order_clicked();

    void on_create_account_clicked();

private:
    Ui::ItemInfo *ui;
    QString username;
    Login conn;
};

#endif // ITEMINFO_H
