#include "shop.h"
#include "ui_shop.h"
#include<QLineEdit>
Shop::Shop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Shop)
{
    ui->setupUi(this);
    this->setFixedSize(1155,606);
    Home();
    ui->radioButton_fullname->hide();
    ui->radioButton_pass->hide();
    ui->radioButton_user->hide();
    ui->radioButton_email->hide();
    ui->radioButton_address2_warehouse->hide();
    ui->radioButton_address1_companyname->hide();
    ui->radioButton_businessphone_phone->hide();
    ui->label_edit1->hide();
    ui->label_edit2->hide();
    ui->label_edit3->hide();
    ui->lineEdit_edit1->hide();
    ui->lineEdit_edit2->hide();
    ui->lineEdit_edit3->hide();
    ui->pushButton_update->hide();
    ui->tableView_orders->hide();
    // table widget style
    ui->tableWidget_baslet_2->setStyleSheet("QTableWidget{"
                                          "background-color: #C0C0C0;"
                                          "alternate-background-color: #606060;"
                                          "selection-background-color: #282828;"
                                          "}");
    //cell item properties
     ui->tableWidget_baslet_2->setSelectionMode(QAbstractItemView::SingleSelection);
     ui->tableWidget_baslet_2->setSelectionBehavior(QAbstractItemView::SelectRows);
     ui->tableWidget_baslet_2->setTextElideMode(Qt::ElideRight);
     //table properties
     ui->tableWidget_baslet_2->setShowGrid(true);
     ui->tableWidget_baslet_2->setGridStyle(Qt::DotLine);
     ui->tableWidget_baslet_2->setSortingEnabled(true);
     ui->tableWidget_baslet_2->setCornerButtonEnabled(true);
     //header properties
     ui->tableWidget_baslet_2->horizontalHeader()->setVisible(true);
     ui->tableWidget_baslet_2->horizontalHeader()->setDefaultSectionSize(150);
     ui->tableWidget_baslet_2->horizontalHeader()->setStretchLastSection(true);
     ui->tableWidget_baslet_2->horizontalHeader()->setSectionResizeMode(QHeaderView :: Fixed);

}
void Shop::Home()
{
    MainWindow w;
    int i = 0,j = 0,count_only = 0;
    QString onlyforyou[6];
    if(!w.connopen())
    {
      qDebug()<< "database is not open";
    }
    w.connopen();
    QSqlQuery qry,qry_getdata,qry_onlyforyou;
    qry.prepare("select * from items where numberoforders = 0");
   // get data which have highest number of orders
    int count_items = 0;

    qry_getdata.prepare("select * from items where numberoforders>0");
    qry_getdata.exec();
    while (qry_getdata.next()) {
        count_items++;
    }
    QString highest_orderitems[count_items];
    int no_of_orders[count_items];

    qry_getdata.first();
    i = 0;
    do {
            highest_orderitems[i] = qry_getdata.value(1).toString();
            no_of_orders[i] = qry_getdata.value(7).toInt();
          i++;  } while (qry_getdata.next());

         i = 0, j = 0;
    while (i<count_items) {
        for (j = i;j<count_items ;j++) {

            if(no_of_orders[i]<no_of_orders[j])
            {
                QString temp;
                no_of_orders[i] =  no_of_orders[i] + no_of_orders[j];
                no_of_orders[j] = no_of_orders[i] - no_of_orders[j];
                no_of_orders[i] = no_of_orders[i] - no_of_orders[j];
                temp = highest_orderitems[i];
                highest_orderitems[i] = highest_orderitems[j];
                highest_orderitems[j] = temp;
            }
        }
        i++;
    }

    i = 0;
    while (i<6) {
        onlyforyou[i] = highest_orderitems[i];
        i++;
    }



    //sale on those products which have number of orders = 0
    if(qry.exec())     // runs only if number of orders = 0 then sale is given
   {
    ui->label_13->setText("FLASH SALE");

    QString catagory[3] = {"","",""};
    i = 0;
    while (qry.next() && i<3) {

        if(catagory[0]!=qry.value(4).toString() && catagory[1]!=qry.value(4).toString() &&catagory[2]!=qry.value(4).toString())
       { sale[i] = qry.value(1).toString();
        catagory[i] = qry.value(4).toString();
         i++;        //i++ in if so that data stores in arr00ey than moves forward
        }
    }

    i = 0;
    QString path[3]= {"","",""},price[3]= {"","",""};
    while(i<3)
    {

        qry_getdata.exec("select * from items where productname = '"+sale[i]+"'");
          qry_getdata.next();
           path[i] = qry_getdata.value(2).toString();
           price[i] = qry_getdata.value(11).toString();
           i++;
    }

    QPixmap pic1(path[0]);
    int w = ui->label_Fpic1->width();
    int h = ui->label_Fpic1->height();
    ui->label_Fpic1->setPixmap(pic1.scaled(w,h));

    QPixmap pic2(path[1]);
     w = ui->label_Fpic2->width();
     h = ui->label_Fpic2->height();
    ui->label_Fpic2->setPixmap(pic2.scaled(w,h));

    QPixmap pic3(path[2]);
    w = ui->label_Fpic3->width();
    h = ui->label_Fpic3->height();
    ui->label_Fpic3->setPixmap(pic3.scaled(w,h));


    ui->label_Fname1_2->setText(price[0]);
    ui->label_Fname2_2->setText(price[1]);
    ui->label_Fname3_3->setText(price[2]);
    i = 0;
    while (i<3) {
        price[i] =QString::number( (price[i].toInt() - ((price[i].toInt()*5)/100))  );
        i++;
    }

    ui->label_Fname1->setText(sale[0]+"\n"+catagory[0]+"\n"+price[0]);
    ui->label_Fname2->setText(sale[1]+"\n"+catagory[1]+"\n"+price[1]);
    ui->label_Fname3->setText(sale[2]+"\n"+catagory[2]+"\n"+price[2]);
    }
    else
    {


        ui->label_13->setText("ONLY FOR YOU");


        count_only = 3;
        i = 0;
            QString path[3]= {"","",""},price[3]= {"","",""},catagory[3] ={"","",""} ;
            while(i<3)
            {

                qry_onlyforyou.exec("select * from items where productname = '"+onlyforyou[i]+"'");
                  qry_onlyforyou.next();
                   path[i] = qry_onlyforyou.value(2).toString();
                   price[i] = qry_onlyforyou.value(11).toString();
                   catagory[i] = qry_onlyforyou.value(4).toString();
                   i++;
            }

            QPixmap pic1(path[0]);
            int w = ui->label_Fpic1->width();
            int h = ui->label_Fpic1->height();
            ui->label_Fpic1->setPixmap(pic1.scaled(w,h));

            QPixmap pic2(path[1]);
             w = ui->label_Fpic2->width();
             h = ui->label_Fpic2->height();
            ui->label_Fpic2->setPixmap(pic2.scaled(w,h));

            QPixmap pic3(path[2]);
            w = ui->label_Fpic3->width();
            h = ui->label_Fpic3->height();
            ui->label_Fpic3->setPixmap(pic3.scaled(w,h));


        ui->label_Fname1->setText(onlyforyou[0]+"\n"+catagory[0]+"\n"+price[0]);
        ui->label_Fname2->setText(onlyforyou[1]+"\n"+catagory[1]+"\n"+price[1]);
        ui->label_Fname3->setText(onlyforyou[2]+"\n"+catagory[2]+"\n"+price[2]);


}


    /*only for you*/


    if(count_only==3)
    {
        i = 0,j = 3;
            QString path[3]= {"","",""},price[3]= {"","",""},catagory[3] ={"","",""} ;
            while(i<3)
            {

                qry_onlyforyou.exec("select * from items where productname = '"+onlyforyou[j]+"'");
                  qry_onlyforyou.next();
                   path[i] = qry_onlyforyou.value(2).toString();
                   price[i] = qry_onlyforyou.value(11).toString();
                   catagory[i] = qry_onlyforyou.value(4).toString();
                   i++; j++;
            }

            QPixmap pic1(path[0]);
            int w = ui->label_opic1->width();
            int h = ui->label_opic1->height();
            ui->label_opic1->setPixmap(pic1.scaled(w,h));

            QPixmap pic2(path[1]);
             w = ui->label_opic2->width();
             h = ui->label_opic2->height();
            ui->label_opic2->setPixmap(pic2.scaled(w,h));

            QPixmap pic3(path[2]);
            w = ui->label_opic3->width();
            h = ui->label_opic3->height();
            ui->label_opic3->setPixmap(pic3.scaled(w,h));


        ui->label_oname1->setText(onlyforyou[0]+"\n"+catagory[0]+"\n"+price[0]);
        ui->label_oname2->setText(onlyforyou[1]+"\n"+catagory[1]+"\n"+price[1]);
        ui->label_oname3->setText(onlyforyou[2]+"\n"+catagory[2]+"\n"+price[2]);
    }


    else if(count_only==0)
    {
        ui->label_14->setText("ONLY FOR YOU");
        i = 0;
            QString path[3]= {"","",""},price[3]= {"","",""},catagory[3] ={"","",""} ;
            while(i<3)
            {

                qry_onlyforyou.exec("select * from items where productname = '"+onlyforyou[i]+"'");
                  qry_onlyforyou.next();
                   path[i] = qry_onlyforyou.value(2).toString();
                   price[i] = qry_onlyforyou.value(11).toString();
                   catagory[i] = qry_onlyforyou.value(4).toString();
                   i++;
            }

            QPixmap pic1(path[0]);
            int w = ui->label_opic1->width();
            int h = ui->label_opic1->height();
            ui->label_opic1->setPixmap(pic1.scaled(w,h));

            QPixmap pic2(path[1]);
             w = ui->label_opic2->width();
             h = ui->label_opic2->height();
            ui->label_opic2->setPixmap(pic2.scaled(w,h));

            QPixmap pic3(path[2]);
            w = ui->label_opic3->width();
            h = ui->label_opic3->height();
            ui->label_opic3->setPixmap(pic3.scaled(w,h));


        ui->label_oname1->setText(onlyforyou[0]+"\n"+catagory[0]+"\n"+price[0]);
        ui->label_oname2->setText(onlyforyou[1]+"\n"+catagory[1]+"\n"+price[1]);
        ui->label_oname3->setText(onlyforyou[2]+"\n"+catagory[2]+"\n"+price[2]);

    }
w.connclose();
}


