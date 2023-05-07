#ifndef SHOP_H
#define SHOP_H
#include<categories_items.h>
#include <QDialog>

namespace Ui {
class Shop;
}

class Shop : public QDialog
{
    Q_OBJECT

public:
    void Home();
public:
    explicit Shop(QWidget *parent = nullptr);
    ~Shop();
public slots:
     void on_pushButton_Logout_clicked();

private slots:


    void on_rB_artscraft_clicked();

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

    void on_pushButton_shopmore_2_clicked();

    void on_pushButton_edit_2_clicked();

    void on_pushButton_BUY_2_clicked();

    void on_pushButton_search_clicked();

    void on_pushButton_orders1_clicked();

    void on_pushButton_orders2_clicked();

    void on_pushButton_orders3_clicked();

    void on_pushButton_ordero1_clicked();

    void on_pushButton_ordero2_clicked();

    void on_pushButton_ordero3_clicked();

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



private:
    Ui::Shop *ui;
};

#endif // SHOP_H
