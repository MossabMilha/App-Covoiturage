#include "signup.h"
#include "ui_signup.h"

SignUP::SignUP(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SignUP)
{
    ui->setupUi(this);
}

SignUP::~SignUP()
{
    delete ui;
}
