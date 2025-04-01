#ifndef START_H
#define START_H

#include "login.h"
#include "signup.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class start;
}
QT_END_NAMESPACE

class start : public QMainWindow
{
    Q_OBJECT

public:
    start(QWidget *parent = nullptr);
    ~start();

private:
    Ui::start *ui;
};
#endif // START_H