Shop::~Shop()
{
    delete ui;
}


void Shop::on_rB_artscraft_clicked()
{
    hide();
    Categories_items show;
    show.setModal(true);
    show.radiobutton_click(0);
    show.exec();
}

void Shop::on_rB_automobile_clicked()
{
    hide();
    Categories_items show;
    show.setModal(true);
    show.radiobutton_click(1);
    show.exec();
}

void Shop::on_rB_baby_clicked()
{
    hide();
    Categories_items show;
    show.setModal(true);
    show.radiobutton_click(2);
    show.exec();
}

void Shop::on_rB_Beauty_clicked()
{
    hide();
    Categories_items show;
    show.setModal(true);
    show.radiobutton_click(3);
    show.exec();
}

void Shop::on_rB_books_clicked()
{
    hide();
    Categories_items show;
    show.setModal(true);
    show.radiobutton_click(4);
    show.exec();
}

void Shop::on_rB_computors_clicked()
{
    hide();
    Categories_items show;
    show.setModal(true);
    show.radiobutton_click(5);
    show.exec();
}

void Shop::on_rB_electronics_clicked()
{
    hide();
    Categories_items show;
    show.setModal(true);
    show.radiobutton_click(6);
    show.exec();
}

void Shop::on_rB_health_clicked()
{
    hide();
    Categories_items show;
    show.setModal(true);
    show.radiobutton_click(7);
    show.exec();
}

