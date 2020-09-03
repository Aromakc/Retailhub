#include "login.h"
#include "ui_login.h"
#include"iteminfo.h"
#include"order.h"
#include"salerecord.h"
#include "createaccount.h"


Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);

    if(!connOpen())
        ui->statusbar->showMessage("Failed to locate database!");
    else
        ui->statusbar->showMessage("Connected...");

    QDateTime datetime= QDateTime::currentDateTime();
    QString datetime_text=datetime.toString("dd MMM yyyy");
    ui->date->setText(datetime_text);

    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showtime()));
    timer->start();

    ui->stackedWidget->setCurrentIndex(0);
}

Login::~Login()
{
    delete ui;
}
void Login::showtime()
{
    QTime time=QTime::currentTime();
    QString time_text=time.toString("hh : mm : ss");
    ui->time->setText(time_text);

}
QString Login::currentdate() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%d-%m-%Y", &tstruct);

    return buf;
}


//DASHBOARD
void Login::on_dashboard_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget_2->setCurrentIndex(0);
}


//ACCOUNT
void Login::on_customers_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->stackedWidget_2->setCurrentIndex(1);
}
void Login::on_pushButton_create_clicked()
{

    if(addaccount()){
        QMessageBox::information(this, "Succesfull", "Account Created!");
        resetForm();
    }

}
void Login::on_pushButton_showcustomerinfo_clicked()
{

}
bool Login::addaccount()
{
    // add customers acccount to database(Table:Users)
    // receive information

    QString name,address,password,username,gender,phone;
    username=ui->line_username->text();
    //password=ui->line_password->text();
    name=ui->line_name->text();
    address=ui->line_address->text();
    phone=ui->line_phone->text();
    if(ui->radioButton_M->isChecked())
    { gender="Male";}
    if(ui->radioButton_F->isChecked())
    { gender="Female";}

    QSqlQuery query;
    query.prepare("INSERT into Users(username,name,gender,address,phone) "
                  "values ('"+username+"','"+name+"','"+gender+"','"+address+"',"+phone+")");
    //execute the query
    if(!query.exec()){
        QMessageBox::critical(this, "Error", query.lastError().text()
                              + "\n" + query.lastQuery());
        return false;
    }
    return true;
}
void Login::resetForm()
{
    ui->line_username->clear();
    //ui->line_password->clear();
    ui->line_name->clear();
    ui->line_phone->clear();
    ui->line_address->clear();
    ui->line_username->setFocus();
}


//Inventory
void Login::refresh_table()
{
    QSqlQueryModel* modal= new QSqlQueryModel();
    QSqlQuery* qry=new QSqlQuery();
    qry->prepare("select * from Inventory");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
}

void Login::on_Inventory_clicked()
{
    refresh_table();
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget_2->setCurrentIndex(2);
}


void Login::on_insert_sw3_clicked()
{
    QString type,brand,item;
        qint64 iid,price,quantity;
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
        qDebug()<< qry.executedQuery();


        if(qry.exec()){
            //QMessageBox::information(this,tr("Save"),tr("Saved"));
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
        refresh_table();

}

void Login::on_update_sw3_clicked()
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
      refresh_table();
}

void Login::on_delete_sw3_clicked()
{
    QString iid;
       iid=ui->lineEdit_iid->text();

       QSqlQuery qry;
       qry.prepare("DELETE from Inventory WHERE ID="+iid+"");
       if(qry.exec()){
           QMessageBox::information(this,tr("Delete"),tr("Deleted"));
           ui->lineEdit_iid->clear();
       }
       else
       {
           QMessageBox::critical(this,tr("Error."),qry.lastError().text());
       }
       refresh_table();
}

//SALE!!!!!!!!!!
void Login::on_Sale_clicked()
{
   //show stacked window
    ui->stackedWidget->setCurrentIndex(3);

    // show stacked window 2
    ui->stackedWidget_2->setCurrentIndex(3);

       QSqlQueryModel *modal=new QSqlQueryModel();
       QSqlQuery *qry= new QSqlQuery;

       qry->prepare("SELECT username from Users");
       qry->exec();
       modal->setQuery(*qry);
       ui->comboBox_user->setModel(modal);

       QString username=ui->comboBox_user->currentText();


       QSqlQueryModel *modal2=new QSqlQueryModel();
       qry->prepare("SELECT items from Inventory");

       qry->exec();
       modal2->setQuery(*qry);
       ui->comboBox_prod->setModel(modal2);
       QString product_input=ui->comboBox_user->currentText();

       ui->le_vat->setText("13");
}

