#include "categories_items.h"
#include "ui_categories_items.h"
#include<shop.h>
Categories_items::Categories_items(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Categories_items)
{
    ui->setupUi(this);
    this->setFixedSize(1155,606);

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
    initialise_array();
    ui->label_FinalAmount->hide();
    ui->label->hide();
    Home();
}
void Categories_items::radiobutton_click(int i)
{
     if(i==1)
    ui->rB_automobile->click();
    else if(i==2)
    ui->rB_baby->click();
    else if(i==3)
    ui->rB_Beauty->click();
    else if(i==4)
    ui->rB_books->click();
    else if(i==5)
    ui->rB_computors->click();
    else if(i==6)
    ui->rB_electronics->click();
    else if(i==7)
    ui->rB_health->click();
    else if(i==8)
    ui->rB_homekitchen->click();
    else if(i==9)
    ui->rB_indus_scientific->click();
    else if(i==10)
    ui->rB_gaming->click();
    else if(i==11)
    ui->rB_watches->click();
    else if(i==12)
    ui->rB_software->click();
    else if(i==13)
    ui->rB_sports->click();
    else if(i==14)
    ui->rB_Tools->click();
    else if(i==15)
    ui->rB_furniture->click();

}

void Categories_items::order_display()
{
    int rows = 0,i=0;
    while (Basket_name[rows]!="") {
        rows++;
    }


    ui->tableWidget_baslet->setRowCount(rows);
    ui->tableWidget_baslet->setColumnCount(4);
    QStringList column_name;
    column_name<<"Product name" <<"Price of Single product" <<"Quantity" <<"Total Price of Product";
   ui->tableWidget_baslet->setHorizontalHeaderLabels(column_name);
    i=0;
    int j;
    int x;
   QTableWidgetItem *item;
   for (i=0;i<10;i++) {
       for (j=0;j<4;j++) {
            item = new QTableWidgetItem;
           if(j==0)
           {item->setText(Basket_name[i]);}
            else if(j==1)
            {   item->setText(Basket_itemprice[i]);}
           else if(j==2)
           {item->setText(item_quantity[i]);}
           else if(j==3){
                x = Basket_itemprice[i].toInt()*item_quantity[i].toInt();

               item->setText(QString::number(x));   }
           item->setFlags(item->flags()^Qt::ItemIsEditable); // do not give access to customers to edit their order at run time
           ui->tableWidget_baslet->setItem(i,j,item);


       }
   }
   ui->tableWidget_baslet->setStyleSheet("QTableWidget{"
                                         "background-color: #C0C0C0;"
                                         "alternate-background-color: #606060;"
                                         "selection-background-color: #282828;"
                                         "}");
   //cell item properties
    ui->tableWidget_baslet->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_baslet->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_baslet->setTextElideMode(Qt::ElideRight);
    //table properties
    ui->tableWidget_baslet->setShowGrid(true);
    ui->tableWidget_baslet->setGridStyle(Qt::DotLine);
    ui->tableWidget_baslet->setSortingEnabled(true);
    ui->tableWidget_baslet->setCornerButtonEnabled(true);
    //header properties
    ui->tableWidget_baslet->horizontalHeader()->setVisible(true);
    ui->tableWidget_baslet->horizontalHeader()->setDefaultSectionSize(150);
    ui->tableWidget_baslet->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_baslet->horizontalHeader()->setSectionResizeMode(QHeaderView :: Fixed);
}

int Categories_items::delete_item_0quantity()      //delete items with 0 quantity
{
    int q = 0;
    MainWindow w;
    if(!w.connopen())
    {
        qDebug()<< "database is not open";
    }
    w.connopen();
    QSqlQuery * qry1 = new QSqlQuery(w.mydb);
    qry1->prepare("select * from items where productname = '"+item_name[count]+"'");
    if(qry1->exec()){
        qry1->next();
    q = qry1->value(3).toInt();
    if(quantity < q )
    {}
    else
    {
        QMessageBox::warning(this,"Error","Number of Items available : "+ QString::number(q));
    }
    }
    return q;
}

void Categories_items::initialise_array()
{
    int i=0;
    while(i<50)
    {
        item_pics[i].clear();
         item_name[i].clear();
         item_price[i].clear();
         Details[i].clear();
         Basket_name[i].clear();
         item_quantity[i].clear();
         Basket_itemprice[i].clear();
         i++;
    }
}

