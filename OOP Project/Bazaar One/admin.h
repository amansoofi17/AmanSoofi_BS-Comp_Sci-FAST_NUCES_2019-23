#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>
#include<mainwindow.h>
#include<QDebug>
#include<QMessageBox>
#include<QPixmap>

#include<show_acc_info.h>
namespace Ui {
class Admin;
}

class Admin : public QDialog
{
    Q_OBJECT
public:
    void getAccounts();
    QString item_pics = "";
    QString item_name= "";
    QString item_price= "";
    QString item_catagory= "";
    QString number_available= "";
    QString new_items = "";
    QString dealer_name= "";
    QString dealer_email= "";
    QString dealer_username= "";
    QString details = "";
    int count_totalitems = 0;   //in database for viewing items
    int total_requests = 0;
    void requests();
    void show();
    void delete_data_fromrequests();
    void show_profit();

public:
    explicit Admin(QWidget *parent = nullptr);
    ~Admin();

private slots:
    void on_pushButton_deleteAcc_clicked();

    void on_pushButton_addtax_clicked();

    void on_pushButton_next_clicked();

    void on_pushButton_previous_clicked();

    void on_pushButton_Accept_clicked();

    void on_pushButton_Reject_clicked();

    void on_pushButton_Acc_Info_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_pushButton_Logout_clicked();

private:
    Ui::Admin *ui;
};

#endif // ADMIN_H
