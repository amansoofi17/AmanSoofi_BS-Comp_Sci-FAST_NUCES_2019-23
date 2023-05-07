#include "add_items.h"
#include "ui_add_items.h"
#include<QIntValidator>
#include<QSqlQuery>
#include<QSqlDatabase>
#include<business_account.h>
Add_items::Add_items(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_items)
{
    ui->setupUi(this);
    this->setFixedSize(1155,606);
    QPixmap pic(":/new/login/login image/image.png");
    int w = ui->label_pic_2->width();
    int h = ui->label_pic_2->height();
    ui->label_pic_2->setPixmap(pic.scaled(w,h));
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
    ui->lineEdit_totalitems->setValidator(new QIntValidator(0,100,this));
    ui->lineEdit_price->setValidator(new QIntValidator(0,10000,this));

    ui->lineEdit_qantity->hide();
    ui->pushButton_quantity->hide();
}

Add_items::~Add_items()
{
    delete ui;
}

void Add_items::radiobutton_click(int i)
{

     if(i==1)
    ui->rB_automobile_5->click();
    else if(i==2)
    ui->rB_baby_5->click();
    else if(i==3)
    ui->rB_Beauty_5->click();
    else if(i==4)
    ui->rB_books_5->click();
    else if(i==5)
    ui->rB_computors_5->click();
    else if(i==6)
    ui->rB_electronics_5->click();
    else if(i==7)
    ui->rB_health_5->click();
    else if(i==8)
    ui->rB_homekitchen_5->click();
    else if(i==9)
    ui->rB_indus_scientific_5->click();
    else if(i==10)
    ui->rB_gaming_5->click();
    else if(i==11)
    ui->rB_watches_5->click();
    else if(i==12)
    ui->rB_software_5->click();
    else if(i==13)
    ui->rB_sports_5->click();
    else if(i==14)
    ui->rB_Tools_5->click();
    else if(i==15)
    ui->rB_furniture_5->click();

}

void Add_items::show_products()
{
    MainWindow w;
    QSqlQueryModel * modal = new QSqlQueryModel();
    if(!w.connopen())
    {
        qDebug()<< "database is not open";
    }
    w.connopen();
    QSqlQuery * qry1 = new QSqlQuery(w.mydb);
    qry1->prepare("select productid,productname,numberofitemsavailable,catagories,price,Tax,SoldPrice,numberoforders,averagerating from items where DealerUsername = '"+username_string+"'");
    qry1->exec();
    modal->setQuery(*qry1);
    ui->tableView_products->setModel(modal);
    //cell item properties
     ui->tableView_products->setSelectionMode(QAbstractItemView::SingleSelection);
     ui->tableView_products->setSelectionBehavior(QAbstractItemView::SelectRows);
     ui->tableView_products->setTextElideMode(Qt::ElideRight);
     //table properties
     ui->tableView_products->setShowGrid(true);
     ui->tableView_products->setGridStyle(Qt::DotLine);
     ui->tableView_products->setSortingEnabled(true);
     ui->tableView_products->setCornerButtonEnabled(true);
     //header properties
     ui->tableView_products->horizontalHeader()->setVisible(true);
     ui->tableView_products->horizontalHeader()->setDefaultSectionSize(150);
     ui->tableView_products->horizontalHeader()->setStretchLastSection(true);
     ui->tableView_products->horizontalHeader()->setSectionResizeMode(QHeaderView :: Fixed);

}