void Categories_items::search_products(QString search)
{
    int count_search = 0,count1=0,i=0,j=0;
    QString Final_product,product,temp_name,temp_search;
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

    ui->tab_Home->close();
    ui->tabWidget->setCurrentIndex(1);
    ui->tab_categories->show();

     if(catagory == "automobile"){
        ui->rB_automobile->setChecked(true);
        ui->rB_automobile->clicked(true);
    }
    else if(catagory == "baby"){
        ui->rB_baby->setChecked(true);
        ui->rB_baby->clicked(true);
    }
    else if(catagory == "Beauty and personal care"){
        ui->rB_Beauty->setChecked(true);
        ui->rB_Beauty->clicked(true);
    }
    else if(catagory == "Books"){
        ui->rB_books->setChecked(true);
        ui->rB_books->clicked(true);
    }
    else if(catagory == "Computers"){
        ui->rB_computors->setChecked(true);
        ui->rB_computors->clicked(true);
    }
    else if(catagory == "Electronics"){
        ui->rB_electronics->setChecked(true);
        ui->rB_electronics->clicked(true);
    }
    else if(catagory == "Health and Household"){
        ui->rB_health->setChecked(true);
        ui->rB_health->clicked(true);
    }
    else if(catagory == "Home and kitchen"){
        ui->rB_homekitchen->setChecked(true);
        ui->rB_homekitchen->clicked(true);
    }
    else if(catagory == "Industrial and scientific"){
        ui->rB_indus_scientific->setChecked(true);
        ui->rB_indus_scientific->clicked(true);
    }
    else if(catagory == "Gaming"){
        ui->rB_gaming->setChecked(true);
        ui->rB_gaming->clicked(true);
    }
    else if(catagory == "Watches"){
        ui->rB_watches->setChecked(true);
        ui->rB_watches->clicked(true);
    }
    else if(catagory == "Software"){
        ui->rB_software->setChecked(true);
        ui->rB_software->clicked(true);
    }
    else if(catagory == "Sports and outdoors"){
        ui->rB_sports->setChecked(true);
        ui->rB_sports->clicked(true);
    }
    else if(catagory == "Tools and Home improvement"){
        ui->rB_Tools->setChecked(true);
        ui->rB_Tools->clicked(true);
    }
    else if(catagory == "Furniture"){
        ui->rB_furniture->setChecked(true);
        ui->rB_furniture->clicked(true);
    }

    i = 1;      // as we are on 1st item
    while (i<count_numberofitems) {
        ui->pushButton_next->clicked();
        i++;
    }


}

