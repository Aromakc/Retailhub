#ifndef ITEMINFO_H
#define ITEMINFO_H

#include <QDialog>
#include "login.h"

namespace Ui {
class ItemInfo;
}

class ItemInfo : public QDialog
{
    Q_OBJECT

public:
    explicit ItemInfo(QString inputUsername, QWidget *parent = nullptr);
    ~ItemInfo();

private slots:
    void on_pushButton_vinv_clicked();

    void on_pushButton_clicked();

    void on_update_clicked();

    void on_pushButton_delete_clicked();

private:
    Ui::ItemInfo *ui;
    QString username;
    Login conn;
};

#endif // ITEMINFO_H
