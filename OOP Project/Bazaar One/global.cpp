#include "global.h"
#include "ui_global.h"
#include<QString>
#include<QMessageBox>
global::global(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::global)
{
    ui->setupUi(this);

}

global::~global()
{
    delete ui;
}

QString username_string = "\0";
QString sale[3] = {"","",""};