void Shop::on_rB_homekitchen_clicked()
{
    hide();
    Categories_items show;
    show.setModal(true);
    show.radiobutton_click(8);
    show.exec();
}

void Shop::on_rB_indus_scientific_clicked()
{
    hide();
    Categories_items show;
    show.setModal(true);
    show.radiobutton_click(9);
    show.exec();
}

void Shop::on_rB_gaming_clicked()
{
    hide();
    Categories_items show;
    show.setModal(true);
    show.radiobutton_click(10);
    show.exec();
}

void Shop::on_rB_watches_clicked()
{
    hide();
    Categories_items show;
    show.setModal(true);
    show.radiobutton_click(11);
    show.exec();
}

void Shop::on_rB_software_clicked()
{
    hide();
    Categories_items show;
    show.setModal(true);
    show.radiobutton_click(12);
    show.exec();
}

void Shop::on_rB_sports_clicked()
{
    hide();
    Categories_items show;
    show.setModal(true);
    show.radiobutton_click(13);
    show.exec();
}

void Shop::on_rB_Tools_clicked()
{
    hide();
    Categories_items show;
    show.setModal(true);
    show.radiobutton_click(14);
    show.exec();
}

void Shop::on_rB_furniture_clicked()
{
    hide();
    Categories_items show;
    show.setModal(true);
    show.radiobutton_click(15);
    show.exec();
}

