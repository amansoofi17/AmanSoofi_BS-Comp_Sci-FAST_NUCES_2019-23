#include "admin.h"
#include "ui_admin.h"

Admin::Admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
    this->setFixedSize(1155,606);
    QPixmap pic(":/new/login/login image/image.png");
    int w = ui->label_pic_2->width();
    int h = ui->label_pic_2->height();
    ui->label_pic_2->setPixmap(pic.scaled(w,h));
    getAccounts();
    requests();
    show();
}

Admin::~Admin()
{
    delete ui;
}

void Admin::on_pushButton_deleteAcc_clicked()
{

    QModelIndex index = ui->listView_Acc->currentIndex();
    QString Account = index.data(Qt::DisplayRole).toString();
    index.data(Qt::DisplayRole);
    MainWindow w;
    if(!w.connopen())
    {
        qDebug()<<"Database is not open";
    }
    w.connopen();
    QSqlQuery qry;
    qry.prepare("delete from signup_data where username = '"+Account+"'");
    qry.exec();
    getAccounts();
}
void Admin::getAccounts()
{
    MainWindow w;
    if(!w.connopen())
    {
        qDebug()<<"Database is not open";
    }
    QSqlQueryModel *model = new QSqlQueryModel();
    w.connopen();
    QSqlQuery *qry = new QSqlQuery(w.mydb);
    qry->prepare("select username from signup_data");
    if(qry->exec())
    {
        model->setQuery(*qry);
        ui->listView_Acc->setModel(model);
        w.connclose();
    }
}

void Admin::requests()
{
    MainWindow w;
    total_requests = 0; //when request called calculate again requests if any deleted.
    if(!w.connopen())
    {
        qDebug()<<"Database is not open";
    }
    w.connopen();
    QSqlQuery qry,qry_count_totalitems;
    qry_count_totalitems.prepare("select * from Requests ");
    if(qry_count_totalitems.exec())
     {
        while (qry_count_totalitems.next()) {
            total_requests++;

        }



    }
    qry.prepare("select * from Requests ");
    int i = 0;
    if(qry.exec())
     {

  while(i<count_totalitems)
    {
            qry.next();  // for every item passed
            i++;
     }




       qry.next();
          item_name = qry.value(0).toString();
          item_pics = qry.value(1).toString();
          number_available = qry.value(2).toString();
          item_catagory = qry.value(3).toString();
          item_price = qry.value(4).toString();
          dealer_email = qry.value(5).toString();
          dealer_name = qry.value(6).toString();
          dealer_username = qry.value(7).toString();
          new_items = qry.value(8).toString();
          details = qry.value(9).toString();

         w.connclose();
     }


}

void Admin::show()
{
    requests();
    if(total_requests==0)
    {
        ui->pushButton_next->hide();
        ui->pushButton_previous->hide();
        ui->pushButton_Accept->hide();
        ui->pushButton_Reject->hide();
        return;
    }

    int wi = ui->label_pic->width();
    int h = ui->label_pic->height();
    if(item_pics!=NULL){
        QPixmap pic(item_pics);
        ui->label_pic->setPixmap(pic.scaled(wi,h));
    }

        ui->label_itemname->setText(item_name);
        ui->label_price->setText("PRICE: $"+item_price);
        ui->label_quantityold->setText("Number of existing items : "+number_available);
        ui->label_quantitynew->setText("Number of new items : "+number_available);
        ui->label_catagory->setText("Catagory : "+item_catagory);
        ui->label_dealername->setText("Requested by : "+dealer_name);
        ui->label_demail->setText("Email : "+dealer_email);
        ui->label_remaining->setText(QString::number(count_totalitems+1)+" out of "+QString::number(total_requests) );
}

void Admin::delete_data_fromrequests()
{
    MainWindow w;
    if(!w.connopen())
    {
        qDebug()<<"Database is not open";
    }
    w.connopen();
     QSqlQuery qry;
     qry.prepare("delete from Requests where productname = '"+item_name+"' ");
     if(qry.exec())
     {
         show();
     }
}

void Admin::show_profit()
{
    int profit = 0;

    MainWindow w;
    QSqlQueryModel * modal = new QSqlQueryModel();
    if(!w.connopen())
    {
        qDebug()<< "database is not open";
    }
    w.connopen();
    QSqlQuery * qry1 = new QSqlQuery(w.mydb),qry;
    qry1->prepare("select productid,productname,dealername,dealerusername,buyername,buyerusername,price_individual,Quantity,price_total,Profit from orders");
    qry1->exec();
    while (qry1->next()) {
        profit += qry1->value(9).toInt();   }
    modal->setQuery(*qry1);
    ui->tableView_profit->setModel(modal);
    //cell item properties
     ui->tableView_profit->setSelectionMode(QAbstractItemView::SingleSelection);
     ui->tableView_profit->setSelectionBehavior(QAbstractItemView::SelectRows);
     ui->tableView_profit->setTextElideMode(Qt::ElideRight);
     //table properties
     ui->tableView_profit->setShowGrid(true);
     ui->tableView_profit->setGridStyle(Qt::DotLine);
     ui->tableView_profit->setSortingEnabled(true);
     ui->tableView_profit->setCornerButtonEnabled(true);
     //header properties
     ui->tableView_profit->horizontalHeader()->setVisible(true);
     ui->tableView_profit->horizontalHeader()->setDefaultSectionSize(150);
     ui->tableView_profit->horizontalHeader()->setStretchLastSection(true);
     ui->tableView_profit->horizontalHeader()->setSectionResizeMode(QHeaderView :: Fixed);

     ui->label_Profit->setText("Total Profit : "+QString::number(profit));


}



