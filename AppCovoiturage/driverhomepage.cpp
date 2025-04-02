#include "driverhomepage.h"
#include "ui_driverhomepage.h"

DriverHomePage::DriverHomePage(User* user, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DriverHomePage)
{
    ui->setupUi(this);
    int userId = user->getId();
    connect(ui->CreateDriveButton, &QPushButton::clicked, this, [this,userId]() {
        User user = User::getUserById(userId);
        DriverCreateTrip* CreateTripPage = new DriverCreateTrip(&user);
        CreateTripPage->show();
        this->hide();
    });
    connect(ui->HistoryOfTrajectButton, &QPushButton::clicked, this, [this,userId]() {
        User user = User::getUserById(userId);
        DriverHistoryOfTraject* HistoryTrajectPage = new DriverHistoryOfTraject(&user);
        HistoryTrajectPage->show();
        this->hide();
    });


}

DriverHomePage::~DriverHomePage()
{
    delete ui;
}
