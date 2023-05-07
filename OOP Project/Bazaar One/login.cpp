#include "login.h"
#include "ui_login.h"
#include<QPixmap>
#include<QMessageBox>
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    MainWindow obj;

    if (!obj.connopen())
    {
   ui->label_4->setText("failed to connect");
    }
    else {
      ui->label_4->setText("database connected.......");
    }
        QPixmap pic(":/new/login/login image/image.png");
        int w = ui->label_pic->width();
        int h = ui->label_pic->height();
        ui->label_pic->setPixmap(pic.scaled(w,h));
}
login::~login()
{
    delete ui;
}
void login::on_pushButton_login_clicked()
{
    MainWindow obj;
    QString user = ui->lineEdit_->text();
   QString password = ui->lineEdit_password->text();
  int count1=0,count2=0;
  if(!obj.connopen())
  {
    qDebug()<< "database is not open";
  }
  obj.connopen();
   QSqlQuery qry1,qry2;
   qry1.prepare("select * from signup_data where username= '"+user+"' and password='"+password+"'");
   qry2.prepare("select name from signup_data where username= '"+user+"'");
   if(qry1.exec())
    {
       if(qry2.exec())
       {
           while(qry2.next())
           {
           count1++;
           }
           if(count1 == 1)
           {
               while(qry1.next())
               {
                   count2++;
               }
              if(count2 >= 1)
              {
              QMessageBox :: information(this,"HOME","login successfully");
              obj.connclose();
              }
              else
              {
                 QMessageBox :: warning(this,"error","username or password is in correct");
              }
           }
           else
           {
               QMessageBox :: warning(this,"error","this username is already taken");
           }
       }
   }

}
