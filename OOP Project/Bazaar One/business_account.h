#ifndef BUSINESS_ACCOUNT_H
#define BUSINESS_ACCOUNT_H

#include <QDialog>
#include<add_items.h>
namespace Ui {
class Business_Account;
}

class Business_Account : public QDialog
{
    Q_OBJECT

public:
    void show_products();

public:
    explicit Business_Account(QWidget *parent = nullptr);
    ~Business_Account();

public slots:
    void on_pushButton_Logout_clicked();



private slots:

    void on_rB_automobile_5_clicked();

    void on_rB_baby_5_clicked();

    void on_rB_Beauty_5_clicked();

    void on_rB_books_5_clicked();

    void on_rB_computors_5_clicked();

    void on_rB_electronics_5_clicked();

    void on_rB_health_5_clicked();

    void on_rB_homekitchen_5_clicked();

    void on_rB_indus_scientific_5_clicked();

    void on_rB_gaming_5_clicked();

    void on_rB_watches_5_clicked();

    void on_rB_software_5_clicked();

    void on_rB_sports_5_clicked();

    void on_rB_Tools_5_clicked();

    void on_rB_furniture_5_clicked();

    void on_tabWidget_tabBarClicked(int index);


    void on_pushButton_quantity_clicked();

    void on_pushButton_edit_clicked();

    void on_pushButton_delete_clicked();

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
    Ui::Business_Account *ui;
};

#endif // BUSINESS_ACCOUNT_H
