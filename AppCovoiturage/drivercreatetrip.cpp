#include "drivercreatetrip.h"
#include "ui_drivercreatetrip.h"

DriverCreateTrip::DriverCreateTrip(User* user, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DriverCreateTrip)
{
    int userId = user->getId();
    ui->setupUi(this);
    ui->StartOfTrip->addItems(cities);
    ui->DestinationOfTrip->addItems(cities);
    ui->NombrePlaces->addItems(places);
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    connect(ui->CreateTrajectButton, &QPushButton::clicked, this, [this,userId]() {
        User user = User::getUserById(userId);
        // Capture user inputs
        QString startOfTrip = ui->StartOfTrip->currentText();
        QString destinationOfTrip = ui->DestinationOfTrip->currentText();
        int availableSeats = ui->NombrePlaces->currentText().toInt();
        QString carModel = ui->carModelEdit->text();
        double price = ui->priceSpinBox->value();
        QString dateTime = ui->dateTimeEdit->text();

        qDebug() << dateTime;

        // Create a new Traject object with the user inputs
        Traject newTraject(0, user.getId(), startOfTrip.toStdString(), destinationOfTrip.toStdString(), dateTime.toStdString(), availableSeats, price, carModel.toStdString());

        QString error;  // String to hold validation error messages

        // Validate the new traject
        if (newTraject.isValid(&error)) {
            // If valid, save the traject to the database
            newTraject.saveTrajectToDB();
            QMessageBox::information(this, "Success", "🎉 Traject Created Successfully!");
        } else {
            // If invalid, show the error messages
            QMessageBox::warning(this, "Validation Error", error);
        }
    });
}





DriverCreateTrip::~DriverCreateTrip()
{
    delete ui;
}
