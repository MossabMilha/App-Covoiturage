#include "passengerhomepage.h"
#include "ui_passengerhomepage.h"

PassengerHomePage::PassengerHomePage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PassengerHomePage)
{
    ui->setupUi(this);
}

PassengerHomePage::~PassengerHomePage()
{
    delete ui;
}
