#ifndef SHOW_ITEMS_H
#define SHOW_ITEMS_H
#include<mainwindow.h>
#include <QDialog>
#include<shop.h>
#include<signup.h>
#include<global.h>
namespace Ui {
class Show_items;
}

class Show_items : public QDialog
{
    Q_OBJECT

public:

    void radiobutton_click(int i);
    QString item_pics[50];
    QString item_name[50];
    QString item_price[50];
    QString Details[50];
    QString item_Ratings[50];
    int count=0;
    void search_products(QString);
    void show_products(QString);
    void initialise_array();
    void Home();















public:
    explicit Show_items(QWidget *parent = nullptr);
    ~Show_items();

public slots:

    void on_pushButton_orders1_clicked();

    void on_pushButton_orders2_clicked();

    void on_pushButton_orders3_clicked();

    void on_pushButton_ordero1_clicked();

    void on_pushButton_ordero2_clicked();

    void on_pushButton_ordero3_clicked();

private slots:

    void on_rB_automobile_2_clicked();

    void on_rB_baby_2_clicked();

    void on_rB_Beauty_2_clicked();

    void on_rB_books_2_clicked();

    void on_rB_computors_2_clicked();

    void on_rB_electronics_2_clicked();

    void on_rB_health_2_clicked();

    void on_rB_homekitchen_2_clicked();

    void on_rB_indus_scientific_2_clicked();

    void on_rB_gaming_2_clicked();

    void on_rB_watches_2_clicked();

    void on_rB_software_2_clicked();

    void on_rB_sports_2_clicked();

    void on_rB_Tools_2_clicked();

    void on_rB_furniture_2_clicked();

    void on_pushButton_login_clicked();

    void on_pushButton_signup_clicked();

    void on_pushButton_next_clicked();

    void on_pushButton_previous_clicked();

    void on_pushButton_addtobasket_clicked();

    void on_pushButton_clicked();

    void on_pushButton_search_clicked();


private:
    Ui::Show_items *ui;

};

#endif // SHOW_ITEMS_H

