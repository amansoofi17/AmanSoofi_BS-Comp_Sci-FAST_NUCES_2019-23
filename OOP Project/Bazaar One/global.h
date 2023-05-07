#ifndef GLOBAL_H
#define GLOBAL_H
#include<QtGlobal>
//#include<qtglobal.h>
#include <QDialog>
#include<mainwindow.h>
QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE
//

//
#define MAGIC_NUM 42
extern QString username_string;
extern QString sale[3];
namespace Ui {
class global;
}

class global : public QDialog
{
    Q_OBJECT
public:
void datadb();
public:
    explicit global(QWidget *parent = nullptr);
    ~global();
private:
    Ui::global *ui;
};

#endif // GLOBAL_H