void Categories_items::show_products(QString catagery)
{
    MainWindow w;
    ui->label_numberofitems->setText(QString :: number(quantity));
    //  QSqlQueryModel * model = new QSqlQueryModel();
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

void Categories_items::Home()
{
    MainWindow w;
    int i = 0,j = 0,count_only = 0;
    QString onlyforyou[6];
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




Categories_items::~Categories_items()
{
    delete ui;
}





void Categories_items::on_rB_automobile_clicked()
{
    QString catagery = "automobile";
    count = 0;  //for next and previous
    quantity = 1;
    show_products(catagery);
}

void Categories_items::on_rB_baby_clicked()
{
    QString catagery = "baby";
    count = 0;  //for next and previous
    quantity = 1;
    show_products(catagery);
}

void Categories_items::on_rB_Beauty_clicked()
{
    QString catagery = "Beauty and personal care";
    count = 0;  //for next and previous
    quantity = 1;
    show_products(catagery);
}

void Categories_items::on_rB_books_clicked()
{
    QString catagery = "Books";
    count = 0;  //for next and previous
    quantity = 1;
    show_products(catagery);
}

void Categories_items::on_rB_computors_clicked()
{
    QString catagery = "Computers";
    count = 0;  //for next and previous
    quantity = 1;
    show_products(catagery);
}

void Categories_items::on_rB_electronics_clicked()
{
    QString catagery = "Electronics";
    count = 0;  //for next and previous
    quantity = 1;
    show_products(catagery);
}

void Categories_items::on_rB_health_clicked()
{
    QString catagery = "Health and Household";
    count = 0;  //for next and previous
    quantity = 1;
    show_products(catagery);
}

void Categories_items::on_rB_homekitchen_clicked()
{
    QString catagery = "Home and kitchen";
    count = 0;  //for next and previous
    quantity = 1;
    show_products(catagery);
}

void Categories_items::on_rB_indus_scientific_clicked()
{
    QString catagery = "Industrial and scientific";
    count = 0;  //for next and previous
    quantity = 1;
    show_products(catagery);
}

void Categories_items::on_rB_gaming_clicked()
{
    QString catagery = "Gaming";
    count = 0;  //for next and previous
    quantity = 1;
    show_products(catagery);
}

void Categories_items::on_rB_watches_clicked()
{
    QString catagery = "Watches";
    count = 0;  //for next and previous
    quantity = 1;
    show_products(catagery);
}

void Categories_items::on_rB_software_clicked()
{
    QString catagery = "Software";
    count = 0;  //for next and previous
    quantity = 1;
    show_products(catagery);
}

void Categories_items::on_rB_sports_clicked()
{
    QString catagery = "Sports and outdoors";
    count = 0;  //for next and previous
    quantity = 1;
    show_products(catagery);
}

void Categories_items::on_rB_Tools_clicked()
{
    QString catagery = "Tools and Home improvement";
    count = 0;  //for next and previous
    quantity = 1;
    show_products(catagery);
}

void Categories_items::on_rB_furniture_clicked()
{
    QString catagery = "Furniture";
    count = 0;//for next and previous
    quantity = 1;
    show_products(catagery);
}

void Categories_items::on_pushButton_next_clicked()
{
    MainWindow w;
    QString catagery;

    if(ui->rB_automobile->isChecked())
       { catagery = "automobile";}
    if(ui->rB_baby->isChecked())
        catagery = "baby";
    if(ui->rB_Beauty->isChecked())
        catagery = "Beauty and personal care";
    if(ui->rB_books->isChecked())
        catagery = "Books";
    if(ui->rB_computors->isChecked())
        catagery = "Computers";
    if(ui->rB_electronics->isChecked())
        catagery = "Electronics";
    if(ui->rB_health->isChecked())
        catagery = "Health and Household";
    if(ui->rB_homekitchen->isChecked())
        catagery = "Home and kitchen";
    if(ui->rB_indus_scientific->isChecked())
        catagery = "Industrial and scientific";
    if(ui->rB_gaming->isChecked())
        catagery = "Gaming";
    if(ui->rB_watches->isChecked())
        catagery = "Watches";
    if(ui->rB_software->isChecked())
        catagery = "Software";
    if(ui->rB_sports->isChecked())
        catagery = "Sports and outdoors";
    if(ui->rB_Tools->isChecked())
        catagery = "Tools and Home improvement";
    if(ui->rB_furniture->isChecked())
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

void Categories_items::on_pushButton_previous_clicked()
{
    if(count==0){
        QMessageBox::warning(this,"Error","This is the First Item");
    }
    else{

    MainWindow w;
    QString catagery;

    if(ui->rB_automobile->isChecked())
       { catagery = "automobile";}
    if(ui->rB_baby->isChecked())
        catagery = "baby";
    if(ui->rB_Beauty->isChecked())
        catagery = "Beauty and personal care";
    if(ui->rB_books->isChecked())
        catagery = "Books";
    if(ui->rB_computors->isChecked())
        catagery = "Computers";
    if(ui->rB_electronics->isChecked())
        catagery = "Electronics";
    if(ui->rB_health->isChecked())
        catagery = "Health and Household";
    if(ui->rB_homekitchen->isChecked())
        catagery = "Home and kitchen";
    if(ui->rB_indus_scientific->isChecked())
        catagery = "Industrial and scientific";
    if(ui->rB_gaming->isChecked())
        catagery = "Gaming";
    if(ui->rB_watches->isChecked())
        catagery = "Watches";
    if(ui->rB_software->isChecked())
        catagery = "Software";
    if(ui->rB_sports->isChecked())
        catagery = "Sports and outdoors";
    if(ui->rB_Tools->isChecked())
        catagery = "Tools and Home improvement";
    if(ui->rB_furniture->isChecked())
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


void Categories_items::on_pushButton_addtobasket_clicked()
{ 
    if(count_Basket>=50)
    {
        QMessageBox::warning(this,"Error","Product Buy Limit at a time is 50.\n You can delete or Buy Products in Basket Tab");
    }
   Basket_name[count_Basket] = item_name[count];
   item_quantity[count_Basket] =QString::number( quantity);


   if(Basket_name[count_Basket]==sale[0] || Basket_name[count_Basket]==sale[1] || Basket_name[count_Basket]==sale[2]){          //due to sale
   Basket_itemprice[count_Basket] =QString::number( (item_price[count].toInt() - ((item_price[count].toInt()*5)/100))   );  }
   else {
       Basket_itemprice[count_Basket] = item_price[count];
   }

   QMessageBox::information(this,"","\titem added to basket.\nIf you want to buy these products click on the tab Basket");

    count_Basket+=1;




}

void Categories_items::on_pushButton_plus_clicked()
{
    int q = 0;
    MainWindow w;
    if(!w.connopen())
    {
        qDebug()<< "database is not open";
    }
    w.connopen();
    QSqlQuery * qry1 = new QSqlQuery(w.mydb);
    qry1->prepare("select * from items where productname = '"+item_name[count]+"'");
    if(qry1->exec()){
        qry1->next();
    q = qry1->value(3).toInt();
    if(quantity <= q )
    {
        quantity+=1;
        ui->label_numberofitems->setText(QString :: number(quantity));
    }
    else
    {
        QMessageBox::warning(this,"Error","Number of Items available : "+ QString::number(q));
    }


    }
    }
void Categories_items::on_pushButton_minus_clicked()
{
    if(quantity >1 )
    {
        quantity-=1;
        ui->label_numberofitems->setText(QString :: number(quantity));
    }
    else
    {
        QMessageBox::warning(this,"Error","Select atleast one product");
    }

}

void Categories_items::on_tabWidget_tabBarClicked(int index)
{
    if(index == 2){
        ui->label_FinalAmount->hide();
        ui->label->hide();
        order_display();
    }
}

void Categories_items::on_pushButton_BUY_clicked()
{
    if(Basket_name[0]=="")
    {
        QMessageBox::warning(this,"","Please Buy atleast one Product to Proceed.");
        return;
    }
    MainWindow w;
    if(!w.connopen())
    {
        qDebug()<< "database is not open";
    }
    w.connopen();
    QSqlQuery qry1,qry2,qry_getdata,qry_delete,qry_buyerdata;
    QString Dname,Duser,path,id,Bname; //dealer name & username, Buyer name
    qry_buyerdata.prepare("select * from signup_data where username = '"+username_string+"'");
    qry_buyerdata.exec(); qry_buyerdata.next();
    Bname = qry_buyerdata.value(0).toString();

  int i=0,dealer_price=0,profit=0,Tprice = 0 , FinalAmount = 0;
    while(i<count_Basket){
    qry_getdata.prepare("select * from items where productname = '"+Basket_name[i]+"'");
      if(qry_getdata.exec())
      {
        qry_getdata.next();
        Dname = qry_getdata.value(9).toString();
        Duser = qry_getdata.value(5).toString();
        path  = qry_getdata.value(2).toString();
        id = qry_getdata.value(0).toString();
        dealer_price = qry_getdata.value(6).toInt();
      }
        Tprice = Basket_itemprice[i].toInt()*item_quantity[i].toInt();
        FinalAmount+=Tprice;
       profit = ((Basket_itemprice[i].toInt()-dealer_price)*item_quantity[i].toInt());


        if(  qry1.exec("update items set numberofitemsavailable = numberofitemsavailable -'"+item_quantity[i]+"' , numberoforders = numberoforders + '"+item_quantity[i]+"' where productname = '"+Basket_name[i]+"'"))
       {

            if(qry2.exec("insert into orders (productid,productname,productimage,price_individual,Quantity,dealername,dealerusername,price_total,Profit,buyername,buyerusername) values ('"+id+"','"+Basket_name[i]+"','"+path+"','"+Basket_itemprice[i]+"','"+item_quantity[i]+"','"+Dname+"','"+Duser+"','"+QString::number(Tprice)+"','"+QString::number(profit)+"' ,'"+Bname+"','"+username_string+"')"))
            {
            }

       }

        i++;
    }
    ui->label->show();
    ui->label_FinalAmount->show();
    ui->label_FinalAmount_2->setText("PKR"+QString::number(FinalAmount));
       i=0;
    while(i<50){
    Basket_name[i].clear();
    Basket_itemprice[i].clear();
    item_quantity[i].clear();
    i++;
    }
    count_Basket = 0;
    qry_delete.prepare("delete from items where numberofitemsavailable = 0");
    qry_delete.exec();
}



void Categories_items::on_pushButton_edit_clicked()
{
    int n = -1;         // as table widget has index = 0
     n = ui->tableWidget_baslet->currentRow();
    if(n<0)
    {
        QMessageBox::warning(this,"","Select any one Product");
        return;
    }
    MainWindow w;
    if(!w.connopen())
    {
        qDebug()<<"Database is not open";
    }
    w.connopen();
     QSqlQuery qry;
     qry.prepare("select * from items where productname = '"+Basket_name[n]+"'");
        QString catagory;
        if(qry.exec()){
            qry.next();
            catagory = qry.value(4).toString();
        }
        ui->tabWidget->setCurrentIndex(1);
        if(catagory == "automobile"){
            ui->rB_automobile->setChecked(true);
            ui->rB_automobile->clicked(true);
        }
        else if(catagory == "baby"){
            ui->rB_baby->setChecked(true);
            ui->rB_baby->clicked(true);
        }
        else if(catagory == "Beauty and personal care"){
            ui->rB_Beauty->setChecked(true);
            ui->rB_Beauty->clicked(true);
        }
        else if(catagory == "Books"){
            ui->rB_books->setChecked(true);
            ui->rB_books->clicked(true);
        }
        else if(catagory == "Computers"){
            ui->rB_computors->setChecked(true);
            ui->rB_computors->clicked(true);
        }
        else if(catagory == "Electronics"){
            ui->rB_electronics->setChecked(true);
            ui->rB_electronics->clicked(true);
        }
        else if(catagory == "Health and Household"){
            ui->rB_health->setChecked(true);
            ui->rB_health->clicked(true);
        }
        else if(catagory == "Home and kitchen"){
            ui->rB_homekitchen->setChecked(true);
            ui->rB_homekitchen->clicked(true);
        }
        else if(catagory == "Industrial and scientific"){
            ui->rB_indus_scientific->setChecked(true);
            ui->rB_indus_scientific->clicked(true);
        }
        else if(catagory == "Gaming"){
            ui->rB_gaming->setChecked(true);
            ui->rB_gaming->clicked(true);
        }
        else if(catagory == "Watches"){
            ui->rB_watches->setChecked(true);
            ui->rB_watches->clicked(true);
        }
        else if(catagory == "Software"){
            ui->rB_software->setChecked(true);
            ui->rB_software->clicked(true);
        }
        else if(catagory == "Sports and outdoors"){
            ui->rB_sports->setChecked(true);
            ui->rB_sports->clicked(true);
        }
        else if(catagory == "Tools and Home improvement"){
            ui->rB_Tools->setChecked(true);
            ui->rB_Tools->clicked(true);
        }
        else if(catagory == "Furniture"){
            ui->rB_furniture->setChecked(true);
            ui->rB_furniture->clicked(true);
        }

        while (1) {

        if(ui->label_itemname_price->text()==Basket_name[n])
        break;
        else
        ui->pushButton_next->clicked(true);
       }

        Basket_name[n].clear();
        item_quantity[n].clear();
        Basket_itemprice[n].clear();
       for (int i=0;i<49;i++) {             //49 because Basket[50] stores Basket[51]

                if(Basket_name[i]=="")
                {
                        Basket_name[i] = Basket_name[i+1];
                        item_quantity[i] = item_quantity[i+1];
                        Basket_itemprice[i] = Basket_itemprice[i+1];
                        Basket_name[i+1].clear();
                        item_quantity[i+1].clear();
                        Basket_itemprice[i+1].clear();

               }

       }
        count_Basket--;
}

void Categories_items::on_pushButton_rate_clicked()
{
    Ratings r;
    r.setModal(true);
    r.get_ratingProduct(item_name[count]);
    r.exec();
}


void Categories_items::on_pushButton_shopmore_clicked()
{
    ui->tab_Basket->close();
    ui->tabWidget->setCurrentIndex(1);
    ui->tab_categories->show();
}

void Categories_items::on_pushButton_search_clicked()
{
    search_products(ui->lineEdit_search->text());
}

void Categories_items::on_pushButton_orders1_clicked()
{
    ui->tab_Home->close();
    ui->tabWidget->setCurrentIndex(1);
    ui->tab_categories->show();

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
      ui->rB_automobile->setChecked(true);
      ui->rB_automobile->clicked(true);
  }
  else if(catagory == "baby"){
      ui->rB_baby->setChecked(true);
      ui->rB_baby->clicked(true);
  }
  else if(catagory == "Beauty and personal care"){
      ui->rB_Beauty->setChecked(true);
      ui->rB_Beauty->clicked(true);
  }
  else if(catagory == "Books"){
      ui->rB_books->setChecked(true);
      ui->rB_books->clicked(true);
  }
  else if(catagory == "Computers"){
      ui->rB_computors->setChecked(true);
      ui->rB_computors->clicked(true);
  }
  else if(catagory == "Electronics"){
      ui->rB_electronics->setChecked(true);
      ui->rB_electronics->clicked(true);
  }
  else if(catagory == "Health and Household"){
      ui->rB_health->setChecked(true);
      ui->rB_health->clicked(true);
  }
  else if(catagory == "Home and kitchen"){
      ui->rB_homekitchen->setChecked(true);
      ui->rB_homekitchen->clicked(true);
  }
  else if(catagory == "Industrial and scientific"){
      ui->rB_indus_scientific->setChecked(true);
      ui->rB_indus_scientific->clicked(true);
  }
  else if(catagory == "Gaming"){
      ui->rB_gaming->setChecked(true);
      ui->rB_gaming->clicked(true);
  }
  else if(catagory == "Watches"){
      ui->rB_watches->setChecked(true);
      ui->rB_watches->clicked(true);
  }
  else if(catagory == "Software"){
      ui->rB_software->setChecked(true);
      ui->rB_software->clicked(true);
  }
  else if(catagory == "Sports and outdoors"){
      ui->rB_sports->setChecked(true);
      ui->rB_sports->clicked(true);
  }
  else if(catagory == "Tools and Home improvement"){
      ui->rB_Tools->setChecked(true);
      ui->rB_Tools->clicked(true);
  }
  else if(catagory == "Furniture"){
      ui->rB_furniture->setChecked(true);
      ui->rB_furniture->clicked(true);
  }


   i = 1;      // as we are on 1st item
  while (i<count_numberofitems) {
      ui->pushButton_next->clicked();
      i++;
  }
}

void Categories_items::on_pushButton_orders2_clicked()
{
    ui->tab_Home->close();
    ui->tabWidget->setCurrentIndex(1);
    ui->tab_categories->show();

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
      ui->rB_automobile->setChecked(true);
      ui->rB_automobile->clicked(true);
  }
  else if(catagory == "baby"){
      ui->rB_baby->setChecked(true);
      ui->rB_baby->clicked(true);
  }
  else if(catagory == "Beauty and personal care"){
      ui->rB_Beauty->setChecked(true);
      ui->rB_Beauty->clicked(true);
  }
  else if(catagory == "Books"){
      ui->rB_books->setChecked(true);
      ui->rB_books->clicked(true);
  }
  else if(catagory == "Computers"){
      ui->rB_computors->setChecked(true);
      ui->rB_computors->clicked(true);
  }
  else if(catagory == "Electronics"){
      ui->rB_electronics->setChecked(true);
      ui->rB_electronics->clicked(true);
  }
  else if(catagory == "Health and Household"){
      ui->rB_health->setChecked(true);
      ui->rB_health->clicked(true);
  }
  else if(catagory == "Home and kitchen"){
      ui->rB_homekitchen->setChecked(true);
      ui->rB_homekitchen->clicked(true);
  }
  else if(catagory == "Industrial and scientific"){
      ui->rB_indus_scientific->setChecked(true);
      ui->rB_indus_scientific->clicked(true);
  }
  else if(catagory == "Gaming"){
      ui->rB_gaming->setChecked(true);
      ui->rB_gaming->clicked(true);
  }
  else if(catagory == "Watches"){
      ui->rB_watches->setChecked(true);
      ui->rB_watches->clicked(true);
  }
  else if(catagory == "Software"){
      ui->rB_software->setChecked(true);
      ui->rB_software->clicked(true);
  }
  else if(catagory == "Sports and outdoors"){
      ui->rB_sports->setChecked(true);
      ui->rB_sports->clicked(true);
  }
  else if(catagory == "Tools and Home improvement"){
      ui->rB_Tools->setChecked(true);
      ui->rB_Tools->clicked(true);
  }
  else if(catagory == "Furniture"){
      ui->rB_furniture->setChecked(true);
      ui->rB_furniture->clicked(true);
  }


   i = 1;      // as we are on 1st item
  while (i<count_numberofitems) {
      ui->pushButton_next->clicked();
      i++;
  }
}

void Categories_items::on_pushButton_orders3_clicked()
{
    ui->tab_Home->close();
    ui->tabWidget->setCurrentIndex(1);
    ui->tab_categories->show();

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
      ui->rB_automobile->setChecked(true);
      ui->rB_automobile->clicked(true);
  }
  else if(catagory == "baby"){
      ui->rB_baby->setChecked(true);
      ui->rB_baby->clicked(true);
  }
  else if(catagory == "Beauty and personal care"){
      ui->rB_Beauty->setChecked(true);
      ui->rB_Beauty->clicked(true);
  }
  else if(catagory == "Books"){
      ui->rB_books->setChecked(true);
      ui->rB_books->clicked(true);
  }
  else if(catagory == "Computers"){
      ui->rB_computors->setChecked(true);
      ui->rB_computors->clicked(true);
  }
  else if(catagory == "Electronics"){
      ui->rB_electronics->setChecked(true);
      ui->rB_electronics->clicked(true);
  }
  else if(catagory == "Health and Household"){
      ui->rB_health->setChecked(true);
      ui->rB_health->clicked(true);
  }
  else if(catagory == "Home and kitchen"){
      ui->rB_homekitchen->setChecked(true);
      ui->rB_homekitchen->clicked(true);
  }
  else if(catagory == "Industrial and scientific"){
      ui->rB_indus_scientific->setChecked(true);
      ui->rB_indus_scientific->clicked(true);
  }
  else if(catagory == "Gaming"){
      ui->rB_gaming->setChecked(true);
      ui->rB_gaming->clicked(true);
  }
  else if(catagory == "Watches"){
      ui->rB_watches->setChecked(true);
      ui->rB_watches->clicked(true);
  }
  else if(catagory == "Software"){
      ui->rB_software->setChecked(true);
      ui->rB_software->clicked(true);
  }
  else if(catagory == "Sports and outdoors"){
      ui->rB_sports->setChecked(true);
      ui->rB_sports->clicked(true);
  }
  else if(catagory == "Tools and Home improvement"){
      ui->rB_Tools->setChecked(true);
      ui->rB_Tools->clicked(true);
  }
  else if(catagory == "Furniture"){
      ui->rB_furniture->setChecked(true);
      ui->rB_furniture->clicked(true);
  }


   i = 1;      // as we are on 1st item
  while (i<count_numberofitems) {
      ui->pushButton_next->clicked();
      i++;
  }
}

void Categories_items::on_pushButton_ordero1_clicked()
{
    ui->tab_Home->close();
    ui->tabWidget->setCurrentIndex(1);
    ui->tab_categories->show();

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
      ui->rB_automobile->setChecked(true);
      ui->rB_automobile->clicked(true);
  }
  else if(catagory == "baby"){
      ui->rB_baby->setChecked(true);
      ui->rB_baby->clicked(true);
  }
  else if(catagory == "Beauty and personal care"){
      ui->rB_Beauty->setChecked(true);
      ui->rB_Beauty->clicked(true);
  }
  else if(catagory == "Books"){
      ui->rB_books->setChecked(true);
      ui->rB_books->clicked(true);
  }
  else if(catagory == "Computers"){
      ui->rB_computors->setChecked(true);
      ui->rB_computors->clicked(true);
  }
  else if(catagory == "Electronics"){
      ui->rB_electronics->setChecked(true);
      ui->rB_electronics->clicked(true);
  }
  else if(catagory == "Health and Household"){
      ui->rB_health->setChecked(true);
      ui->rB_health->clicked(true);
  }
  else if(catagory == "Home and kitchen"){
      ui->rB_homekitchen->setChecked(true);
      ui->rB_homekitchen->clicked(true);
  }
  else if(catagory == "Industrial and scientific"){
      ui->rB_indus_scientific->setChecked(true);
      ui->rB_indus_scientific->clicked(true);
  }
  else if(catagory == "Gaming"){
      ui->rB_gaming->setChecked(true);
      ui->rB_gaming->clicked(true);
  }
  else if(catagory == "Watches"){
      ui->rB_watches->setChecked(true);
      ui->rB_watches->clicked(true);
  }
  else if(catagory == "Software"){
      ui->rB_software->setChecked(true);
      ui->rB_software->clicked(true);
  }
  else if(catagory == "Sports and outdoors"){
      ui->rB_sports->setChecked(true);
      ui->rB_sports->clicked(true);
  }
  else if(catagory == "Tools and Home improvement"){
      ui->rB_Tools->setChecked(true);
      ui->rB_Tools->clicked(true);
  }
  else if(catagory == "Furniture"){
      ui->rB_furniture->setChecked(true);
      ui->rB_furniture->clicked(true);
  }


   i = 1;      // as we are on 1st item
  while (i<count_numberofitems) {
      ui->pushButton_next->clicked();
      i++;
  }
}

void Categories_items::on_pushButton_ordero2_clicked()
{
    ui->tab_Home->close();
    ui->tabWidget->setCurrentIndex(1);
    ui->tab_categories->show();

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
      ui->rB_automobile->setChecked(true);
      ui->rB_automobile->clicked(true);
  }
  else if(catagory == "baby"){
      ui->rB_baby->setChecked(true);
      ui->rB_baby->clicked(true);
  }
  else if(catagory == "Beauty and personal care"){
      ui->rB_Beauty->setChecked(true);
      ui->rB_Beauty->clicked(true);
  }
  else if(catagory == "Books"){
      ui->rB_books->setChecked(true);
      ui->rB_books->clicked(true);
  }
  else if(catagory == "Computers"){
      ui->rB_computors->setChecked(true);
      ui->rB_computors->clicked(true);
  }
  else if(catagory == "Electronics"){
      ui->rB_electronics->setChecked(true);
      ui->rB_electronics->clicked(true);
  }
  else if(catagory == "Health and Household"){
      ui->rB_health->setChecked(true);
      ui->rB_health->clicked(true);
  }
  else if(catagory == "Home and kitchen"){
      ui->rB_homekitchen->setChecked(true);
      ui->rB_homekitchen->clicked(true);
  }
  else if(catagory == "Industrial and scientific"){
      ui->rB_indus_scientific->setChecked(true);
      ui->rB_indus_scientific->clicked(true);
  }
  else if(catagory == "Gaming"){
      ui->rB_gaming->setChecked(true);
      ui->rB_gaming->clicked(true);
  }
  else if(catagory == "Watches"){
      ui->rB_watches->setChecked(true);
      ui->rB_watches->clicked(true);
  }
  else if(catagory == "Software"){
      ui->rB_software->setChecked(true);
      ui->rB_software->clicked(true);
  }
  else if(catagory == "Sports and outdoors"){
      ui->rB_sports->setChecked(true);
      ui->rB_sports->clicked(true);
  }
  else if(catagory == "Tools and Home improvement"){
      ui->rB_Tools->setChecked(true);
      ui->rB_Tools->clicked(true);
  }
  else if(catagory == "Furniture"){
      ui->rB_furniture->setChecked(true);
      ui->rB_furniture->clicked(true);
  }


   i = 1;      // as we are on 1st item
  while (i<count_numberofitems) {
      ui->pushButton_next->clicked();
      i++;
  }
}

