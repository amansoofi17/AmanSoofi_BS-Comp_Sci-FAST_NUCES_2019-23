#ifndef SIGNUP_H
#define SIGNUP_H
#include <QDialog>
#include<mainwindow.h>

namespace Ui {
class signup;
};
class signup : public QDialog
{
    Q_OBJECT
public:
    QString Acc_type;
public:
    explicit signup(QWidget *parent = nullptr);
    ~signup();

private slots:
    void on_pushButton_clicked();
    void on_radioButton_personal_clicked();

    void on_radioButton_business_clicked();
    
private:
    Ui::signup *ui;
};

#endif // SIGNUP_H
