#include "start.h"
#include "ui_start.h"
#include "login.h"
#include "signup.h"

start::start(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::start)
{
    ui->setupUi(this);
    connect(ui->LogInButton, &QPushButton::clicked, this, [=]() {
        LogIn *LogInWindow = new LogIn();
        LogInWindow->show();
        this->hide();

    });
    connect(ui->SignUpButton, &QPushButton::clicked, this, [=]() {
        SignUp *SignUpWindow = new SignUp();
        SignUpWindow->show();
        this->hide();
    });
}

start::~start()
{
    delete ui;
}
