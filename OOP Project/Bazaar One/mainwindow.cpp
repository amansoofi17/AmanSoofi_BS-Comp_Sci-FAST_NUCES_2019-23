#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPixmap>
#include<QMessageBox>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_loginerror->setText("");
    this->setFixedSize(1155,606);
    ui->tab_Home->setStyleSheet("backgound-color:black;");
    Home();
    QPixmap pic(":/new/login/login image/image.png");
int wi = ui->label_pic->width();
    int h = ui->label_pic->height();
    ui->label_pic->setPixmap(pic.scaled(wi,h));


}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_signup_clicked()
{
    signup *s1;
    s1 = new signup(this);
    s1->show();
}

void MainWindow::on_pushButton_login_clicked()
{
    QString user = ui->lineEdit_username->text();
   QString password = ui->lineEdit_password->text();
  if(!connopen())
  {
    qDebug()<< "database is not open";
  }
  connopen();
  QString Account;
  QSqlQuery qry1;


   qry1.prepare("select * from signup_data where username= '"+user+"' and password='"+password+"'");

   if(user=="Bazzarone" && password == "onlyone")  // for Admin account
     {

         Admin A;
         ui->label_loginerror->setText(" ");
         ui->lineEdit_username->setText("");
         ui->lineEdit_password->setText("");
         A.exec();
     }

    if(qry1.exec())
    {
      qry1.next();
      if(user==qry1.value(1).toString() && password==qry1.value(2).toString()){
        username_string = qry1.value(1).toString();
       Account = qry1.value(10).toString();

               if(Account=="personal"){
                      Shop shopping;
                      ui->label_loginerror->setText(" ");
                      ui->lineEdit_username->setText("");
                      ui->lineEdit_password->setText("");
                      shopping.exec();
                       connclose();
               }
               else if (Account=="business"){
                        Business_Account B;
                        ui->label_loginerror->setText(" ");
                        ui->lineEdit_username->setText("");
                        ui->lineEdit_password->setText("");
                        B.exec();
                        connclose();
               }
       }

     }
    else
    {
        ui->label_loginerror->setText("Username or Password not correct");
        ui->label_loginerror->setStyleSheet("QLabel {  color : red; }");
    }
}


void MainWindow::on_rB_automobile_clicked()
{
    hide();
    Show_items show;
    show.setModal(true);
    show.radiobutton_click(1);
    show.exec();
}

void MainWindow::on_rB_baby_clicked()
{
     hide();
    Show_items show(0);
    show.setModal(true);
    show.radiobutton_click(2);
    show.exec();
}
void MainWindow::on_rB_Beauty_clicked()
{
    hide();
    Show_items show;
    show.setModal(true);
    show.radiobutton_click(3);
    show.exec();
}

void MainWindow::on_rB_books_clicked()
{
    hide();
    Show_items show;
    show.setModal(true);
    show.radiobutton_click(4);
    show.exec();
}

void MainWindow::on_rB_computors_clicked()
{
    hide();
    Show_items show;
    show.setModal(true);
    show.radiobutton_click(5);
    show.exec();
}

void MainWindow::on_rB_electronics_clicked()
{
    hide();
    Show_items show;
    show.setModal(true);
    show.radiobutton_click(6);
    show.exec();
}

void MainWindow::on_rB_health_clicked()
{
    hide();
    Show_items show;
    show.setModal(true);
    show.radiobutton_click(7);
    show.exec();
}

void MainWindow::on_rB_homekitchen_clicked()
{
    hide();
    Show_items show;
    show.setModal(true);
    show.radiobutton_click(8);
    show.exec();
}

void MainWindow::on_rB_indus_scientific_clicked()
{
    hide();
    Show_items show;
    show.setModal(true);
    show.radiobutton_click(9);
    show.exec();
}

void MainWindow::on_rB_gaming_clicked()
{
    hide();
    Show_items show;
    show.setModal(true);
    show.radiobutton_click(10);
    show.exec();
}

void MainWindow::on_rB_watches_clicked()
{
    hide();
    Show_items show;
    show.setModal(true);
    show.radiobutton_click(11);
    show.exec();
}

void MainWindow::on_rB_software_clicked()
{
    hide();
    Show_items show;
    show.setModal(true);
    show.radiobutton_click(12);
    show.exec();
}

void MainWindow::on_rB_sports_clicked()
{
    hide();
    Show_items show;
    show.setModal(true);
    show.radiobutton_click(13);
    show.exec();
}

void MainWindow::on_rB_Tools_clicked()
{
    hide();
    Show_items show;
    show.setModal(true);
    show.radiobutton_click(14);
    show.exec();
}

void MainWindow::on_rB_furniture_clicked()
{
    hide();
    Show_items show;
    show.setModal(true);
    show.radiobutton_click(15);
    show.exec();
}





void MainWindow::on_pushButton_clicked()
{
    ui->tab_Basket->close();
    ui->tabWidget->setCurrentIndex(1);
    ui->tab_Log_in->show();
}


void MainWindow::on_pushButton_search_clicked()
{
    hide();
    Show_items show;
    show.setModal(true);
    show.search_products(ui->lineEdit_search->text());
    show.exec();
}
void MainWindow::Home()
{
    int i = 0,j = 0,count_only = 0;
    QString onlyforyou[6];
    if(!connopen())
    {
      qDebug()<< "database is not open";
    }
    connopen();
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
connclose();
}

void MainWindow::on_pushButton_orders1_clicked()
{
    hide();
    Show_items s;
    s.on_pushButton_orders1_clicked();
    s.exec();
}

void MainWindow::on_pushButton_ordero1_clicked()
{
    hide();

    Show_items s;
    s.on_pushButton_ordero1_clicked();
    s.exec();
}

void MainWindow::on_pushButton_orders2_clicked()
{
    hide();
    Show_items s;
    s.on_pushButton_orders2_clicked();
    s.exec();
}

void MainWindow::on_pushButton_ordero2_clicked()
{
    hide();
    Show_items s;
    s.on_pushButton_ordero2_clicked();
    s.exec();
}

void MainWindow::on_pushButton_orders3_clicked()
{
    hide();
    Show_items s;
    s.on_pushButton_orders3_clicked();
    s.exec();
}

void MainWindow::on_pushButton_ordero3_clicked()
{
    hide();
    Show_items s;
    s.on_pushButton_ordero3_clicked();
    s.exec();
}
