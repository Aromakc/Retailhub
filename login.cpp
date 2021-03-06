#include "login.h"
#include "ui_login.h"
#include<math.h>

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setWindowTitle("RetailHub");

    if(!connOpen())                                           //connecting and checking database
        ui->statusbar->showMessage("Failed to locate database!");
    else
        ui->statusbar->showMessage("Connected...");

    QString datetime_text=datetime.toString("dd MMM yyyy");
    ui->date->setText(datetime_text);

    QTimer *timer=new QTimer(this);                          //creating new DYNAMIC memory to store time
    connect(timer,SIGNAL(timeout()),this,SLOT(showtime()));
    timer->start();

    ui->stackedWidget->setCurrentIndex(0);                  // showing Dashboard; ui pointing to object stackedWidget
    display_dash();
}

Login::~Login()
{
    delete ui;
    connClose();                                             //closing connection to Sqlite database
}
void Login::showtime()
{
    QTime time=QTime::currentTime();
    QString time_text=time.toString("hh : mm : ss");
    ui->time->setText(time_text);

}
/*QString Login::currentdate() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%d-%m-%Y", &tstruct);

    return buf;
}*/


//===================================================DASHBOARD=========================================================
void Login::on_dashboard_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    display_dash();
}
void Login::display_dash()
{
    qint16 i=0,j=0,k=0;
    QSqlQuery query;

    query.prepare("Select Quantity from Inventory"); //performing a task to select all Items from Quantity column in Inventory Table
    if(query.exec()){
        while(query.next()){
            if (query.value(0)!=0)
              i++;
            else
              j++;
        }
    }
    query.prepare("Select username from Users");
    if(query.exec()){
        while(query.next()){
           k++;
        }
    }
    QString ts=QString::number(i);
    QString os=QString::number(j);
    QString tu=QString::number(k);

    ui->total_stocks_value->setText(ts);            //show quantity_number>0
    ui->out_of_stocks_value->setText(os);           //show quantity_number=0
    ui->total_users_value->setText(tu);
}



//====================================================ACCOUNT===================================================================
void Login::on_customers_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

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
    QString username=ui->line_username->text();
    QSqlQuery query;
    query.prepare("Select * from Users where username='"+username+"'");
    if(!query.exec()){
        QMessageBox::information(this, "Error", "Account hasn't been registered!");
    }
    else{
        while (query.next()){
        ui->group_username->setText(query.value(0).toString());
        ui->group_name->setText(query.value(1).toString());
        ui->group_address->setText(query.value(3).toString());
        ui->group_phone->setText(query.value(4).toString());
        ui->group_showpaid->setText(query.value(5).toString());
        ui->group_showbalance->setText(query.value(6).toString());
        }
    }



}

void Login::on_clear_balance_clicked()
{
    QString username=ui->line_username->text();
    QSqlQuery query;
    query.prepare("Select Expenditure,Balance from Users where username='"+username+"'");
    if(query.exec()){
        while (query.next()){
            qint64 paid=(query.value(0)).toInt();
            qint64 balance=(query.value(1).toInt());
            qDebug()<<paid;
            qDebug()<<balance;
            paid +=balance;
            balance=0;
            QString paids=QString::number(paid);
            QString balances=QString::number(balance);
            query.exec("UPDATE Users set Expenditure='"+paids+"', Balance='"+balances+"' where username='"+username+"'");
        }
    }
    ui->statusbar->showMessage("Complete Balance is Paid 😊");
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

//================================================ INVENTORY=============================================================================

void Login::on_Inventory_clicked()
{
    refresh_table();
    ui->stackedWidget->setCurrentIndex(2);
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
        //qDebug()<<ok2;

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
           inv_clear();
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
          inv_clear();
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
           inv_clear();
       }
       else
       {
           QMessageBox::critical(this,tr("Error."),qry.lastError().text());
       }
       refresh_table();
}

void Login::inv_clear(){
    ui->lineEdit_brand->clear();
    ui->lineEdit_iid->clear();
    ui->lineEdit_item->clear();
    ui->lineEdit_type->clear();
    ui->lineEdit_price->clear();
    ui->lineEdit_qty->clear();
}
//======================================================Records============================================================================

