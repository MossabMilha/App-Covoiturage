#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>

namespace Ui {
class SignUP;
}

class SignUP : public QDialog
{
    Q_OBJECT

public:
    explicit SignUP(QWidget *parent = nullptr);
    ~SignUP();

private:
    Ui::SignUP *ui;
};

#endif // SIGNUP_H
