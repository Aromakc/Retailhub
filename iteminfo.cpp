#include "iteminfo.h"
#include "ui_iteminfo.h"

#include<iostream>
#include<QMessageBox>

ItemInfo::ItemInfo(QString inputUsername,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItemInfo),
    username(inputUsername)
{
    ui->setupUi(this);
    if(!conn.connOpen())
        ui->label_vstatus->setText("Failed to locate database!");
    else
        ui->label_vstatus->setText("Connected...");
}

ItemInfo::~ItemInfo()
{
    conn.connClose();
    delete ui;
}

void ItemInfo::on_pushButton_vinv_clicked()
{

    QSqlQueryModel* modal= new QSqlQueryModel();
    QSqlQuery* qry=new QSqlQuery();
    qry->prepare("select * from Inventory");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);

    qDebug() << (modal->rowCount());

}

// INPUT DATABASE

void ItemInfo::on_pushButton_clicked()
{
    QString type,brand,item;
    qint64 iid,price,quantity;
    //iid=ui->lineEdit_iid->text().toInt();
   bool ok1,ok2;
    iid=ui->lineEdit_iid->text().toInt();
    type=ui->lineEdit_type->text();
    brand=ui->lineEdit_brand->text();
    item=ui->lineEdit_item->text();
    price=ui->lineEdit_price->text().toInt(&ok1);
    quantity=ui->lineEdit_qty->text().toInt(&ok2);

    if(ok1 && ok2){

    QSqlQuery qry;
    //qry.prepare("INSERT into Inventory (ID,Type,Brand,Items,Price,Quantity) values ('"+iid+"','"+type+"','"+brand+"','"+item+"','"+price+"','"+quantity+"')");

    qry.prepare("INSERT INTO Inventory (ID,Type,Brand,Items,Price,Quantity) VALUES(?, ?, ?, ?, ?, ?)");

    qry.addBindValue(iid);
    qry.addBindValue(type);
    qry.addBindValue(brand);
    qry.addBindValue(item);
    qry.addBindValue(price);
    qry.addBindValue(quantity);

    if(qry.exec()){
        QMessageBox::information(this,tr("Save"),tr("Saved"));
        ui->lineEdit_brand->clear();
        ui->lineEdit_iid->clear();
        ui->lineEdit_item->clear();
        ui->lineEdit_type->clear();
        ui->lineEdit_price->clear();
        ui->lineEdit_qty->clear();
    }
    else
    {
        QMessageBox::critical(this,tr("Error."),qry.lastError().text());         //?????????
    }
    }
     else
    {
        QMessageBox::information(this, "Invalid Input", "Enter Proper Number");
    }
}

// UPDATE DATABASE

void ItemInfo::on_update_clicked()
{
    QString type,brand,item,iid,price,quantity;
    iid=ui->lineEdit_iid->text();
    type=ui->lineEdit_type->text();
    brand=ui->lineEdit_brand->text();
    item=ui->lineEdit_item->text();
    price=ui->lineEdit_price->text();
    quantity=ui->lineEdit_qty->text();

    QSqlQuery qry;
    qry.prepare("UPDATE Inventory set Type='"+type+"',Brand='"+brand+"',Items='"+item+"', Price="+price+",Quantity="+quantity+" WHERE ID="+iid+"");
    if(qry.exec()){
        QMessageBox::information(this,tr("Edit"),tr("Updated"));
        ui->lineEdit_brand->clear();
        ui->lineEdit_iid->clear();
        ui->lineEdit_item->clear();
        ui->lineEdit_type->clear();
        ui->lineEdit_price->clear();
        ui->lineEdit_qty->clear();
    }
    else
    {
        QMessageBox::critical(this,tr("Error."),qry.lastError().text());
    }
}

// DELETE DATABASE
void ItemInfo::on_pushButton_delete_clicked()
{
    QString iid;
    iid=ui->lineEdit_iid->text();

    QSqlQuery qry;
    qry.prepare("DELETE from Inventory WHERE ID="+iid+"");
    if(qry.exec()){
        QMessageBox::information(this,tr("Delete"),tr("Deleted"));
        ui->lineEdit_iid->clear();
        ui->lineEdit_brand->clear();
        ui->lineEdit_item->clear();
        ui->lineEdit_type->clear();
        ui->lineEdit_price->clear();
        ui->lineEdit_qty->clear();
    }
    else
    {
        QMessageBox::critical(this,tr("Error."),qry.lastError().text());
    }
}