void Login::on_comboBox_user_currentIndexChanged(const QString &arg1)
{
    QString nulll=arg1;
    QString username=ui->comboBox_user->currentText();

    QSqlQuery qry;
       qry.prepare("SELECT name,phone from Users where username='"+username+"'");

       if(qry.exec())
       {
           while (qry.next())
           {
               ui->le_name->setText(qry.value(0).toString());
               ui->le_phone->setText(qry.value(1).toString());
           }
           qDebug()<< qry.lastQuery();

       }
       else
       {
           QMessageBox::critical(this,tr("error"),qry.lastError().text());
       }
   }

void Login::on_comboBox_prod_currentIndexChanged(const QString &arg1)
{
     QString nulll=arg1;
    QString product=ui->comboBox_prod->currentText();
       QSqlQuery qry;
       qry.prepare("SELECT Price from Inventory where Items='"+product+"'");

       if(qry.exec())
       {
           while (qry.next())
           {
               ui->le_rate->setText(qry.value(0).toString());
           }
           qDebug()<< qry.lastQuery();
       }
       else
       {
           QMessageBox::critical(this,tr("error"),qry.lastError().text());
      }
}


void Login::on_Proceed_Cal_clicked()
{
        qfloat16 rate,vat,discount,qty;
        qfloat16 cal2,cal3,cal1;

        rate=ui->le_rate->text().toInt();
        qty=ui->le_qty->text().toInt();
        vat=ui->le_vat->text().toInt();
        discount=ui->le_discount->text().toInt();

        cal1=qty*rate;

        cal2=(cal1-((discount/100)*cal1));
        cal3=(cal2+((vat/100)*cal2));


        QString amount= QString::number(cal1);
        QString total= QString::number(cal3);


        ui->le_amount->setText(amount);
        ui->le_gross->setText(amount);
        ui->le_total->setText(total);
}
void Login::on_cancel_order_clicked()
{
    ui->le_amount->clear();
    ui->le_qty->clear();
    ui->le_total->clear();
}


void Login::on_create_order_clicked()
{
        QString product_input=ui->comboBox_prod->currentText();
        qint64 qty=ui->le_qty->text().toInt();

        // subtracting quantity from inventory
        QSqlQuery query;
        query.prepare("SELECT Quantity from Inventory where Items='"+product_input+"'");
        if(query.exec())
        {
            while (query.next())
            {
                int cal=query.value(0).toInt(); //wuantiity col 0 next col 1
                cal-=qty;
                QString calc=QString::number(cal);

                query.exec("Update Inventory SET Quantity=" + calc + " where Items='"+product_input+"'" );
            }

        }
        //static QString brands;
        QString name,phone,total,cal_qty,brands;

        QString usernames=ui->comboBox_user->currentText();
        QString products=ui->comboBox_prod->currentText();
        QString brand="Select Brand from Inventory where Items='"+products+"'";
        query.prepare(brand);
        if(query.exec())
        {
            while(query.next())
            {
              brands=query.value(0).toString();
            }
        }

        name=ui->le_name->text();
        phone=ui->le_phone->text();
        total=ui->le_total->text();

        QDate date = QDate::currentDate();
        QString date_set=date.toString("yyyy-MM-dd");

        QTime time= QTime::currentTime();
        QString time_set=time.toString();

        QString input_order="INSERT into Orders (username,Name,Sold_Item,Brand,Total_Price,Date,Time) values "
                            "('"+usernames+"','"+name+"','"+products+"','"+brands+"',"+total+",'"+date_set+"','"+time_set+"')";

          if(query.exec(input_order)){
             QMessageBox::information(this,tr("Save"),tr("Saved"));
             qDebug()<<query.executedQuery();
            }
        else
        {

            QMessageBox::critical(this,tr("Error."),query.lastError().text());
        }
}

