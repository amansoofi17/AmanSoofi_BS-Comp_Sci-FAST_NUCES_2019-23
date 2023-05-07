#include "show_items.h"
#include "ui_show_items.h"
#include<global.h>
#include<QMessageBox>
#include<QString>
#include<string.h>
#include<cstring>

Show_items::Show_items(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Show_items)
{
    ui->setupUi(this);
    this->setFixedSize(1155,606);

    Home();
    MainWindow w;
    QPixmap pic(":/new/login/login image/image.png");
    int wi = ui->label_pic->width();
    int h = ui->label_pic->height();
    ui->label_pic->setPixmap(pic.scaled(wi,h));

}

void Show_items::radiobutton_click(int i)
{
    if(i==1)
    ui->rB_automobile_2->click();
    else if(i==2)
    ui->rB_baby_2->click();
    else if(i==3)
    ui->rB_Beauty_2->click();
    else if(i==4)
    ui->rB_books_2->click();
    else if(i==5)
    ui->rB_computors_2->click();
    else if(i==6)
    ui->rB_electronics_2->click();
    else if(i==7)
    ui->rB_health_2->click();
    else if(i==8)
    ui->rB_homekitchen_2->click();
    else if(i==9)
    ui->rB_indus_scientific_2->click();
    else if(i==10)
    ui->rB_gaming_2->click();
    else if(i==11)
    ui->rB_watches_2->click();
    else if(i==12)
    ui->rB_software_2->click();
    else if(i==13)
    ui->rB_sports_2->click();
    else if(i==14)
    ui->rB_Tools_2->click();
    else if(i==15)
    ui->rB_furniture_2->click();

}

void Show_items::search_products(QString search)
{
    int count_search = 0,count1=0,i=0,j=0;
    QString Final_product = "",product,temp_name,temp_search;
    MainWindow w;
    if(!w.connopen())
    {
      qDebug()<< "database is not open";
    }
    w.connopen();
    QSqlQuery qry_search,qry_catagory,qry_noofitems;
    ui->lineEdit_search->setText(search);       // if searched from main window
    qry_search.prepare("select * from items");
    if(qry_search.exec())
    {
        while (qry_search.next()) {
             count1 = 0;
            product = qry_search.value(1).toString();

            for (i=0,j=0;search[i]!='\0';i++) {

                       temp_search.clear();

                    while(search[i]!=' '){
                        if(search[i]=='\0')
                            break;
                temp_search.append(search[i]);
                            i++;
                    }



            for (;product[j]!='\0';j++) {
               temp_name.clear();
              while(product[j]!=' '){
                  if(product[j]=='\0')
                      break;
                  temp_name.append(product[j]);
                      j++;
              }


              temp_search = temp_search.toLower();
              temp_name = temp_name.toLower();
              qDebug()<<temp_name<<" "<<temp_search;
              if(temp_name==temp_search)
                  count1++;

            }
            }

            if(count_search<count1){
                count_search = count1;
                Final_product = product;
            }
        /*qry_search.next*/}

        /*qry_search.exec*/}

    int count_numberofitems = 0;


    qry_catagory.prepare("select * from items where productname = '"+Final_product+"'");

    qry_catagory.exec();    qry_catagory.next();
    QString catagory = qry_catagory.value(4).toString();
    qry_noofitems.prepare("select * from items where catagories = '"+catagory+"'");
    qry_noofitems.exec();
    while (qry_noofitems.next()) {
        count_numberofitems++;
        if(Final_product == qry_noofitems.value(1))
            break;
    }

    if(Final_product=="")
    {
        QMessageBox::warning(this,"NOT FOUND","Searched Product not available right now");
    }

    ui->tab_Home->close();
    ui->tabWidget->setCurrentIndex(2);
    ui->tab_Categories->show();

    if(catagory == "automobile"){
        ui->rB_automobile_2->setChecked(true);
        ui->rB_automobile_2->clicked(true);
    }
    else if(catagory == "baby"){
        ui->rB_baby_2->setChecked(true);
        ui->rB_baby_2->clicked(true);
    }
    else if(catagory == "Beauty and personal care"){
        ui->rB_Beauty_2->setChecked(true);
        ui->rB_Beauty_2->clicked(true);
    }
    else if(catagory == "Books"){
        ui->rB_books_2->setChecked(true);
        ui->rB_books_2->clicked(true);
    }
    else if(catagory == "Computers"){
        ui->rB_computors_2->setChecked(true);
        ui->rB_computors_2->clicked(true);
    }
    else if(catagory == "Electronics"){
        ui->rB_electronics_2->setChecked(true);
        ui->rB_electronics_2->clicked(true);
    }
    else if(catagory == "Health and Household"){
        ui->rB_health_2->setChecked(true);
        ui->rB_health_2->clicked(true);
    }
    else if(catagory == "Home and kitchen"){
        ui->rB_homekitchen_2->setChecked(true);
        ui->rB_homekitchen_2->clicked(true);
    }
    else if(catagory == "Industrial and scientific"){
        ui->rB_indus_scientific_2->setChecked(true);
        ui->rB_indus_scientific_2->clicked(true);
    }
    else if(catagory == "Gaming"){
        ui->rB_gaming_2->setChecked(true);
        ui->rB_gaming_2->clicked(true);
    }
    else if(catagory == "Watches"){
        ui->rB_watches_2->setChecked(true);
        ui->rB_watches_2->clicked(true);
    }
    else if(catagory == "Software"){
        ui->rB_software_2->setChecked(true);
        ui->rB_software_2->clicked(true);
    }
    else if(catagory == "Sports and outdoors"){
        ui->rB_sports_2->setChecked(true);
        ui->rB_sports_2->clicked(true);
    }
    else if(catagory == "Tools and Home improvement"){
        ui->rB_Tools_2->setChecked(true);
        ui->rB_Tools_2->clicked(true);
    }
    else if(catagory == "Furniture"){
        ui->rB_furniture_2->setChecked(true);
        ui->rB_furniture_2->clicked(true);
    }

    i = 1;      // as we are on 1st item
    while (i<count_numberofitems) {
        ui->pushButton_next->clicked();
        i++;
    }


}

