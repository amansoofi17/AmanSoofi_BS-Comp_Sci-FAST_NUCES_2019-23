#include "show_acc_info.h"
#include "ui_show_acc_info.h"
show_acc_info::show_acc_info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::show_acc_info)
{
    ui->setupUi(this);
}

show_acc_info::~show_acc_info()
{
    delete ui;
}
void show_acc_info::show_account_info(QString account)
{
    MainWindow w;
    if(!w.connopen())
    {
        qDebug()<<"Database is not open";
    }
    w.connopen();
    QSqlQuery qry ;
    qry.prepare("select * from signup_data where username = '"+account+"'");
    if(qry.exec())
    {
        qry.next();
        ui->label_fullname->setText("Full Name: "+qry.value(0).toString());
        ui->label_username->setText("Username: "+qry.value(1).toString());
        ui->label_account->setText("Account Type: "+qry.value(10).toString());
        ui->label_B_email->setText("Email: "+qry.value(8).toString());

        if(qry.value(10).toString()=="business"){
        ui->label_company->setText("Company Name: "+qry.value(6).toString());
        ui->label_warehouse_add->setText("Warehouse Address"+qry.value(7).toString());
        ui->label_B_phone->setText("Phone Number: "+qry.value(9).toString());
        }
        else if(qry.value(10).toString()=="personal")
        {
            ui->label_company->setText("Address: "+qry.value(4).toString());
            ui->label_B_phone->setText("Phone Number: "+qry.value(3).toString());
            }
        }
        w.connclose();
    }