void Add_items::on_pushButton_add_clicked()
{
    QString name,path,catagery,email,details;
    QString number,price;

    if(ui->rB_automobile_5->isChecked())
       { catagery = "automobile";}
    if(ui->rB_baby_5->isChecked())
        catagery = "baby";
    if(ui->rB_Beauty_5->isChecked())
        catagery = "Beauty and personal care";
    if(ui->rB_books_5->isChecked())
        catagery = "Books";
    if(ui->rB_computors_5->isChecked())
        catagery = "Computers";
    if(ui->rB_electronics_5->isChecked())
        catagery = "Electronics";
    if(ui->rB_health_5->isChecked())
        catagery = "Health and Household";
    if(ui->rB_homekitchen_5->isChecked())
        catagery = "Home and kitchen";
    if(ui->rB_indus_scientific_5->isChecked())
        catagery = "Industrial and scientific";
    if(ui->rB_gaming_5->isChecked())
        catagery = "Gaming";
    if(ui->rB_watches_5->isChecked())
        catagery = "Watches";
    if(ui->rB_software_5->isChecked())
        catagery = "Software";
    if(ui->rB_sports_5->isChecked())
        catagery = "Sports and outdoors";
    if(ui->rB_Tools_5->isChecked())
        catagery = "Tools and Home improvement";
    if(ui->rB_furniture_5->isChecked())
        catagery = "Furniture";

    name = ui->lineEdit_productname->text();
    path = ui->lineEdit_picpath->text();
    number = ui->lineEdit_totalitems->text();
    price = ui->lineEdit_price->text();
    details = ui->lineEdit_description->text();
    if(path.isNull() || name.isNull() || number.isNull() || price.isNull())
    { QMessageBox::warning(this,"Error","Complete Data!");   }
        else {


    MainWindow w;
    if(!w.connopen())
    {
        qDebug()<< "database is not open";
  }
  w.connopen();
   QSqlQuery qry1,qry_email,qry_checkcatagory;
qry_checkcatagory.prepare("select * from items where catagories = '"+catagery+"'");
int count_catagoryitems = 0;
if(qry_checkcatagory.exec())
{
    while (qry_checkcatagory.next()) {
        count_catagoryitems++;
    }

}

    if(count_catagoryitems>50)
    {
        QMessageBox::warning(this,"ERROR","Sorry This Catagory : "+catagery +" has Full Items. \n Limit of Items in a Catagory is : 50");
        return;
    }
   QString dealer_name;
   qry_email.prepare("select * from signup_data where username= '"+username_string+"'");
     if(qry_email.exec())
     {
         qry_email.next();
         email = qry_email.value(8).toString();
         dealer_name = qry_email.value(0).toString();
     }

    qry1.prepare("insert into Requests (productname,productimage,numberofitemsavailable,catagories,price,businessemail,dealername,DealerUsername,Addquantity,Details) values (:name,:image,:number,:catagery,:price,:email,:dname,:DealerUsername,:add,:details)");
    qry1.bindValue(":name",name);
    qry1.bindValue(":image",path);
    qry1.bindValue(":number",0);
    qry1.bindValue(":catagery",catagery);
    qry1.bindValue(":price",price);
    qry1.bindValue(":email",email);
    qry1.bindValue(":dname",dealer_name);
    qry1.bindValue(":DealerUsername",username_string);
    qry1.bindValue(":add",number);
    qry1.bindValue(":details",details);


    if(qry1.exec())

    {
      QMessageBox :: information(this,"SUCCESFUL","Your request has been sent");
      ui->lineEdit_productname->clear();
      ui->lineEdit_totalitems->clear();
      ui->lineEdit_picpath->clear();
      ui->lineEdit_price->clear();
        w.connclose();
    }
     else
     {
         QMessageBox::warning(this,"","This Product already exists \n You can add quantity from Your Products Tab");
     }

}
}

void Add_items::on_pushButton_edit_clicked()
{
    ui->lineEdit_qantity->show();
    ui->pushButton_quantity->show();
}

void Add_items::on_pushButton_delete_clicked()
{
    int n = ui->tableView_products->selectionModel()->currentIndex().row();
   QString name = ui->tableView_products->model()->index(n,1).data().toString();
   MainWindow w;
   if(!w.connopen())
   {
       qDebug()<<"Database is not open";
   }
   w.connopen();
    QSqlQuery qry;
    qry.prepare("delete from items where productname = '"+name+"'");
      if(qry.exec())
      {
          show_products();
          w.connclose();
      }
}