void Show_items::show_products(QString catagery)
{

    MainWindow w;
if(!w.connopen())
{
    qDebug()<< "database is not open";
}
w.connopen();
QSqlQuery * qry1 = new QSqlQuery(w.mydb);
qry1->prepare("select * from items where catagories = '"+catagery+"'");
int i=0;
if(qry1->exec())
{
   while(qry1->next()) {
    item_pics[i] = qry1->value(2).toString();
    item_name[i] = qry1->value(1).toString();
    item_price[i] = qry1->value(11).toString();
    Details[i] = qry1->value(12).toString();
   item_Ratings[i] = qry1->value(8).toString();
    i++;
   }
   w.connclose();
}
   int wi = ui->label_itempic->width();
   int h = ui->label_itempic->height();
   QPixmap pic(item_pics[count]);
   ui->label_itempic->setPixmap(pic.scaled(wi,h));
   ui->label_itemname_price->setText(item_name[count]);
   ui->label_price->setText("PRICE: $"+item_price[count]);
    ui->label_rating->setText("Average Rating : "+item_Ratings[count]);
}

void Show_items::initialise_array()
{
    int i=0;
    while(i<50)
    {
        item_pics[i].clear();
         item_name[i].clear();
         item_price[i].clear();
         Details[i].clear();
         i++;
    }
}