void Admin::on_pushButton_addtax_clicked()
{
    MainWindow w;
    int count_no_data = 0;
    if(!w.connopen())
    {
        qDebug()<<"Database is not open";
    }
    QString tax = ui->lineEdit_taxper->text();
    QSqlQuery qry,qry2,qry3,qry4;
    qry.prepare("update items set Tax = '"+tax+"'");
    qry2.prepare("select * from items");
    qry.exec();
             if(qry2.exec())
             {
                 while(qry2.next())
                     count_no_data+=1;
             }
            qry2.first();
             int dealer_price = 0, soldprice = 0;
                 if(qry2.exec()){
                 while(qry2.next())
                 {
                   dealer_price = qry2.value(6).toInt();
                  soldprice = (dealer_price+((dealer_price*tax.toInt())/100));
                               if(qry4.exec("UPDATE items set SoldPrice = '"+QString::number( soldprice)+"' WHERE price = '"+QString::number(dealer_price)+"'"))
                               {
                                         QMessageBox::information(this,"","Tax Updated to :"+tax);
                               }
                 }


              w.connclose();
             }
}
void Admin::on_pushButton_next_clicked()
{
    if(count_totalitems+1<total_requests)
    {
        count_totalitems++;
        show();
    }

    else if(count_totalitems+1==total_requests)
{
    QMessageBox::information(this,"","This is all");
    }
    else {
        QMessageBox::information(this,"Sorry","No Pending Requests");
    }

    }

void Admin::on_pushButton_previous_clicked()
{
    if(count_totalitems>0)
    {
        count_totalitems--;
        show();
    }

    else if(count_totalitems==0)
    {
        QMessageBox::information(this,"","This is the first Request");
    }
    else {
        QMessageBox::information(this,"Sorry","No Pending Requests");
    }
}

void Admin::on_pushButton_Accept_clicked()
{

    MainWindow w;
    QSqlQuery qry_tax;
    int tax = 0;


    if(total_requests!=0){
   if(!w.connopen())
   {
       qDebug()<<"Database is not open";
   }
   w.connopen();
   int product_id = 100;
    QSqlQuery qry,qry_idcount,qry_productid,qry_update;
    QString productname = ui->label_itemname->text(),quantity_new = ui->label_quantitynew->text();
    qry_idcount.prepare("select * from items");
    if(qry_idcount.exec())
    {
        while(qry_idcount.next()){
            product_id++;
        if(productname == qry_idcount.value(1).toString())
        {
            productname = "yes";
        }
        }
        qry_idcount.first();
            tax = qry_idcount.value(10).toInt();
    }

    product_id = product_id +1;
    QString id= QString::number(product_id);

                 int  soldprice = 0;
                      soldprice = (item_price.toInt()+((item_price.toInt()*tax)/100));

                            if(productname == "yes"){
                      qry_update.prepare("update items set numberofitemsavailable = numberofitemsavailable + '"+quantity_new+"' where productname = '"+item_name+"'");
                      qry_update.exec();
}
//

    qry.prepare("insert into items (productid,productname,productimage,numberofitemsavailable,catagories,price,dealername,DealerUsername,SoldPrice,Details) values (:id,:productname,:productimage,:numberofitemsavailable,:catagories,:price,:dealername,:DealerUsername,:sold,:details)");
   qry.bindValue(":id",id);
    qry.bindValue(":productname",item_name);
    qry.bindValue(":productimage",item_pics);
    qry.bindValue(":numberofitemsavailable",number_available);
    qry.bindValue(":catagories",item_catagory);
    qry.bindValue(":price",item_price);
    qry.bindValue(":dealername",dealer_name);
    qry.bindValue(":DealerUsername",dealer_username);
    qry.bindValue(":sold",QString::number(soldprice));
    qry.bindValue(":details",details);

    if(qry.exec())
    {

            QMessageBox::information(this,"Accepted","Data added to Product list");
            delete_data_fromrequests();

    }


}
    else {
        QMessageBox::information(this,"Sorry","No Pending Requests");
    }

}

void Admin::on_pushButton_Reject_clicked()
{
    if(total_requests!=0){
    delete_data_fromrequests();
    QMessageBox::information(this,"","Data Deleted from Request List");
    }
    else {
        QMessageBox::information(this,"","No Pending Requests");
    }
}

void Admin::on_pushButton_Acc_Info_clicked()
{
    QModelIndex index = ui->listView_Acc->currentIndex();
    QString Account = index.data(Qt::DisplayRole).toString();
    index.data(Qt::DisplayRole);

    MainWindow w;
    if(!w.connopen())
    {
        qDebug()<<"Database is not open";
    }
    w.connopen();
    QSqlQuery qry;
    qry.prepare("select * from signup_data where username = '"+Account+"' ");
    if(qry.exec())
    {
        show_acc_info show;
        show.setModal(true);
        show.show_account_info(Account);
        show.exec();
        w.connclose();
    }
    else
    {
        QMessageBox::information(this,""," na");
    }
}

void Admin::on_tabWidget_tabBarClicked(int index)
{
    if(index == 3)
        show_profit();
}

void Admin::on_pushButton_Logout_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,"LOGOUT","Are You Sure You Want To Logout?",QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        hide();
        MainWindow *w;
        w = new MainWindow(this);
        w->show();
    }

    else {
        return;
    }
}