void Shop::on_pushButton_shopmore_2_clicked()
{
    ui->tab_Basket->close();
    ui->tabWidget->setCurrentIndex(1);
    ui->tab_categories->show();
}

void Shop::on_pushButton_edit_2_clicked()
{
    QMessageBox::warning(this,"","Please Buy atleast one Product to Proceed.");
}

void Shop::on_pushButton_BUY_2_clicked()
{
    QMessageBox::warning(this,"","Please Buy atleast one Product to Proceed.");
}



void Shop::on_pushButton_search_clicked()
{
    Categories_items c;
    c.setModal(true);
    c.search_products(ui->lineEdit_search->text());
    c.exec();
}

void Shop::on_pushButton_orders1_clicked()
{
 Categories_items c;
 c.on_pushButton_orders1_clicked();
 c.exec();
}

void Shop::on_pushButton_orders2_clicked()
{
    Categories_items c;
    c.on_pushButton_orders2_clicked();
    c.exec();
}

void Shop::on_pushButton_orders3_clicked()
{
    Categories_items c;
    c.on_pushButton_orders3_clicked();
    c.exec();
}

void Shop::on_pushButton_ordero1_clicked()
{
    Categories_items c;
    c.on_pushButton_ordero1_clicked();
    c.exec();
}

void Shop::on_pushButton_ordero2_clicked()
{
    Categories_items c;
    c.on_pushButton_ordero2_clicked();
    c.exec();
}

void Shop::on_pushButton_ordero3_clicked()
{
    Categories_items c;
    c.on_pushButton_ordero3_clicked();
    c.exec();
}

void Shop::on_radioButton_accounts_clicked()
{
    ui->tableView_orders->hide();
    ui->label->setText("Select Anyone of These to Edit Account Details");
    ui->radioButton_fullname->show();
    ui->radioButton_pass->show();
    ui->radioButton_user->show();
    ui->radioButton_email->show();
    ui->radioButton_address2_warehouse->show();
    ui->radioButton_address1_companyname->show();
    ui->radioButton_businessphone_phone->show();
    ui->pushButton_update->show();

    ui->label_editerror1->setText(" ");
    ui->label_editerror2->setText(" ");
    ui->label_editerror3->setText(" ");
    ui->lineEdit_edit1->setText("");
    ui->lineEdit_edit2->setText("");
    ui->lineEdit_edit3->setText("");
    ui->label_edit1->setText(" ");
    ui->label_edit2->setText(" ");
    ui->label_edit3->setText(" ");
    MainWindow w;
    if(!w.connopen())
    {
      qDebug()<< "database is not open";
    }
    QSqlQuery qry;
    qry.exec("select * from signup_data where username = '"+username_string+"'");
    qry.next();
    QString Account = qry.value(10).toString();
    if(Account == "personal"){
        ui->radioButton_address1_companyname->setText("Address 1");
        ui->radioButton_address2_warehouse->setText("Address 2");
        ui->radioButton_businessphone_phone->setText("Phone");
    }

        else if (Account == "business") {
        ui->radioButton_address1_companyname->setText("Company Name");
        ui->radioButton_address2_warehouse->setText("WareHouse Address");
        ui->radioButton_businessphone_phone->setText("Phone");
    }



}

