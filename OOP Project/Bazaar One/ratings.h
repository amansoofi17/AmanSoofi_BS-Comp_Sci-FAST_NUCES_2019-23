#ifndef RATINGS_H
#define RATINGS_H

#include <QDialog>
#include<mainwindow.h>
#include<QPixmap>
#include<categories_items.h>
namespace Ui {
class Ratings;
}

class Ratings : public QDialog
{
    Q_OBJECT

public:
    void get_ratingProduct(QString);
public:
    explicit Ratings(QWidget *parent = nullptr);
    ~Ratings();

private slots:
    void on_spinBox_rating_valueChanged(int arg1);

    void on_pushButton_skip_clicked();

    void on_pushButton_proceed_clicked();

private:
    Ui::Ratings *ui;
};

#endif // RATINGS_H
