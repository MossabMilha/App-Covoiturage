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

    connect(ui->SearchTraject, &QPushButton::clicked, this, [this, userId]() {
        User user = User::getUserById(userId);
        // Capture user inputs
        QString startOfTrip = ui->StartOfTrip->currentText();
        QString destinationOfTrip = ui->DestinationOfTrip->currentText();
        int availableSeats = ui->NombrePlaces->currentText().toInt();
        double price = ui->priceSpinBox->value();
        QString dateTime = ui->dateTimeEdit->text();

        // Create a new Search object with the user inputs
        Search newSearch(0, user.getId(), startOfTrip.toStdString(), destinationOfTrip.toStdString(), availableSeats, price, QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss").toStdString(), dateTime.toStdString());

        QString error;


        if (newSearch.isValid(&error)) {
            int searchId;
            if (newSearch.saveSearchToDB(searchId)) {
                qDebug()<<searchId;
                QMessageBox::information(this, "Success", "🎉 Search Created Successfully!");
                //Calling The Script

            } else {
                QMessageBox::warning(this, "Database Error", "Failed to save the search to the database.");
            }
        } else {

            QMessageBox::warning(this, "Validation Error", error);
        }
    });
    connect(ui->SearchHistory, &QPushButton::clicked, this, [this, userId]() {
        User user = User::getUserById(userId);
        PassengerSearchHistory* SearchHistory = new PassengerSearchHistory(&user);
        SearchHistory->show();
        this->hide();
    });
}

PassengerHomePage::~PassengerHomePage()
{
    delete ui;
}