void Shop::on_radioButton_orders_clicked()
{
    ui->tableView_orders->show();
    ui->radioButton_fullname->hide();
    ui->radioButton_pass->hide();
    ui->radioButton_user->hide();
    ui->radioButton_email->hide();
    ui->radioButton_address2_warehouse->hide();
    ui->radioButton_address1_companyname->hide();
    ui->radioButton_businessphone_phone->hide();
    ui->label_edit1->hide();
    ui->label_edit2->hide();
    ui->label_edit3->hide();
    ui->lineEdit_edit1->hide();
    ui->lineEdit_edit2->hide();
    ui->lineEdit_edit3->hide();
    ui->label_editerror1->hide();
    ui->label_editerror2->hide();
    ui->label_editerror3->hide();
    ui->pushButton_update->hide();
    // order table
    MainWindow w;
    QSqlQueryModel * modal = new QSqlQueryModel();
    if(!w.connopen())
    {
        qDebug()<< "database is not open";
    }
    w.connopen();
    QSqlQuery * qry1 = new QSqlQuery(w.mydb),qry;
    qry1->prepare("select productid,productname,dealername,dealerusername,price_individual,Quantity,price_total from orders where buyerusername = '"+username_string+"'");
    qry1->exec();
    modal->setQuery(*qry1);
    ui->tableView_orders->setModel(modal);

    ui->tableView_orders->setStyleSheet("QTableView{"
                                          "background-color: #C0C0C0;"
                                          "alternate-background-color: #606060;"
                                          "selection-background-color: #282828;"
                                          "}");
    //cell item properties
     ui->tableView_orders->setSelectionMode(QAbstractItemView::SingleSelection);
     ui->tableView_orders->setSelectionBehavior(QAbstractItemView::SelectRows);
     ui->tableView_orders->setTextElideMode(Qt::ElideRight);
     //table properties
     ui->tableView_orders->setShowGrid(true);
     ui->tableView_orders->setGridStyle(Qt::DotLine);
     ui->tableView_orders->setSortingEnabled(true);
     ui->tableView_orders->setCornerButtonEnabled(true);
     //header properties
     ui->tableView_orders->horizontalHeader()->setVisible(true);
     ui->tableView_orders->horizontalHeader()->setDefaultSectionSize(150);
     ui->tableView_orders->horizontalHeader()->setStretchLastSection(true);
     ui->tableView_orders->horizontalHeader()->setSectionResizeMode(QHeaderView :: Fixed);

}

void Shop::on_radioButton_fullname_clicked()
{
    ui->label_editerror1->setText(" ");
    ui->label_editerror2->setText(" ");
    ui->label_editerror3->setText(" ");
    ui->lineEdit_edit1->setText("");
    ui->lineEdit_edit2->setText("");
    ui->lineEdit_edit3->setText("");
    ui->label_edit1->setText(" ");
    ui->label_edit2->setText(" ");
    ui->label_edit3->setText(" ");
    ui->label_edit1->hide();
    ui->label_edit2->show();
    ui->label_edit2->setText("Full Name");
    ui->label->setText("Enter New Name");
    ui->label_edit3->hide();
    ui->lineEdit_edit1->hide();
    ui->lineEdit_edit2->show();
    ui->lineEdit_edit3->hide();
}

