#include "driverhomepage.h"
#include "ui_driverhomepage.h"

DriverHomePage::DriverHomePage(User* user, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DriverHomePage)
{
    ui->setupUi(this);
    connect(ui->CreateDriveButton, &QPushButton::clicked, this, [=]() {
        DriverCreateTrip* CreateTripPage = new DriverCreateTrip(user);
        CreateTripPage->show();
        this->hide();
    });
}

DriverHomePage::~DriverHomePage()
{
    delete ui;
}
