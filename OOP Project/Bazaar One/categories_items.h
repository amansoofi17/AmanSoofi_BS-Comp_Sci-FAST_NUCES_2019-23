#ifndef CATEGORIES_ITEMS_H
#define CATEGORIES_ITEMS_H

#include <QDialog>
#include<mainwindow.h>
#include<QDebug>
#include<QMessageBox>
#include <QTableWidget>
#include<QTableWidgetItem>
#include<ratings.h>


namespace Ui {
class Categories_items;
}

class Categories_items : public QDialog
{
    Q_OBJECT

public:
    void radiobutton_click(int i);
    QString item_pics[50]; // Catagory wise
    QString item_name[50];
    QString item_price[50];
    QString Details[50];
    QString item_Ratings[50];
    //Basket
    QString Basket_name[50];
    QString item_quantity[50];  // for basket
    QString Basket_itemprice[50];
    int quantity = 1;
    int count=0;
    int count_Basket = 0;
    void order_display();
    int delete_item_0quantity();
    void initialise_array();
    void search_products(QString);
    void show_products(QString);
    void Home();

private:

QTableWidget* m_pTableWidget;

QStringList m_TableHeader;

public slots:

void on_pushButton_orders1_clicked();

void on_pushButton_orders2_clicked();

void on_pushButton_orders3_clicked();

void on_pushButton_ordero1_clicked();

void on_pushButton_ordero2_clicked();

void on_pushButton_ordero3_clicked();

public:
    explicit Categories_items(QWidget *parent = nullptr);
    ~Categories_items();

private slots:


    void on_rB_automobile_clicked();

    void on_rB_baby_clicked();

    void on_rB_Beauty_clicked();

    void on_rB_books_clicked();

    void on_rB_computors_clicked();

    void on_rB_electronics_clicked();

    void on_rB_health_clicked();

    void on_rB_homekitchen_clicked();

    void on_rB_indus_scientific_clicked();

    void on_rB_gaming_clicked();

    void on_rB_watches_clicked();

    void on_rB_software_clicked();

    void on_rB_sports_clicked();

    void on_rB_Tools_clicked();

    void on_rB_furniture_clicked();

    void on_pushButton_next_clicked();

    void on_pushButton_previous_clicked();

    void on_pushButton_addtobasket_clicked();

    void on_pushButton_plus_clicked();

    void on_pushButton_minus_clicked();

   // void cellSelected(int nRow, int nCol);

    void on_tabWidget_tabBarClicked(int index);

    void on_pushButton_BUY_clicked();


    void on_pushButton_edit_clicked();



    void on_pushButton_rate_clicked();


    void on_pushButton_shopmore_clicked();

    void on_pushButton_search_clicked();

    void on_radioButton_accounts_clicked();

    void on_radioButton_orders_clicked();

    void on_radioButton_fullname_clicked();

    void on_radioButton_user_clicked();

    void on_radioButton_pass_clicked();

    void on_radioButton_email_clicked();

    void on_radioButton_businessphone_phone_clicked();

    void on_radioButton_address1_companyname_clicked();

    void on_radioButton_address2_warehouse_clicked();


    void on_pushButton_update_clicked();

    void on_radioButton_Accoun_info_clicked();

    void on_pushButton_Logout_clicked();



private:
    Ui::Categories_items *ui;
};

#endif // CATEGORIES_ITEMS_H