void Shop::on_radioButton_user_clicked()
{
    ui->label_editerror1->setText(" ");
    ui->label_editerror2->setText(" ");
    ui->label_editerror3->setText(" ");
    ui->lineEdit_edit1->setText("");
    ui->lineEdit_edit2->setText("");
    ui->lineEdit_edit3->setText("");
    ui->label_edit1->setText(" ");
    ui->label_edit2->setText(" ");
    ui->label_edit3->setText(" ");
    ui->label_edit1->hide();
    ui->label_edit2->show();
    ui->label_edit2->setText("Username");
    ui->label->setText("Enter New Username");
    ui->label_edit3->hide();
    ui->lineEdit_edit1->hide();
    ui->lineEdit_edit2->show();
    ui->lineEdit_edit3->hide();
}

void Shop::on_radioButton_pass_clicked()
{
    ui->label_editerror1->setText(" ");
    ui->label_editerror2->setText(" ");
    ui->label_editerror3->setText(" ");
    ui->lineEdit_edit1->setText("");
    ui->lineEdit_edit2->setText("");
    ui->lineEdit_edit3->setText("");
    ui->label->setText(" ");
    ui->label_edit1->setText(" ");
    ui->label_edit2->setText(" ");
    ui->label_edit3->setText(" ");
    ui->label_edit1->show();
    ui->label_edit1->setText("Enter Old Password");
    ui->label_edit2->show();
    ui->label_edit2->setText("Enter New Password");
    ui->label_edit3->show();
    ui->label_edit3->setText("Confirm New Password");
    ui->lineEdit_edit1->show();
    ui->lineEdit_edit2->show();
    ui->lineEdit_edit3->show();
}

void Shop::on_radioButton_email_clicked()
{
    ui->label_editerror1->setText(" ");
    ui->label_editerror2->setText(" ");
    ui->label_editerror3->setText(" ");
    ui->lineEdit_edit1->setText("");
    ui->lineEdit_edit2->setText("");
    ui->lineEdit_edit3->setText("");
    ui->label_edit1->setText(" ");
    ui->label_edit2->setText(" ");
    ui->label_edit3->setText(" ");
    ui->label_edit1->hide();
    ui->label_edit2->show();
    ui->label_edit2->setText("Email");
    ui->label->setText("Enter New Email");
    ui->label_edit3->hide();
    ui->lineEdit_edit1->hide();
    ui->lineEdit_edit2->show();
    ui->lineEdit_edit3->hide();
}

void Shop::on_radioButton_businessphone_phone_clicked()
{
    ui->label_editerror1->setText(" ");
    ui->label_editerror2->setText(" ");
    ui->label_editerror3->setText(" ");
    ui->lineEdit_edit1->setText("");
    ui->lineEdit_edit2->setText("");
    ui->lineEdit_edit3->setText("");
    ui->label_edit1->setText(" ");
    ui->label_edit2->setText(" ");
    ui->label_edit3->setText(" ");
    ui->label_edit1->hide();
    ui->label_edit2->show();
    ui->label_edit2->setText("Phone");
    ui->label->setText("Enter New Phone Number");
    ui->label_edit3->hide();
    ui->lineEdit_edit1->hide();
    ui->lineEdit_edit2->show();
    ui->lineEdit_edit3->hide();
}

void Shop::on_radioButton_address1_companyname_clicked()
{
    ui->label_editerror1->setText(" ");
    ui->label_editerror2->setText(" ");
    ui->label_editerror3->setText(" ");
    ui->lineEdit_edit1->setText("");
    ui->lineEdit_edit2->setText("");
    ui->lineEdit_edit3->setText("");
    ui->label_edit1->setText(" ");
    ui->label_edit2->setText(" ");
    ui->label_edit3->setText(" ");
    ui->label_edit1->hide();
    ui->label_edit2->show();
    ui->label_edit2->setText(ui->radioButton_address1_companyname->text());
    ui->label->setText("Enter New "+ ui->radioButton_address1_companyname->text());
    ui->label_edit3->hide();
    ui->lineEdit_edit1->hide();
    ui->lineEdit_edit2->show();
    ui->lineEdit_edit3->hide();
}

