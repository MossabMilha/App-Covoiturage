#include "driverhomepage.h"
#include "ui_driverhomepage.h"
#include "login.h"  // ➕ Ajoute ceci pour accéder à la classe Login

DriverHomePage::DriverHomePage(User* user, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DriverHomePage)
    , currentUser(user) // Sauvegarde le pointeur
{
    ui->setupUi(this);

    connect(ui->CreateDriveButton, &QPushButton::clicked, this, [this]() {
        DriverCreateTrip* CreateTripPage = new DriverCreateTrip(currentUser); // Utilise le pointeur sauvegardé
        CreateTripPage->show();
        this->hide();
    });

    connect(ui->HistoryOfTrajectButton, &QPushButton::clicked, this, [this]() {
        DriverHistoryOfTraject* HistoryTrajectPage = new DriverHistoryOfTraject(currentUser); // ✅
        HistoryTrajectPage->show();
        this->hide();
    });

    connect(ui->logoutBtn, &QPushButton::clicked, this, [this]() {
        LogIn* loginPage = new LogIn();
        loginPage->show();
        this->close();
    });
}


DriverHomePage::~DriverHomePage()
{
    delete ui;
}
