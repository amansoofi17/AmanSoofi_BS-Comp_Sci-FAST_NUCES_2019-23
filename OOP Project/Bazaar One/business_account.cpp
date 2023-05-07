#include "business_account.h"
#include "ui_business_account.h"
#include<QIntValidator>
Business_Account::Business_Account(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Business_Account)
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
    ui->lineEdit_qantity->hide();
    ui->pushButton_quantity->hide();
    ui->lineEdit_qantity->setValidator(new QIntValidator(0,10,this));
}

Business_Account::~Business_Account()
{
    delete ui;
}



void Business_Account::on_rB_automobile_5_clicked()
{
    hide();
    Add_items show;
    show.setModal(true);
    show.radiobutton_click(1);
    show.exec();
}

void Business_Account::on_rB_baby_5_clicked()
{
    hide();
    Add_items show;
    show.setModal(true);
    show.radiobutton_click(2);
    show.exec();
}

void Business_Account::on_rB_Beauty_5_clicked()
{
    hide();
    Add_items show;
    show.setModal(true);
    show.radiobutton_click(3);
    show.exec();
}

void Business_Account::on_rB_books_5_clicked()
{
    hide();
    Add_items show;
    show.setModal(true);
    show.radiobutton_click(4);
    show.exec();
}

void Business_Account::on_rB_computors_5_clicked()
{
    hide();
    Add_items show;
    show.setModal(true);
    show.radiobutton_click(5);
    show.exec();
}

void Business_Account::on_rB_electronics_5_clicked()
{
    hide();
    Add_items show;
    show.setModal(true);
    show.radiobutton_click(6);
    show.exec();
}

void Business_Account::on_rB_health_5_clicked()
{
    hide();
    Add_items show;
    show.setModal(true);
    show.radiobutton_click(7);
    show.exec();
}

void Business_Account::on_rB_homekitchen_5_clicked()
{
    hide();
    Add_items show;
    show.setModal(true);
    show.radiobutton_click(8);
    show.exec();
}

void Business_Account::on_rB_indus_scientific_5_clicked()
{
    hide();
    Add_items show;
    show.setModal(true);
    show.radiobutton_click(9);
    show.exec();
}

void Business_Account::on_rB_gaming_5_clicked()
{
    hide();
    Add_items show;
    show.setModal(true);
    show.radiobutton_click(10);
    show.exec();
}

void Business_Account::on_rB_watches_5_clicked()
{
    hide();
    Add_items show;
    show.setModal(true);
    show.radiobutton_click(11);
    show.exec();
}

void Business_Account::on_rB_software_5_clicked()
{
    hide();
    Add_items show;
    show.setModal(true);
    show.radiobutton_click(12);
    show.exec();
}

void Business_Account::on_rB_sports_5_clicked()
{
    hide();
    Add_items show;
    show.setModal(true);
    show.radiobutton_click(13);
    show.exec();
}

void Business_Account::on_rB_Tools_5_clicked()
{
    hide();
    Add_items show;
    show.setModal(true);
    show.radiobutton_click(14);
    show.exec();
}

void Business_Account::on_rB_furniture_5_clicked()
{
    hide();
    Add_items show;
    show.setModal(true);
    show.radiobutton_click(15);
    show.exec();
}
void Business_Account::show_products()
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

void Business_Account::on_tabWidget_tabBarClicked(int index)
{
    if(index == 2)
        show_products();
}



void Business_Account::on_pushButton_quantity_clicked()
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

void Business_Account::on_pushButton_edit_clicked()
{
    ui->lineEdit_qantity->show();
    ui->pushButton_quantity->show();
}

void Business_Account::on_pushButton_delete_clicked()
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

void Business_Account::on_radioButton_accounts_clicked()
{
    ui->tableView_orders->hide();
    ui->label_7->setText("Select Anyone of These to Edit Account Details");
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

void Business_Account::on_radioButton_orders_clicked()
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

void Business_Account::on_radioButton_fullname_clicked()
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
    ui->label_7->setText("Enter New Name");
    ui->label_edit3->hide();
    ui->lineEdit_edit1->hide();
    ui->lineEdit_edit2->show();
    ui->lineEdit_edit3->hide();
}

void Business_Account::on_radioButton_user_clicked()
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
    ui->label_7->setText("Enter New Username");
    ui->label_edit3->hide();
    ui->lineEdit_edit1->hide();
    ui->lineEdit_edit2->show();
    ui->lineEdit_edit3->hide();
}

void Business_Account::on_radioButton_pass_clicked()
{
    ui->label_editerror1->setText(" ");
    ui->label_editerror2->setText(" ");
    ui->label_editerror3->setText(" ");
    ui->lineEdit_edit1->setText("");
    ui->lineEdit_edit2->setText("");
    ui->lineEdit_edit3->setText("");
    ui->label_7->setText(" ");
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

void Business_Account::on_radioButton_email_clicked()
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
    ui->label_7->setText("Enter New Email");
    ui->label_edit3->hide();
    ui->lineEdit_edit1->hide();
    ui->lineEdit_edit2->show();
    ui->lineEdit_edit3->hide();
}

void Business_Account::on_radioButton_businessphone_phone_clicked()
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
    ui->label_7->setText("Enter New Phone Number");
    ui->label_edit3->hide();
    ui->lineEdit_edit1->hide();
    ui->lineEdit_edit2->show();
    ui->lineEdit_edit3->hide();
}

void Business_Account::on_radioButton_address1_companyname_clicked()
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
    ui->label_7->setText("Enter New "+ ui->radioButton_address1_companyname->text());
    ui->label_edit3->hide();
    ui->lineEdit_edit1->hide();
    ui->lineEdit_edit2->show();
    ui->lineEdit_edit3->hide();
}

void Business_Account::on_radioButton_address2_warehouse_clicked()
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
    ui->label_7->setText("Enter New "+ ui->radioButton_address2_warehouse->text());
    ui->label_edit3->hide();
    ui->lineEdit_edit1->hide();
    ui->lineEdit_edit2->show();
    ui->lineEdit_edit3->hide();
}


void Business_Account::on_pushButton_update_clicked()
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

        ui->label_7->setText("");
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
        ui->label_7->setText("Succesfully Updated");
        ui->label_7->setStyleSheet("QLabel {  color : black; }");



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

void Business_Account::on_radioButton_Accoun_info_clicked()
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

void Business_Account::on_pushButton_Logout_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,"LOGOUT","Are You Sure You Want To Logout?",QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        hide();
        MainWindow *w = new MainWindow(this);
        w->show();
    }

    else {
        return;
    }
}