void Add_items::on_pushButton_quantity_clicked()
{
        int n = ui->tableView_products->selectionModel()->currentIndex().row();

       QString name,pic,quantity_old,catagories,price,email,Dname,quantity_new;
        name= ui->tableView_products->model()->index(n,1).data().toString();
        quantity_old = ui->tableView_products->model()->index(n,2).data().toString();
        catagories = ui->tableView_products->model()->index(n,3).data().toString();
        price = ui->tableView_products->model()->index(n,4).data().toString();
         quantity_new = ui->lineEdit_qantity->text();
        MainWindow w;
       if(!w.connopen())
       {
           qDebug()<<"Database is not open";
       }
       w.connopen();
        QSqlQuery qry1,qry_itemdata,qry_email;
        qry_itemdata.prepare("select * from items where productname = '"+name+"'");
        qry_itemdata.exec();
        qry_itemdata.next();
        pic = qry_itemdata.value(2).toString();
        Dname = qry_itemdata.value(9).toString();
        qry_email.prepare("select * from signup_data where username= '"+username_string+"'");
          if(qry_email.exec())
          {
              qry_email.next();
              email = qry_email.value(8).toString();
          }
          qry1.prepare("insert into Requests (productname,productimage,numberofitemsavailable,catagories,price,businessemail,dealername,DealerUsername,Addquantity) values (:name,:image,:number,:catagery,:price,:email,:dname,:DealerUsername,:add)");
          qry1.bindValue(":name",name);
          qry1.bindValue(":image",pic);
          qry1.bindValue(":number",quantity_old);
          qry1.bindValue(":catagery",catagories);
          qry1.bindValue(":price",price);
          qry1.bindValue(":email",email);
          qry1.bindValue(":dname",Dname);
          qry1.bindValue(":DealerUsername",username_string);
          qry1.bindValue(":add",quantity_new);
            qry1.exec();
            QMessageBox :: information(this,"SUCCESFUL","Your request has been sent");

            show_products();

}
void Add_items::on_tabWidget_tabBarClicked(int index)
{
    if(index == 2)
    show_products();

    }


void Add_items::on_lineEdit_productname_textEdited(const QString &arg1)
{
    int n = arg1.size();
    if(n>40)
    {
        ui->label_productnameerror->setText("Product Name Charcter Limit(25) Exceeds.");
    }
    if(n<40)
    {
        ui->label_productnameerror->setText("");
    }


}

void Add_items::on_lineEdit_picpath_textEdited(const QString &arg1)
{
    QPixmap pic(arg1);
    if(pic.isNull())
    {
        ui->label_picerror->setText("Enter Correct Image Path");
    }
    if(!pic.isNull())
    {
        ui->label_picerror->setText("");

    }
}

void Add_items::on_radioButton_accounts_clicked()
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

void Add_items::on_radioButton_orders_clicked()
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

void Add_items::on_radioButton_fullname_clicked()
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

void Add_items::on_radioButton_user_clicked()
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

void Add_items::on_radioButton_pass_clicked()
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

void Add_items::on_radioButton_email_clicked()
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

void Add_items::on_radioButton_businessphone_phone_clicked()
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

void Add_items::on_radioButton_address1_companyname_clicked()
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

void Add_items::on_radioButton_address2_warehouse_clicked()
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


void Add_items::on_pushButton_update_clicked()
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
        ui->lineEdit_edit1->setEchoMode(QLineEdit::Password);
        ui->lineEdit_edit2->setEchoMode(QLineEdit::Password);
        ui->lineEdit_edit3->setEchoMode(QLineEdit::Password);

        ui->label->setText("");
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

void Add_items::on_radioButton_Accoun_info_clicked()
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

void Add_items::on_pushButton_Logout_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,"LOGOUT","Are You Sure You Want To Logout?",QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        hide();
        Business_Account b;
        b.on_pushButton_Logout_clicked();
    }

    else {
        return;
    }
}
