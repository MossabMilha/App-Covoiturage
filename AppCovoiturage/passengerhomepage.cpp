#include "passengerhomepage.h"
#include "ui_passengerhomepage.h"



PassengerHomePage::PassengerHomePage(User* user,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PassengerHomePage)
{
    int userId = user->getId();
    ui->setupUi(this);
    ui->StartOfTrip->addItems(cities);
    ui->DestinationOfTrip->addItems(cities);
    ui->NombrePlaces->addItems(places);
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());



}

PassengerHomePage::~PassengerHomePage()
{
    delete ui;
}