void Show_items::Home()
{
    int i = 0,j = 0,count_only = 0;
    QString onlyforyou[6];
    MainWindow w;
    if(!w.connopen())
    {
      qDebug()<< "database is not open";
    }
    w.connopen();
    QSqlQuery qry,qry_getdata,qry_onlyforyou,qry_;
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

Show_items::~Show_items()
{
    delete ui;
}


void Show_items::on_rB_automobile_2_clicked()
{
    count = 0;  //for next and previous
    show_products("automobile");

}
void Show_items::on_rB_baby_2_clicked()
{
    count = 0;  //for next and previous
    show_products("baby");
}

void Show_items::on_rB_Beauty_2_clicked()
{

    count = 0;  //for next and previous
    show_products("Beauty and personal care");
}

void Show_items::on_rB_books_2_clicked()
{
    count = 0;  //for next and previous
    show_products("Books");
}

void Show_items::on_rB_computors_2_clicked()
{

    count = 0;  //for next and previous
    show_products("Computers");
}

void Show_items::on_rB_electronics_2_clicked()
{

    count = 0;  //for next and previous
    show_products("Electronics");
}

void Show_items::on_rB_health_2_clicked()
{

    count = 0;  //for next and previous
    show_products("Health and Household");
}

void Show_items::on_rB_homekitchen_2_clicked()
{

    count = 0;  //for next and previous
    show_products("Home and kitchen");
}

void Show_items::on_rB_indus_scientific_2_clicked()
{

    count = 0;  //for next and previous
    show_products("Industrial and scientific");
}

void Show_items::on_rB_gaming_2_clicked()
{

            count = 0;  //for next and previous
            show_products("Gaming");

}
void Show_items::on_rB_watches_2_clicked()
{

    count = 0;  //for next and previous
    show_products("Watches");
}

void Show_items::on_rB_software_2_clicked()
{
    count = 0;  //for next and previous
    show_products("Software");

}

void Show_items::on_rB_sports_2_clicked()
{

    count = 0;  //for next and previous
    show_products("Sports and outdoors");
}

void Show_items::on_rB_Tools_2_clicked()
{

            count = 0;  //for next and previous
            show_products("Tools and Home improvement");
}

void Show_items::on_rB_furniture_2_clicked()
{

    count = 0;  //for next and previous
    show_products("Furniture");
}

void Show_items::on_pushButton_login_clicked()
{
    MainWindow w;
    QString Account;
    QString user = ui->lineEdit_username->text();
   QString password = ui->lineEdit_password->text();
    if(!w.connopen())
    {
        qDebug()<< "database is not open";
  }
  w.connopen();
   QSqlQuery qry1;
   qry1.prepare("select * from signup_data where username= '"+user+"' and password='"+password+"'");

   if(user=="Bazzarone" && password == "onlyone")  // for Admin account
     {

         Admin A;
         A.exec();
         ui->label_loginerror->setText(" ");
         ui->lineEdit_username->setText("");
         ui->lineEdit_password->setText("");
     }

    if(qry1.exec())
    {
      qry1.next();
      if(user==qry1.value(1).toString() && password==qry1.value(2).toString()){
        username_string = qry1.value(1).toString();
       Account = qry1.value(10).toString();

               if(Account=="personal"){
                      Shop shopping;
                      shopping.exec();
                       ui->label_loginerror->setText(" ");
                       ui->lineEdit_username->setText("");
                       ui->lineEdit_password->setText("");
                       w.connclose();
               }
               else if (Account=="business"){
                        Business_Account B;
                        B.exec();
                        ui->label_loginerror->setText("  ");
                        ui->lineEdit_username->setText("");
                        ui->lineEdit_password->setText("");
                        w.connclose();
               }
       }

     }



   else
   {
       ui->label_loginerror->setText("Username or Password not correct");
       ui->label_loginerror->setStyleSheet("QLabel {  color : red; }");
   }

}

void Show_items::on_pushButton_signup_clicked()
{
    signup s1;
    s1.exec();

}


void Show_items::on_pushButton_next_clicked()
{
    MainWindow w;
    QString catagery;

    if(ui->rB_automobile_2->isChecked())
       { catagery = "automobile";}
    if(ui->rB_baby_2->isChecked())
        catagery = "baby";
    if(ui->rB_Beauty_2->isChecked())
        catagery = "Beauty and personal care";
    if(ui->rB_books_2->isChecked())
        catagery = "Books";
    if(ui->rB_computors_2->isChecked())
        catagery = "Computers";
    if(ui->rB_electronics_2->isChecked())
        catagery = "Electronics";
    if(ui->rB_health_2->isChecked())
        catagery = "Health and Household";
    if(ui->rB_homekitchen_2->isChecked())
        catagery = "Home and kitchen";
    if(ui->rB_indus_scientific_2->isChecked())
        catagery = "Industrial and scientific";
    if(ui->rB_gaming_2->isChecked())
        catagery = "Gaming";
    if(ui->rB_watches_2->isChecked())
        catagery = "Watches";
    if(ui->rB_software_2->isChecked())
        catagery = "Software";
    if(ui->rB_sports_2->isChecked())
        catagery = "Sports and outdoors";
    if(ui->rB_Tools_2->isChecked())
        catagery = "Tools and Home improvement";
    if(ui->rB_furniture_2->isChecked())
        catagery = "Furniture";
   ////////////////////////////////////////////////////

    if(!w.connopen())
    {
        qDebug()<< "database is not open";
    }
    w.connopen();
    QSqlQuery * qry1 = new QSqlQuery(w.mydb);
    qry1->prepare("select * from items where catagories = '"+catagery+"'");
    int i=0;
    if(qry1->exec())
    {
       while(qry1->next()) {
        item_pics[i] = qry1->value(2).toString();
        item_name[i] = qry1->value(1).toString();
        item_price[i] = qry1->value(6).toString();
        i++;
       }
       w.connclose();
    }
    if(count==i-1)
    {
        QMessageBox::warning(this,"Error","This is the Last Item");
    }
    else{
       int wi = ui->label_itempic->width();
       int h = ui->label_itempic->height();
       count = count + 1;
       QPixmap pic(item_pics[count]);
       ui->label_itempic->setPixmap(pic.scaled(wi,h));
       ui->label_itemname_price->setText(item_name[count]);
       ui->label_price->setText("PRICE: $"+item_price[count]);
}
}

void Show_items::on_pushButton_previous_clicked()
{
    if(count==0){
        QMessageBox::warning(this,"Error","This is the First Item");
    }
    else{

    MainWindow w;
    QString catagery;

    if(ui->rB_automobile_2->isChecked())
       { catagery = "automobile";}
    if(ui->rB_baby_2->isChecked())
        catagery = "baby";
    if(ui->rB_Beauty_2->isChecked())
        catagery = "Beauty and personal care";
    if(ui->rB_books_2->isChecked())
        catagery = "Books";
    if(ui->rB_computors_2->isChecked())
        catagery = "Computers";
    if(ui->rB_electronics_2->isChecked())
        catagery = "Electronics";
    if(ui->rB_health_2->isChecked())
        catagery = "Health and Household";
    if(ui->rB_homekitchen_2->isChecked())
        catagery = "Home and kitchen";
    if(ui->rB_indus_scientific_2->isChecked())
        catagery = "Industrial and scientific";
    if(ui->rB_gaming_2->isChecked())
        catagery = "Gaming";
    if(ui->rB_watches_2->isChecked())
        catagery = "Watches";
    if(ui->rB_software_2->isChecked())
        catagery = "Software";
    if(ui->rB_sports_2->isChecked())
        catagery = "Sports and outdoors";
    if(ui->rB_Tools_2->isChecked())
        catagery = "Tools and Home improvement";
    if(ui->rB_furniture_2->isChecked())
        catagery = "Furniture";
    if(!w.connopen())
    {
        qDebug()<< "database is not open";
    }
    w.connopen();
    QSqlQuery * qry1 = new QSqlQuery(w.mydb);
    qry1->prepare("select * from items where catagories = '"+catagery+"'");
    int i=0;
    if(qry1->exec())
    {
       while(qry1->next()) {
        item_pics[i] = qry1->value(2).toString();
        item_name[i] = qry1->value(1).toString();
        item_price[i] = qry1->value(6).toString();
        i++;
       }
       w.connclose();
    }
       int wi = ui->label_itempic->width();
       int h = ui->label_itempic->height();
       count = count - 1;
       QPixmap pic(item_pics[count]);
       ui->label_itempic->setPixmap(pic.scaled(wi,h));
       ui->label_itemname_price->setText(item_name[count]);
       ui->label_price->setText("PRICE: $"+item_price[count]);
}
}



void Show_items::on_pushButton_addtobasket_clicked()
{
    QMessageBox::warning(this,"Error","You have to Login to buy Products" );
}

void Show_items::on_pushButton_clicked()
{
    ui->tab_Basket->close();
    ui->tabWidget->setCurrentIndex(1);
    ui->tab_Log_in->show();
}

void Show_items::on_pushButton_search_clicked()
{
    show_products(ui->lineEdit_search->text());
}

void Show_items::on_pushButton_orders1_clicked()
{
    ui->tab_Home->close();
    ui->tabWidget->setCurrentIndex(2);
    ui->tab_Categories->show();

    MainWindow w;
    if(!w.connopen())
    {
        qDebug()<< "database is not open";
    }
    w.connopen();
    int count_numberofitems = 0,i = 0;
   QString x,name;
   x = ui->label_Fname1->text();
   while (i<x.length()) {
       if(x[i] == '\n' )
           break;
       name.append(x[i]);
       i++;
   }
         QSqlQuery qry,qry_noofitems;
  qry.prepare("select * from items where productname = '"+name+"'");
  qry.exec();   qry.next();
  QString catagory = qry.value(4).toString();
  qry_noofitems.prepare("select * from items where catagories = '"+catagory+"'");
  qry_noofitems.exec();
  while (qry_noofitems.next()) {
      count_numberofitems++;
      if(name == qry_noofitems.value(1))
          break;
  }

  if(catagory == "automobile"){
      ui->rB_automobile_2->setChecked(true);
      ui->rB_automobile_2->clicked(true);
  }
  else if(catagory == "baby"){
      ui->rB_baby_2->setChecked(true);
      ui->rB_baby_2->clicked(true);
  }
  else if(catagory == "Beauty and personal care"){
      ui->rB_Beauty_2->setChecked(true);
      ui->rB_Beauty_2->clicked(true);
  }
  else if(catagory == "Books"){
      ui->rB_books_2->setChecked(true);
      ui->rB_books_2->clicked(true);
  }
  else if(catagory == "Computers"){
      ui->rB_computors_2->setChecked(true);
      ui->rB_computors_2->clicked(true);
  }
  else if(catagory == "Electronics"){
      ui->rB_electronics_2->setChecked(true);
      ui->rB_electronics_2->clicked(true);
  }
  else if(catagory == "Health and Household"){
      ui->rB_health_2->setChecked(true);
      ui->rB_health_2->clicked(true);
  }
  else if(catagory == "Home and kitchen"){
      ui->rB_homekitchen_2->setChecked(true);
      ui->rB_homekitchen_2->clicked(true);
  }
  else if(catagory == "Industrial and scientific"){
      ui->rB_indus_scientific_2->setChecked(true);
      ui->rB_indus_scientific_2->clicked(true);
  }
  else if(catagory == "Gaming"){
      ui->rB_gaming_2->setChecked(true);
      ui->rB_gaming_2->clicked(true);
  }
  else if(catagory == "Watches"){
      ui->rB_watches_2->setChecked(true);
      ui->rB_watches_2->clicked(true);
  }
  else if(catagory == "Software"){
      ui->rB_software_2->setChecked(true);
      ui->rB_software_2->clicked(true);
  }
  else if(catagory == "Sports and outdoors"){
      ui->rB_sports_2->setChecked(true);
      ui->rB_sports_2->clicked(true);
  }
  else if(catagory == "Tools and Home improvement"){
      ui->rB_Tools_2->setChecked(true);
      ui->rB_Tools_2->clicked(true);
  }
  else if(catagory == "Furniture"){
      ui->rB_furniture_2->setChecked(true);
      ui->rB_furniture_2->clicked(true);
  }


   i = 1;      // as we are on 1st item
  while (i<count_numberofitems) {
      ui->pushButton_next->clicked();
      i++;
  }

}

void Show_items::on_pushButton_orders2_clicked()
{
    ui->tab_Home->close();
    ui->tabWidget->setCurrentIndex(2);
    ui->tab_Categories->show();

    MainWindow w;
    if(!w.connopen())
    {
        qDebug()<< "database is not open";
    }
    w.connopen();
    int count_numberofitems = 0,i = 0;
   QString x,name;
   x = ui->label_Fname2->text();
   while (i<x.length()) {
       if(x[i] == '\n' )
           break;
       name.append(x[i]);
       i++;
   }
         QSqlQuery qry,qry_noofitems;
  qry.prepare("select * from items where productname = '"+name+"'");
  qry.exec();   qry.next();
  QString catagory = qry.value(4).toString();
  qry_noofitems.prepare("select * from items where catagories = '"+catagory+"'");
  qry_noofitems.exec();
  while (qry_noofitems.next()) {
      count_numberofitems++;
      if(name == qry_noofitems.value(1))
          break;
  }

   if(catagory == "automobile"){
      ui->rB_automobile_2->setChecked(true);
      ui->rB_automobile_2->clicked(true);
  }
  else if(catagory == "baby"){
      ui->rB_baby_2->setChecked(true);
      ui->rB_baby_2->clicked(true);
  }
  else if(catagory == "Beauty and personal care"){
      ui->rB_Beauty_2->setChecked(true);
      ui->rB_Beauty_2->clicked(true);
  }
  else if(catagory == "Books"){
      ui->rB_books_2->setChecked(true);
      ui->rB_books_2->clicked(true);
  }
  else if(catagory == "Computers"){
      ui->rB_computors_2->setChecked(true);
      ui->rB_computors_2->clicked(true);
  }
  else if(catagory == "Electronics"){
      ui->rB_electronics_2->setChecked(true);
      ui->rB_electronics_2->clicked(true);
  }
  else if(catagory == "Health and Household"){
      ui->rB_health_2->setChecked(true);
      ui->rB_health_2->clicked(true);
  }
  else if(catagory == "Home and kitchen"){
      ui->rB_homekitchen_2->setChecked(true);
      ui->rB_homekitchen_2->clicked(true);
  }
  else if(catagory == "Industrial and scientific"){
      ui->rB_indus_scientific_2->setChecked(true);
      ui->rB_indus_scientific_2->clicked(true);
  }
  else if(catagory == "Gaming"){
      ui->rB_gaming_2->setChecked(true);
      ui->rB_gaming_2->clicked(true);
  }
  else if(catagory == "Watches"){
      ui->rB_watches_2->setChecked(true);
      ui->rB_watches_2->clicked(true);
  }
  else if(catagory == "Software"){
      ui->rB_software_2->setChecked(true);
      ui->rB_software_2->clicked(true);
  }
  else if(catagory == "Sports and outdoors"){
      ui->rB_sports_2->setChecked(true);
      ui->rB_sports_2->clicked(true);
  }
  else if(catagory == "Tools and Home improvement"){
      ui->rB_Tools_2->setChecked(true);
      ui->rB_Tools_2->clicked(true);
  }
  else if(catagory == "Furniture"){
      ui->rB_furniture_2->setChecked(true);
      ui->rB_furniture_2->clicked(true);
  }


   i = 1;      // as we are on 1st item
  while (i<count_numberofitems) {
      ui->pushButton_next->clicked();
      i++;
  }

}

void Show_items::on_pushButton_orders3_clicked()
{
    ui->tab_Home->close();
    ui->tabWidget->setCurrentIndex(2);
    ui->tab_Categories->show();

    MainWindow w;
    if(!w.connopen())
    {
        qDebug()<< "database is not open";
    }
    w.connopen();
    int count_numberofitems = 0,i = 0;
   QString x,name;
   x = ui->label_Fname3->text();
   while (i<x.length()) {
       if(x[i] == '\n' )
           break;
       name.append(x[i]);
       i++;
   }
         QSqlQuery qry,qry_noofitems;
  qry.prepare("select * from items where productname = '"+name+"'");
  qry.exec();   qry.next();
  QString catagory = qry.value(4).toString();
  qry_noofitems.prepare("select * from items where catagories = '"+catagory+"'");
  qry_noofitems.exec();
  while (qry_noofitems.next()) {
      count_numberofitems++;
      if(name == qry_noofitems.value(1))
          break;
  }

   if(catagory == "automobile"){
      ui->rB_automobile_2->setChecked(true);
      ui->rB_automobile_2->clicked(true);
  }
  else if(catagory == "baby"){
      ui->rB_baby_2->setChecked(true);
      ui->rB_baby_2->clicked(true);
  }
  else if(catagory == "Beauty and personal care"){
      ui->rB_Beauty_2->setChecked(true);
      ui->rB_Beauty_2->clicked(true);
  }
  else if(catagory == "Books"){
      ui->rB_books_2->setChecked(true);
      ui->rB_books_2->clicked(true);
  }
  else if(catagory == "Computers"){
      ui->rB_computors_2->setChecked(true);
      ui->rB_computors_2->clicked(true);
  }
  else if(catagory == "Electronics"){
      ui->rB_electronics_2->setChecked(true);
      ui->rB_electronics_2->clicked(true);
  }
  else if(catagory == "Health and Household"){
      ui->rB_health_2->setChecked(true);
      ui->rB_health_2->clicked(true);
  }
  else if(catagory == "Home and kitchen"){
      ui->rB_homekitchen_2->setChecked(true);
      ui->rB_homekitchen_2->clicked(true);
  }
  else if(catagory == "Industrial and scientific"){
      ui->rB_indus_scientific_2->setChecked(true);
      ui->rB_indus_scientific_2->clicked(true);
  }
  else if(catagory == "Gaming"){
      ui->rB_gaming_2->setChecked(true);
      ui->rB_gaming_2->clicked(true);
  }
  else if(catagory == "Watches"){
      ui->rB_watches_2->setChecked(true);
      ui->rB_watches_2->clicked(true);
  }
  else if(catagory == "Software"){
      ui->rB_software_2->setChecked(true);
      ui->rB_software_2->clicked(true);
  }
  else if(catagory == "Sports and outdoors"){
      ui->rB_sports_2->setChecked(true);
      ui->rB_sports_2->clicked(true);
  }
  else if(catagory == "Tools and Home improvement"){
      ui->rB_Tools_2->setChecked(true);
      ui->rB_Tools_2->clicked(true);
  }
  else if(catagory == "Furniture"){
      ui->rB_furniture_2->setChecked(true);
      ui->rB_furniture_2->clicked(true);
  }


   i = 1;      // as we are on 1st item
  while (i<count_numberofitems) {
      ui->pushButton_next->clicked();
      i++;
  }

}

void Show_items::on_pushButton_ordero1_clicked()
{
    ui->tab_Home->close();
    ui->tabWidget->setCurrentIndex(2);
    ui->tab_Categories->show();

    MainWindow w;
    if(!w.connopen())
    {
        qDebug()<< "database is not open";
    }
    w.connopen();
    int count_numberofitems = 0,i = 0;
   QString x,name;
   x = ui->label_oname1->text();
   while (i<x.length()) {
       if(x[i] == '\n' )
           break;
       name.append(x[i]);
       i++;
   }
         QSqlQuery qry,qry_noofitems;
  qry.prepare("select * from items where productname = '"+name+"'");
  qry.exec();   qry.next();
  QString catagory = qry.value(4).toString();
  qry_noofitems.prepare("select * from items where catagories = '"+catagory+"'");
  qry_noofitems.exec();
  while (qry_noofitems.next()) {
      count_numberofitems++;
      if(name == qry_noofitems.value(1))
          break;
  }

   if(catagory == "automobile"){
      ui->rB_automobile_2->setChecked(true);
      ui->rB_automobile_2->clicked(true);
  }
  else if(catagory == "baby"){
      ui->rB_baby_2->setChecked(true);
      ui->rB_baby_2->clicked(true);
  }
  else if(catagory == "Beauty and personal care"){
      ui->rB_Beauty_2->setChecked(true);
      ui->rB_Beauty_2->clicked(true);
  }
  else if(catagory == "Books"){
      ui->rB_books_2->setChecked(true);
      ui->rB_books_2->clicked(true);
  }
  else if(catagory == "Computers"){
      ui->rB_computors_2->setChecked(true);
      ui->rB_computors_2->clicked(true);
  }
  else if(catagory == "Electronics"){
      ui->rB_electronics_2->setChecked(true);
      ui->rB_electronics_2->clicked(true);
  }
  else if(catagory == "Health and Household"){
      ui->rB_health_2->setChecked(true);
      ui->rB_health_2->clicked(true);
  }
  else if(catagory == "Home and kitchen"){
      ui->rB_homekitchen_2->setChecked(true);
      ui->rB_homekitchen_2->clicked(true);
  }
  else if(catagory == "Industrial and scientific"){
      ui->rB_indus_scientific_2->setChecked(true);
      ui->rB_indus_scientific_2->clicked(true);
  }
  else if(catagory == "Gaming"){
      ui->rB_gaming_2->setChecked(true);
      ui->rB_gaming_2->clicked(true);
  }
  else if(catagory == "Watches"){
      ui->rB_watches_2->setChecked(true);
      ui->rB_watches_2->clicked(true);
  }
  else if(catagory == "Software"){
      ui->rB_software_2->setChecked(true);
      ui->rB_software_2->clicked(true);
  }
  else if(catagory == "Sports and outdoors"){
      ui->rB_sports_2->setChecked(true);
      ui->rB_sports_2->clicked(true);
  }
  else if(catagory == "Tools and Home improvement"){
      ui->rB_Tools_2->setChecked(true);
      ui->rB_Tools_2->clicked(true);
  }
  else if(catagory == "Furniture"){
      ui->rB_furniture_2->setChecked(true);
      ui->rB_furniture_2->clicked(true);
  }


   i = 1;      // as we are on 1st item
  while (i<count_numberofitems) {
      ui->pushButton_next->clicked();
      i++;
  }

}

void Show_items::on_pushButton_ordero2_clicked()
{
    ui->tab_Home->close();
    ui->tabWidget->setCurrentIndex(2);
    ui->tab_Categories->show();

    MainWindow w;
    if(!w.connopen())
    {
        qDebug()<< "database is not open";
    }
    w.connopen();
    int count_numberofitems = 0,i = 0;
   QString x,name;
   x = ui->label_oname2->text();
   while (i<x.length()) {
       if(x[i] == '\n' )
           break;
       name.append(x[i]);
       i++;
   }
         QSqlQuery qry,qry_noofitems;
  qry.prepare("select * from items where productname = '"+name+"'");
  qry.exec();   qry.next();
  QString catagory = qry.value(4).toString();
  qry_noofitems.prepare("select * from items where catagories = '"+catagory+"'");
  qry_noofitems.exec();
  while (qry_noofitems.next()) {
      count_numberofitems++;
      if(name == qry_noofitems.value(1))
          break;
  }

   if(catagory == "automobile"){
      ui->rB_automobile_2->setChecked(true);
      ui->rB_automobile_2->clicked(true);
  }
  else if(catagory == "baby"){
      ui->rB_baby_2->setChecked(true);
      ui->rB_baby_2->clicked(true);
  }
  else if(catagory == "Beauty and personal care"){
      ui->rB_Beauty_2->setChecked(true);
      ui->rB_Beauty_2->clicked(true);
  }
  else if(catagory == "Books"){
      ui->rB_books_2->setChecked(true);
      ui->rB_books_2->clicked(true);
  }
  else if(catagory == "Computers"){
      ui->rB_computors_2->setChecked(true);
      ui->rB_computors_2->clicked(true);
  }
  else if(catagory == "Electronics"){
      ui->rB_electronics_2->setChecked(true);
      ui->rB_electronics_2->clicked(true);
  }
  else if(catagory == "Health and Household"){
      ui->rB_health_2->setChecked(true);
      ui->rB_health_2->clicked(true);
  }
  else if(catagory == "Home and kitchen"){
      ui->rB_homekitchen_2->setChecked(true);
      ui->rB_homekitchen_2->clicked(true);
  }
  else if(catagory == "Industrial and scientific"){
      ui->rB_indus_scientific_2->setChecked(true);
      ui->rB_indus_scientific_2->clicked(true);
  }
  else if(catagory == "Gaming"){
      ui->rB_gaming_2->setChecked(true);
      ui->rB_gaming_2->clicked(true);
  }
  else if(catagory == "Watches"){
      ui->rB_watches_2->setChecked(true);
      ui->rB_watches_2->clicked(true);
  }
  else if(catagory == "Software"){
      ui->rB_software_2->setChecked(true);
      ui->rB_software_2->clicked(true);
  }
  else if(catagory == "Sports and outdoors"){
      ui->rB_sports_2->setChecked(true);
      ui->rB_sports_2->clicked(true);
  }
  else if(catagory == "Tools and Home improvement"){
      ui->rB_Tools_2->setChecked(true);
      ui->rB_Tools_2->clicked(true);
  }
  else if(catagory == "Furniture"){
      ui->rB_furniture_2->setChecked(true);
      ui->rB_furniture_2->clicked(true);
  }


   i = 1;      // as we are on 1st item
  while (i<count_numberofitems) {
      ui->pushButton_next->clicked();
      i++;
  }

}

void Show_items::on_pushButton_ordero3_clicked()
{
    ui->tab_Home->close();
    ui->tabWidget->setCurrentIndex(2);
    ui->tab_Categories->show();

    MainWindow w;
    if(!w.connopen())
    {
        qDebug()<< "database is not open";
    }
    w.connopen();
    int count_numberofitems = 0,i = 0;
   QString x,name;
   x = ui->label_oname3->text();
   while (i<x.length()) {
       if(x[i] == '\n' )
           break;
       name.append(x[i]);
       i++;
   }
         QSqlQuery qry,qry_noofitems;
  qry.prepare("select * from items where productname = '"+name+"'");
  qry.exec();   qry.next();
  QString catagory = qry.value(4).toString();
  qry_noofitems.prepare("select * from items where catagories = '"+catagory+"'");
  qry_noofitems.exec();
  while (qry_noofitems.next()) {
      count_numberofitems++;
      if(name == qry_noofitems.value(1))
          break;
  }

  if(catagory == "automobile"){
      ui->rB_automobile_2->setChecked(true);
      ui->rB_automobile_2->clicked(true);
  }
  else if(catagory == "baby"){
      ui->rB_baby_2->setChecked(true);
      ui->rB_baby_2->clicked(true);
  }
  else if(catagory == "Beauty and personal care"){
      ui->rB_Beauty_2->setChecked(true);
      ui->rB_Beauty_2->clicked(true);
  }
  else if(catagory == "Books"){
      ui->rB_books_2->setChecked(true);
      ui->rB_books_2->clicked(true);
  }
  else if(catagory == "Computers"){
      ui->rB_computors_2->setChecked(true);
      ui->rB_computors_2->clicked(true);
  }
  else if(catagory == "Electronics"){
      ui->rB_electronics_2->setChecked(true);
      ui->rB_electronics_2->clicked(true);
  }
  else if(catagory == "Health and Household"){
      ui->rB_health_2->setChecked(true);
      ui->rB_health_2->clicked(true);
  }
  else if(catagory == "Home and kitchen"){
      ui->rB_homekitchen_2->setChecked(true);
      ui->rB_homekitchen_2->clicked(true);
  }
  else if(catagory == "Industrial and scientific"){
      ui->rB_indus_scientific_2->setChecked(true);
      ui->rB_indus_scientific_2->clicked(true);
  }
  else if(catagory == "Gaming"){
      ui->rB_gaming_2->setChecked(true);
      ui->rB_gaming_2->clicked(true);
  }
  else if(catagory == "Watches"){
      ui->rB_watches_2->setChecked(true);
      ui->rB_watches_2->clicked(true);
  }
  else if(catagory == "Software"){
      ui->rB_software_2->setChecked(true);
      ui->rB_software_2->clicked(true);
  }
  else if(catagory == "Sports and outdoors"){
      ui->rB_sports_2->setChecked(true);
      ui->rB_sports_2->clicked(true);
  }
  else if(catagory == "Tools and Home improvement"){
      ui->rB_Tools_2->setChecked(true);
      ui->rB_Tools_2->clicked(true);
  }
  else if(catagory == "Furniture"){
      ui->rB_furniture_2->setChecked(true);
      ui->rB_furniture_2->clicked(true);
  }


   i = 1;      // as we are on 1st item
  while (i<count_numberofitems) {
      ui->pushButton_next->clicked();
      i++;
  }

}
