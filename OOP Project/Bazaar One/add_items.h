#ifndef ADD_ITEMS_H
#define ADD_ITEMS_H

#include <QDialog>
#include<mainwindow.h>
#include<QSqlError>
#include<business_account.h>
namespace Ui {
class Add_items;
}

class Add_items : public QDialog
{
    Q_OBJECT
public:
     void radiobutton_click(int i);
    void show_products();

public:
    explicit Add_items(QWidget *parent = nullptr);
    ~Add_items();

private slots:


    void on_pushButton_add_clicked();

    void on_pushButton_edit_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_quantity_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_lineEdit_productname_textEdited(const QString &arg1);

    void on_lineEdit_picpath_textEdited(const QString &arg1);

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
    Ui::Add_items *ui;
};

#endif // ADD_ITEMS_H
