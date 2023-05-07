#include "signup.h"
#include "ui_signup.h"
#include<QMessageBox>
#include<qregexp.h>
#include<regex>
#include<QValidator>
#include<QDoubleValidator>
#include<QString>
#include<string.h>
#include<QLabel>
signup::signup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signup)
{
    ui->setupUi(this);
    this->setFixedSize(1155,606);
    MainWindow obj;
    ui->lineEdit_Paddress1_Bcomapanyname->hide();
    ui->lineEdit_Paddress2_Bwarehouseaddress->hide();
    ui->lineEdit_email->hide();
    ui->lineEdit_phone->hide();
    ui->lineEdit_phone->setValidator(new QDoubleValidator(this));

    if (!obj.connopen())
    {
  // ui->label_5->setText("failed to connect");
    }
    else {
      //ui->label_5->setText("database connected.......");
    }
}
signup::~signup()
{
    delete ui;
}
void signup::on_pushButton_clicked(){
    MainWindow obj;
    QString fullname,username,password,reenter,Bphone,Pphone,address1 = "none",address2 = "none",companyname= "none",
          warehouse= "none",email;

    fullname = ui->lineEdit_fullname->text();
    username = ui->lineEdit_username->text();
    password = ui->lineEdit_password->text();
    reenter = ui->lineEdit_reenterPass->text();
    email = ui->lineEdit_email->text();





    // all data completed
    if((fullname == NULL || username == NULL || password == NULL ||  reenter == NULL || email==NULL) ||  (ui->radioButton_personal->isChecked() && ui->radioButton_business->isChecked()))
   {
        QMessageBox :: warning(this,"error","complete data");
        return;
   }

    //password validation
    if(password.length()<8 || password.length()>15)
    {
        ui->label_passerror->setText("Password character Limit (8-15)!");
        ui->label_passerror->setStyleSheet("QLabel {  color : red; }");
        return;
    }
    if(password != reenter)
    {
        ui->label_reentererror->setText("invalid Re-enter password!");
        ui->label_reentererror->setStyleSheet("QLabel {  color : red; }");
        return;
    }

    //fullname only characters validation
         int i = 0,j = 0;
         while (i<fullname.length()) {

            j = 0;
             while (j<10) {

                 qDebug()<<fullname[i]<<"  "<<j;
                 if( fullname[i]==QString::number(j) )
                 {
                     ui->label_fullnameerror->setText("Numbers not allowed in Full Name!");
                     ui->label_fullnameerror->setStyleSheet("QLabel {  color : red; }");
                     return;
                 }  j++;
             }
             i++;
         }

         //email validation
     QRegExp pattern("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
     pattern.setCaseSensitivity(Qt::CaseInsensitive);
     pattern.setPatternSyntax(QRegExp::RegExp);
     bool check_email = pattern.exactMatch(email);
     if(!check_email){
         ui->label_emailerror->setText("Enter Correct Email Address! \n \tCorrect Format (xxxxx@xxxx.com) ");
         ui->label_emailerror->setStyleSheet("QLabel {  color : red; }");
         return;
     }

     if(Acc_type=="personal")
     {

         address1 = ui->lineEdit_Paddress1_Bcomapanyname->text();
         address2 = ui->lineEdit_Paddress2_Bwarehouseaddress->text();
         Bphone = "0";
         Pphone = ui->lineEdit_phone->text();    //for confirmation
         // phone validation
         if (Pphone.toLongLong() < 1000000000 || Pphone.toLongLong() > 3999999999    )
         {
             ui->label_phoneerror->setText("Please follow the correct number! \n \tformat 03xxxxxxxxx\n");
             ui->label_phoneerror->setStyleSheet("QLabel {  color : red; }");
             return;
         }

     }
     if(Acc_type=="business")
     {
         companyname = ui->lineEdit_Paddress1_Bcomapanyname->text();
         warehouse = ui->lineEdit_Paddress2_Bwarehouseaddress->text();
         Pphone = "0";
         Bphone = ui->lineEdit_phone->text();
         // phone validation
         if( Bphone.toLongLong() < 1000000000 || Bphone.toLongLong() > 3999999999   )
         {
             ui->label_phoneerror->setText("Please follow the correct number! \n \tformat 03xxxxxxxxx\n");
             ui->label_phoneerror->setStyleSheet("QLabel {  color : red; }");
             return;
         }

     }



                if(ui->radioButton_business->isChecked() && (companyname== "none" || warehouse== "none" || Bphone=="none"  )){
                  {
                    ui->label_Business->setText("complete Required Business Account Data!"); return; }
                    ui->label_Business->setStyleSheet("QLabel {  color : red; }");
                  }
                else if(ui->radioButton_personal->isChecked() && (address1== "none" ||Pphone=="none")){
                  {
                    ui->label_Business->setText("complete Required Personal Account Data!"); return;  }
                    ui->label_Business->setStyleSheet("QLabel {  color : red; }");
                   }

                if(!obj.connopen())
                     qDebug()<< "database is not open";

                            obj.connopen();
                            QSqlQuery qry1,qry2;
                            qry1.prepare("insert into signup_data (fullname,username,password,phonenumber,Address1,Address2,companyname,warehouseaddress,email,businessphonenumber,accounttype) values ('"+fullname+"','"+username+"','"+password+"','"+Pphone+"','"+address1+"','"+address2+"','"+companyname+"','"+warehouse+"','"+email+"','"+Bphone+"','"+Acc_type+"')");
                            qry2.prepare("select username from signup_data where username='"+username+"'");
                                    if(qry2.exec())
                                {
                                    int count=0;
                                    while(qry2.next())
                                        count++;

                                  if(count==0)
                                  {
                                      if(qry1.exec())
                                      {

                                         QMessageBox :: information(this,"Signup","You have succesfully signed up");

                                         obj.connclose();
                                         hide();

                                      }

                                }
                                else{
                                    ui->label_usernameerror->setText("This username is already taken!");
                                    ui->label_usernameerror->setStyleSheet("QLabel {  color : red; }");
                                     }

                                    }
}
void signup::on_radioButton_personal_clicked()
{
    Acc_type="personal";
    ui->label_Business->setText("Required for persnol account*");
    ui->label_Paddress1_Bcomapanyname->setText("Address 1");
    ui->label_Paddress2_Bwarehouseaddress->setText("Address 2 (optional)");
    ui->label_email->setText("Persnol Email");
    ui->label_phone->setText("Persnol Phone");
    ui->lineEdit_Paddress1_Bcomapanyname->show();
    ui->lineEdit_Paddress2_Bwarehouseaddress->show();
    ui->lineEdit_email->show();
    ui->lineEdit_phone->show();
}
void signup::on_radioButton_business_clicked()
{
    Acc_type="business";
    ui->label_Business->setText("Required for Business account*");
    ui->label_Paddress1_Bcomapanyname->setText("Company name");
    ui->label_Paddress2_Bwarehouseaddress->setText("Warehouseaddress");
    ui->label_email->setText("Business Email");
    ui->label_phone->setText("Business Phone");
    ui->lineEdit_Paddress1_Bcomapanyname->show();
    ui->lineEdit_Paddress2_Bwarehouseaddress->show();
    ui->lineEdit_email->show();
    ui->lineEdit_phone->show();
}
