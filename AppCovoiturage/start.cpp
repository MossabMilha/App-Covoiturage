#include "start.h"
#include "ui_start.h"

start::start(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::start)
{
    ui->setupUi(this);
    connect(ui->LogInButton, &QPushButton::clicked, this, [=]() {
        LogIn *LogInWindow = new LogIn(this);
        LogInWindow->show();
        this->hide();
    });
    connect(ui->SignUpButton, &QPushButton::clicked, this, [=]() {
        SignUP *SignUpWindow = new SignUP(this);
        SignUpWindow->show();
        this->hide();
    });
}

start::~start()
{
    delete ui;
}