void Categories_items::on_pushButton_ordero3_clicked()
{
    ui->tab_Home->close();
    ui->tabWidget->setCurrentIndex(1);
    ui->tab_categories->show();

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
      ui->rB_automobile->setChecked(true);
      ui->rB_automobile->clicked(true);
  }
  else if(catagory == "baby"){
      ui->rB_baby->setChecked(true);
      ui->rB_baby->clicked(true);
  }
  else if(catagory == "Beauty and personal care"){
      ui->rB_Beauty->setChecked(true);
      ui->rB_Beauty->clicked(true);
  }
  else if(catagory == "Books"){
      ui->rB_books->setChecked(true);
      ui->rB_books->clicked(true);
  }
  else if(catagory == "Computers"){
      ui->rB_computors->setChecked(true);
      ui->rB_computors->clicked(true);
  }
  else if(catagory == "Electronics"){
      ui->rB_electronics->setChecked(true);
      ui->rB_electronics->clicked(true);
  }
  else if(catagory == "Health and Household"){
      ui->rB_health->setChecked(true);
      ui->rB_health->clicked(true);
  }
  else if(catagory == "Home and kitchen"){
      ui->rB_homekitchen->setChecked(true);
      ui->rB_homekitchen->clicked(true);
  }
  else if(catagory == "Industrial and scientific"){
      ui->rB_indus_scientific->setChecked(true);
      ui->rB_indus_scientific->clicked(true);
  }
  else if(catagory == "Gaming"){
      ui->rB_gaming->setChecked(true);
      ui->rB_gaming->clicked(true);
  }
  else if(catagory == "Watches"){
      ui->rB_watches->setChecked(true);
      ui->rB_watches->clicked(true);
  }
  else if(catagory == "Software"){
      ui->rB_software->setChecked(true);
      ui->rB_software->clicked(true);
  }
  else if(catagory == "Sports and outdoors"){
      ui->rB_sports->setChecked(true);
      ui->rB_sports->clicked(true);
  }
  else if(catagory == "Tools and Home improvement"){
      ui->rB_Tools->setChecked(true);
      ui->rB_Tools->clicked(true);
  }
  else if(catagory == "Furniture"){
      ui->rB_furniture->setChecked(true);
      ui->rB_furniture->clicked(true);
  }


   i = 1;      // as we are on 1st item
  while (i<count_numberofitems) {
      ui->pushButton_next->clicked();
      i++;
  }
}

void Categories_items::on_radioButton_accounts_clicked()
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

void Categories_items::on_radioButton_orders_clicked()
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

void Categories_items::on_radioButton_fullname_clicked()
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

void Categories_items::on_radioButton_user_clicked()
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

void Categories_items::on_radioButton_pass_clicked()
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

void Categories_items::on_radioButton_email_clicked()
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

void Categories_items::on_radioButton_businessphone_phone_clicked()
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

void Categories_items::on_radioButton_address1_companyname_clicked()
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

void Categories_items::on_radioButton_address2_warehouse_clicked()
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


void Categories_items::on_pushButton_update_clicked()
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

void Categories_items::on_radioButton_Accoun_info_clicked()
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

void Categories_items::on_pushButton_Logout_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,"LOGOUT","Are You Sure You Want To Logout?",QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        hide();
        Shop s;
        s.on_pushButton_Logout_clicked();
    }

    else {
        return;
    }
}