void Login::on_Record_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
       le->clear();
    }
    ui->tableView_report->reset();
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
   QString report;

if(sortcustomer!="" and sortitem!="" and sortbrand!=""){
    report="Select * from Orders where username='"+sortcustomer+"' "
                   "and Sold_Item='"+sortitem+"' and Brand='"+sortbrand+"' "
                   "and DATE >='"+from+"' "
                   "AND DATE <='"+to+"'";

}
else{
    report="Select * from Orders where DATE >='"+from+"' AND DATE <='"+to+"'";
}
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


//================================================ SALE =============================================================================
void Login::on_Sale_clicked()
{
   //show stacked window
    ui->stackedWidget->setCurrentIndex(3);
    // show stacked window 2

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

       const QStringList titles {"PRODUCT","QTY","RATE","AMOUNT"};
       ui->table->setColumnCount(titles.size());
       ui->table->setHorizontalHeaderLabels(titles);

       //------------------------------------------------invoice----------------------------
                  qint64 invoice=1;
                  QString invoices;
       QSqlQuery query;
                  query.prepare("Select username from orders");
                  if(query.exec()){
                  while(query.next()){
                        invoice++;
                     }
                 }
                  invoices=QString::number(invoice);
                  ui->invoice->setText(invoices);
}

void Login::on_comboBox_user_currentIndexChanged(const QString &username)
{

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
    ui->cart->setText("Cart");
    ui->cart->setStyleSheet("QPushButton{background-color: rgb(0, 175, 0);} QPushButton{color: rgb(255, 255, 255);}");
     QString nulll=arg1;
    QString product=ui->comboBox_prod->currentText();
       QSqlQuery qry;
       qry.prepare("SELECT Price,Quantity from Inventory where Items='"+product+"'");

       if(qry.exec())
       {
           while (qry.next())
           {
               ui->le_rate->setText(qry.value(0).toString());
               ui->le_qty->setPlaceholderText(qry.value(1).toString());
               if(qry.value(1)==0)
               {
                   ui->cart->setText("Out Of Stocks");
                   ui->cart->setStyleSheet("QPushButton{background-color: rgb(255, 75, 0);} QPushButton{color: rgb(255, 255, 255);}");
               }
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
    qfloat16 cal1,vat;
    int total=0;
    for(int i=0;i<ui->table->rowCount();i++){
      int a=ui->table->item(i,3)->text().toInt();
      total=total+a;
    }
    QString gross= QString::number(total);
    ui->le_gross->setText(gross);
    qDebug()<<total;

    vat=ui->le_vat->text().toInt();
    cal1=(total+((vat/100)*total));

    QString ntotal= QString::number(cal1);
    ui->total->setText(ntotal);

}
void Login::on_cancel_order_clicked()
{
    ui->le_amount->clear();
    ui->le_qty->clear();
    ui->total->clear();
    ui->le_gross->clear();
    ui->total->clear();
    ui->le_paid->clear();
    ui->table->clearContents();
    ui->table->setRowCount(0);

}
//----------------------------------------------------auto calculation------------------------------
void Login::on_le_qty_textEdited(const QString &arg1)
{
   int cal=arg1.toInt();
   int cal1= ui->le_rate->text().toInt();
   int cal2=(cal1*cal);
   std::cout<<cal2;
   QString cal3=QString::number(cal2);
    ui->le_amount->setText(cal3);
}

void Login::on_cart_clicked()
{
    const QString product=ui->comboBox_prod->currentText();
    const QString amount=ui->le_amount->text();
    const QString qty=ui->le_qty->text();
    const QString rate=ui->le_rate->text();
    const int rowCount=ui->table->rowCount();
    ui->table->insertRow(rowCount);

    ui->table->setItem(rowCount, PRODUCT, new QTableWidgetItem(product));
    ui->table->setItem(rowCount, QTY, new QTableWidgetItem(qty));
    ui->table->setItem(rowCount, RATE, new QTableWidgetItem(rate));
    ui->table->setItem(rowCount, AMOUNT, new QTableWidgetItem(amount));

    ui->le_qty->clear();
    ui->le_amount->clear();
}
//-------------------------------- PUSHBUTTON -> ORDER -----------------------------------------------------------
void Login::on_create_order_clicked()
{
    QString usernames=ui->comboBox_user->currentText();
    QString product_input=ui->comboBox_prod->currentText();


    qint64 paid=ui->le_paid->text().toInt();
    qint64 total=ui->total->text().toInt();
    QString name=ui->le_name->text();
    QString brand,invoices;

//------------------------------- USERS: EXPENDITURE AND BALANCE UPDATE--------------------------------------------

   QSqlQuery query1;
   QString balances;
   int spend;
   query1.prepare("Select Expenditure,Balance from Users where username='"+usernames+"' ");
   if(query1.exec())
   {
       while(query1.next())
       {          
       spend=query1.value(0).toInt();
       int balance=query1.value(1).toInt();
       qDebug()<<spend;
       spend += paid;
       balance = total-paid;
       QString spends=QString::number(spend);


       balances=QString::number(balance);
       query1.exec("Update Users SET Expenditure='"+spends+"', Balance='"+balances+"' where username='"+usernames+"'" );
       }
    }


//------------------------------INVENTORY: QUANTITY UPDATE -------------------------------------------------

   QString array[200][200];
   for(int i=0;i<ui->table->rowCount();i++)
   {
       for (int j=0;j<ui->table->columnCount();j++)
       {
           QString a =ui->table->item(i,j)->text();
           array[i][j]=a;
           qDebug()<<array[i][j];
       }

           QSqlQuery query;
           query.prepare("SELECT Quantity,Brand from Inventory where Items='"+array[i][0]+"'");
           if(query.exec())
           {
               while (query.next())
               {
                   qint16 cal=query.value(0).toInt();
                   brand=query.value(1).toString();
                   //qDebug()<<cal;

                   qint16 qty=array[i][1].toInt();
                  // qDebug()<<qty;

                   qint16 cal1=(cal-qty);
                   //qDebug()<<cal1;

                   QString calc=QString::number(cal1);

                   query.exec("Update Inventory SET Quantity=" + calc + " where Items='"+array[i][0]+"'" );
               }
           }


//------------------------------------------ODERS.DB SOLD ITEM RECORD-------------------------------------------------------------------------------
           QDate date = QDate::currentDate();
           QString date_set=date.toString("yyyy-MM-dd");

           QTime time= QTime::currentTime();
           QString time_set=time.toString();

           QString input_order="INSERT into Orders (username,Name,Sold_Item,Brand,Total_Price,Date,Time) values "
                               "('"+usernames+"','"+name+"','"+array[i][0]+"','"+brand+"',"+array[i][3]+",'"+date_set+"','"+time_set+"')";

             if(!query.exec(input_order))
           {

               QMessageBox::critical(this,tr("Error."),query.lastError().text());
           }

   }





   QtRPT *report = new QtRPT(this);
   report->loadReport(":/Resources/reporte.xml");

   connect(report, SIGNAL(setDSInfo(DataSetInfo &)),
   this, SLOT(setDSInfo(DataSetInfo &)));


       connect(report,&QtRPT::setValue,[&](const int recNo,
       const QString paramName,QVariant &paramValue,
       const int reportPage)
   {(void) reportPage;
       if (paramName == "customer")
               paramValue = usernames;
       if (paramName == "dates")
               paramValue = ui->date->text();
       if (paramName == "vat")
               paramValue = ui->le_vat->text();
       if (paramName=="product"){
           paramValue=ui->table->item(recNo, PRODUCT)->text();
       }
       if (paramName=="qty"){
           paramValue=ui->table->item(recNo, QTY)->text();
       }
       if(paramName=="rate"){
           paramValue=ui->table->item(recNo, RATE)->text();
       }
       if(paramName=="amount"){
           paramValue=ui->table->item(recNo, AMOUNT)->text();
       }
       if(paramName=="duebalance"){
           paramValue=balances;
       }
       if(paramName=="paid"){
           paramValue=paid;
       }
       if(paramName=="invoice"){
           paramValue=ui->invoice->text();
       }
   });

    report->printExec();
     //report->printPDF("../Invoice/.pdf", true);
}
void Login::setDSInfo(DataSetInfo &dsInfo){
    dsInfo.recordCount = ui->table->rowCount();
}





