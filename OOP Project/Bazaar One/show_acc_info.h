#ifndef SHOW_ACC_INFO_H
#define SHOW_ACC_INFO_H

#include <QDialog>
#include<mainwindow.h>
namespace Ui {
class show_acc_info;
}

class show_acc_info : public QDialog
{
    Q_OBJECT
public:
    void show_account_info(QString account);
public:
    explicit show_acc_info(QWidget *parent = nullptr);
    ~show_acc_info();

private:
    Ui::show_acc_info *ui;
};

#endif // SHOW_ACC_INFO_H
