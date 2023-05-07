#include "ratings.h"
#include "ui_ratings.h"

void Ratings::get_ratingProduct(QString product_name)
{
    MainWindow w;
    if(!w.connopen())
    {
        qDebug()<<"Database is not open";
    }
    w.connopen();
     QSqlQuery qry;
     qry.prepare("select * from items where productname = '"+product_name+"'");
     QString pic,price,seller,details;
     if(qry.exec()){
         qry.next();
     pic = qry.value(2).toString();
     price = qry.value(11).toString();
     seller = qry.value(9).toString();
//     details = ;

    }
     ui->label_productname->setText(product_name);
     ui->label_details_price->setText(price);
     ui->label_seller->setText(seller);
     QPixmap p(pic);
     int wi = ui->label_pic->width();
     int h = ui->label_pic->height();
     ui->label_pic->setPixmap(p.scaled(wi,h));

}

Ratings::Ratings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ratings)
{
    ui->setupUi(this);
}

Ratings::~Ratings()
{
    delete ui;
}



void Ratings::on_spinBox_rating_valueChanged(int arg1)
{
    if(arg1<0)
    {
        arg1 = 0;
    }
    else if( arg1>4) {
        arg1 = 4;
    }
}

void Ratings::on_pushButton_skip_clicked()
{
    hide();
}

void Ratings::on_pushButton_proceed_clicked()
{   
    if(ui->spinBox_rating->text()=="0")
    {
        QMessageBox::warning(this,"Error","Please rate the product");
        return;
    }
    int rate = ui->spinBox_rating->text().toInt();
    QString product_name = ui->label_productname->text();
    MainWindow w;
    if(!w.connopen())
    {
        qDebug()<<"Database is not open";
    }
    w.connopen();
     QSqlQuery qry;
     qry.prepare("UPDATE items set averagerating = (averagerating + '"+QString::number(rate)+"')/2 WHERE productname = '"+product_name+"'");

     if(qry.exec())
    {
        QMessageBox::information(this,"Success","Succesfully rated");
        w.connclose();
        hide();
    }

}