void Login::on_Record_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->stackedWidget_2->setCurrentIndex(4);

    customernamecompleter();
    itemnamecompleter();
    companynamecompleter();

    setdates_record();
}
void Login::customernamecompleter(){
    QSqlQueryModel *customer_name_model= new QSqlQueryModel(this);
    customer_name_model->setQuery("select username from Users");
    auto customer_name_completer = new QCompleter(customer_name_model, this);
    customer_name_completer->setCompletionColumn(0);
    customer_name_completer->setCaseSensitivity(Qt::CaseInsensitive);
    customer_name_completer->setCompletionMode(QCompleter::PopupCompletion);

    // set the model onto the
    ui->setup_customer_name->setCompleter(customer_name_completer);
}
void Login::itemnamecompleter(){
    QSqlQueryModel *item_name_model= new QSqlQueryModel(this);
    item_name_model->setQuery("select Items from Inventory");
    auto item_name_completer = new QCompleter(item_name_model, this);
    item_name_completer->setCompletionColumn(0);
    item_name_completer->setCaseSensitivity(Qt::CaseInsensitive);
    item_name_completer->setCompletionMode(QCompleter::PopupCompletion);

    // set the model onto the
    ui->setup_items_name->setCompleter(item_name_completer);
}
void Login::companynamecompleter(){
    QSqlQueryModel *company_name_model= new QSqlQueryModel(this);
    company_name_model->setQuery("select Brand from Inventory");
    auto company_name_completer = new QCompleter(company_name_model, this);
    company_name_completer->setCompletionColumn(0);
    company_name_completer->setCaseSensitivity(Qt::CaseInsensitive);
    company_name_completer->setCompletionMode(QCompleter::PopupCompletion);

    // set the model onto the
    ui->setup_brand_name->setCompleter(company_name_completer);
}


void Login::on_generate_report_pushbutton_clicked()
{
    QSqlQueryModel* reportModel= new QSqlQueryModel();
    QSqlQuery *qry=new QSqlQuery();

   QString from=ui->from_dateEdit->date().toString("yyyy-MM-dd");
   QString to =ui->to_dateEdit->date().toString("yyyy-MM-dd");

   QString sortcustomer = ui->setup_customer_name->text();
   QString sortbrand = ui->setup_brand_name->text();
   QString sortitem = ui->setup_items_name->text();


    QString report="Select * from Orders where username='"+sortcustomer+"' "
                   "and Sold_Item='"+sortitem+"' and Brand='"+sortbrand+"' "
                   "and DATE >='"+from+"' "
                   "AND DATE <='"+to+"'";
    qry->prepare(report);
    qry->exec();
    qDebug()<<qry->executedQuery();
    reportModel->setQuery(*qry);
    ui->tableView_report->setModel(reportModel);
}
void Login::setdates_record()
{
    ui->from_dateEdit->setDate(QDate::currentDate().addMonths(-1));
    ui->to_dateEdit->setDate(QDate::currentDate());
}

void Login::on_sortcustomerwise_clicked()
{

    QSqlQueryModel* reportModel= new QSqlQueryModel();
    QSqlQuery *qry=new QSqlQuery();

   QString from=ui->from_dateEdit->date().toString("yyyy-MM-dd");
   QString to =ui->to_dateEdit->date().toString("yyyy-MM-dd");
   QString sortcustomer = ui->setup_customer_name->text(); 

    QString report="Select * from Orders where username='"+sortcustomer+"' AND DATE >='"+from+"' AND DATE <='"+to+"'";
    qry->prepare(report);
    qry->exec();
    qDebug()<<qry->executedQuery();
    reportModel->setQuery(*qry);
    ui->tableView_report->setModel(reportModel);
}

void Login::on_sortbrandwise_clicked()
{

    QSqlQueryModel* reportModel= new QSqlQueryModel();
    QSqlQuery *qry=new QSqlQuery();

   QString from=ui->from_dateEdit->date().toString("yyyy-MM-dd");
   QString to =ui->to_dateEdit->date().toString("yyyy-MM-dd");
   QString sortbrand = ui->setup_brand_name->text();

    QString report="Select * from Orders where Brand='"+sortbrand+"' AND DATE >='"+from+"' AND DATE <='"+to+"'";
    qry->prepare(report);
    qry->exec();
    qDebug()<<qry->executedQuery();
    reportModel->setQuery(*qry);
    ui->tableView_report->setModel(reportModel);
}

void Login::on_sortitemwise_clicked()
{

    QSqlQueryModel* reportModel3= new QSqlQueryModel();
    QSqlQuery *qry=new QSqlQuery();
    QString sortitem = ui->setup_items_name->text();

   QString from=ui->from_dateEdit->date().toString("yyyy-MM-dd");
   QString to =ui->to_dateEdit->date().toString("yyyy-MM-dd");

    QString report3="Select * from Orders where Sold_Item='"+sortitem+"' and DATE >='"+from+"' AND DATE <='"+to+"'";
    qry->prepare(report3);
    qry->exec();
    qDebug()<<qry->executedQuery();
    reportModel3->setQuery(*qry);
    ui->tableView_report->setModel(reportModel3);
}






