#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include<signup.h>
#include<shop.h>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QtSql>
#include<QDebug>
#include<QFileInfo>
#include<show_items.h>
#include<global.h>
#include<business_account.h>
#include<admin.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
     QSqlDatabase mydb;
     void connclose()
    {
        mydb.close();
        mydb.removeDatabase(QSqlDatabase :: defaultConnection);
    }
    bool connopen()
    {
        mydb = QSqlDatabase ::addDatabase("QSQLITE");
       mydb.setDatabaseName("F:/data.db");
       if (!mydb.open())
       {
         qDebug()<<"failed to connect";
         return false;
       }
       else {
              qDebug()<<"connected.......";
              return true;
       }
    }
public:
    void Home();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pushButton_signup_clicked();

    void on_pushButton_login_clicked();

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


    void on_pushButton_clicked();


    void on_pushButton_search_clicked();

    void on_pushButton_orders1_clicked();

    void on_pushButton_ordero1_clicked();

    void on_pushButton_orders2_clicked();

    void on_pushButton_ordero2_clicked();

    void on_pushButton_orders3_clicked();

    void on_pushButton_ordero3_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
