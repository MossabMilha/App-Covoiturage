#ifndef SIGNUP_H
#define SIGNUP_H
#include "ui_signup.h"
#include "login.h"
#include "user.h"
#include "checkers.h"
#include "start.h"

#include <string>
#include <QWidget>
#include <QDialog>
#include <QRegularExpression>
#include <QMessageBox>
namespace Ui {
class SignUp;
}

class SignUp : public QWidget
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = nullptr);
    ~SignUp();
private slots:
    bool validateInputs(User newuser, QString confirmPassword, QMap<QString, QString>& ErrorMessages);

private:
    Ui::SignUp *ui;
};

#endif // SIGNUP_H