void Shop::on_radioButton_address2_warehouse_clicked()
{
    ui->label_editerror1->setText(" ");
    ui->label_editerror2->setText(" ");
    ui->label_editerror3->setText(" ");
    ui->lineEdit_edit1->setText("");
    ui->lineEdit_edit2->setText("");
    ui->lineEdit_edit3->setText("");
    ui->label_edit1->setText(" ");
    ui->label_edit2->setText(" ");
    ui->label_edit3->setText(" ");
    ui->label_edit1->hide();
    ui->label_edit2->show();
    ui->label_edit2->setText(ui->radioButton_address2_warehouse->text());
    ui->label->setText("Enter New "+ ui->radioButton_address2_warehouse->text());
    ui->label_edit3->hide();
    ui->lineEdit_edit1->hide();
    ui->lineEdit_edit2->show();
    ui->lineEdit_edit3->hide();
}


void Shop::on_pushButton_update_clicked()
{
    QString data,Account;
    MainWindow w;
    if(!w.connopen())
    {
      qDebug()<< "database is not open";
    }
    QSqlQuery qry,qry_account;
    qry_account.exec("select accounttype from signup_data where username = '"+username_string+"'");
    qry_account.next();
    Account = qry_account.value(0).toString();
    if(ui->radioButton_fullname->isChecked())
    {
        data = ui->lineEdit_edit2->text();
        //fullname only characters validation
             int i = 0,j = 0;
             while (i<data.length()) {

                j = 0;
                 while (j<10) {

                     if( data[i]==QString::number(j) )
                     {
                         ui->label_editerror2->setText("Numbers not allowed in Full Name!");
                         ui->label_editerror2->setStyleSheet("QLabel {  color : red; }");
                         return;
                     }  j++;
                 }
                 i++;
             }
        qry.exec("update signup_data set fullname = '"+data+"' where username = '"+username_string+"'");
        ui->label_editerror2->setText("Succesfully Updated");
        ui->label_editerror2->setStyleSheet("QLabel {  color : black; }");
    }

    else if(ui->radioButton_pass->isChecked())
    {
        ui->label->setText("");
        ui->lineEdit_edit1->setEchoMode(QLineEdit::Password);
        ui->lineEdit_edit2->setEchoMode(QLineEdit::Password);
        ui->lineEdit_edit3->setEchoMode(QLineEdit::Password);

        QString oldPass,newPass,reenterPass;
        QSqlQuery qry_oldpass;
        qry_oldpass.exec("select password from signup_data where username = '"+username_string+"' ");
       qry_oldpass.next();
        oldPass = qry_oldpass.value(0).toString();
        if(oldPass!=ui->lineEdit_edit1->text()){
            ui->label_editerror1->setText("Wrong Password");
            ui->label_editerror1->setStyleSheet("QLabel {  color : red; }");

            return;
        }
        newPass = ui->lineEdit_edit2->text();

        //password validation
        if(newPass.length()<8 || newPass.length()>15)
        {
            ui->label_editerror2->setText("Password character Limit (8-15)!");
            ui->label_editerror2->setStyleSheet("QLabel {  color : red; }");
            return;
        }


        reenterPass = ui->lineEdit_edit3->text();
        if(newPass!=reenterPass){
            ui->label_editerror3->setText("Both Password donot match");
            ui->label_editerror3->setStyleSheet("QLabel {  color : red; }");
            return;
        }

        qry.exec("update signup_data set password = '"+newPass+"' where username = '"+username_string+"'");
        ui->label->setText("Succesfully Updated");
        ui->label->setStyleSheet("QLabel {  color : black; }");



    }
    else if(ui->radioButton_user->isChecked())
    {
        QSqlQuery qry1,qry2;
        data = ui->lineEdit_edit2->text();
        qry2.prepare("select username from signup_data where username='"+data+"'");
                if(qry2.exec())
            {
                int count=0;
                while(qry2.next())
                    count++;

              if(count==0)
              {
                  qry.exec("update signup_data set username = '"+data+"' where username = '"+username_string+"'");
                  username_string = data;
                  ui->label_editerror2->setText("Succesfully Updated");
                  ui->label_editerror2->setStyleSheet("QLabel {  color : black; }");
                }
            else{
                ui->label_editerror2->setText("This username is already taken!");
                ui->label_editerror2->setStyleSheet("QLabel {  color : red; }");
                 }
    }
    }
    else if(ui->radioButton_email->isChecked())
    {
        data = ui->lineEdit_edit2->text();
        //email validation
        QRegExp pattern("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
        pattern.setCaseSensitivity(Qt::CaseInsensitive);
        pattern.setPatternSyntax(QRegExp::RegExp);
        bool check_email = pattern.exactMatch(data);
        if(!check_email){
            ui->label_editerror2->setText("Enter Correct Email Address! \n \tCorrect Format (xxxxx@xxxx.com) ");
            ui->label_editerror2->setStyleSheet("QLabel {  color : red; }");
            return;
        }
        qry.exec("update signup_data set email = '"+data+"' where username = '"+username_string+"'");
        ui->label_editerror2->setText("Succesfully Updated");
        ui->label_editerror2->setStyleSheet("QLabel {  color : black; }");
    }
    else if(ui->radioButton_businessphone_phone->isChecked())
    {
        data = ui->lineEdit_edit2->text();
        // phone validation
        if ((  (data.toLongLong() < 1000000000 || data.toLongLong() > 9999999999) || ((data.toLongLong()/1000000000)!=3) ))
        {
            ui->label_editerror2->setText("Please follow the correct number! \n \tformat 03xxxxxxxxx\n");
            ui->label_editerror2->setStyleSheet("QLabel {  color : red; }");
            return;
        }
        ui->label_editerror2->setText("Succesfully Updated");
        ui->label_editerror2->setStyleSheet("QLabel {  color : black; }");
        if(Account == "personal"){
            qry.exec("update signup_data set phonenumber = '"+data+"' where username = '"+username_string+"'");
        }
        else if(Account == "business"){
            qry.exec("update signup_data set businessphonenumber = '"+data+"' where username = '"+username_string+"'");
        }
    }
    else if(ui->radioButton_address1_companyname->isChecked())
    {
        data = ui->lineEdit_edit2->text();
        ui->label_editerror2->setText("Succesfully Updated");
        ui->label_editerror2->setStyleSheet("QLabel {  color : black; }");
        if(Account == "personal"){
            qry.exec("update signup_data set Address1 = '"+data+"' where username = '"+username_string+"'");
        }
        else if(Account == "business"){
            qry.exec("update signup_data set companyname = '"+data+"' where username = '"+username_string+"'");
        }

    }
    else if(ui->radioButton_address2_warehouse->isChecked())
    {
        data = ui->lineEdit_edit2->text();
        ui->label_editerror2->setText("Succesfully Updated");
        ui->label_editerror2->setStyleSheet("QLabel {  color : black; }");
        if(Account == "personal"){
            qry.exec("update signup_data set Address2 = '"+data+"' where username = '"+username_string+"'");
        }
        else if(Account == "business"){
            qry.exec("update signup_data set warehouseaddress = '"+data+"' where username = '"+username_string+"'");
        }
    }
}

void Shop::on_radioButton_Accoun_info_clicked()
{
    ui->radioButton_fullname->hide();
    ui->radioButton_pass->hide();
    ui->radioButton_user->hide();
    ui->radioButton_email->hide();
    ui->radioButton_address2_warehouse->hide();
    ui->radioButton_address1_companyname->hide();
    ui->radioButton_businessphone_phone->hide();
    ui->label_edit1->hide();
    ui->label_edit2->hide();
    ui->label_edit3->hide();
    ui->lineEdit_edit1->hide();
    ui->lineEdit_edit2->hide();
    ui->lineEdit_edit3->hide();
    ui->pushButton_update->hide();
    ui->tableView_orders->hide();

    show_acc_info a;
    a.show_account_info(username_string);
    a.exec();
}

void Shop::on_pushButton_Logout_clicked()
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
