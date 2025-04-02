#include "traject.h"

// Constructor
Traject::Traject(int id, int driver_id, std::string depart, std::string destination, std::string date_time,
                 int available_seats, double price, std::string car_model, std::string status)
    : id(id), driver_id(driver_id), depart(depart), destination(destination), date_time(date_time),
    available_seats(available_seats), price(price), car_model(car_model), status(status) {}

// Getters
int Traject::getId() const { return id; }
int Traject::getDriverId() const { return driver_id; }
std::string Traject::getDepart() const { return depart; }
std::string Traject::getDestination() const { return destination; }
std::string Traject::getDateTime() const { return date_time; }
int Traject::getAvailableSeats() const { return available_seats; }
double Traject::getPrice() const { return price; }
std::string Traject::getCarModel() const { return car_model; }
std::string Traject::getStatus() const { return status; }

// Setters
void Traject::setDepart(const std::string &newDepart) { depart = newDepart; }
void Traject::setDestination(const std::string &newDestination) { destination = newDestination; }
void Traject::setDateTime(const std::string &newDateTime) { date_time = newDateTime; }
void Traject::setAvailableSeats(int seats) { available_seats = seats; }
void Traject::setPrice(double newPrice) { price = newPrice; }
void Traject::setCarModel(const std::string &newCarModel) { car_model = newCarModel; }
void Traject::setStatus(const std::string &newStatus) { status = newStatus; }

bool Traject::isValid(QString* error) const
{
    bool state = true;

    // Check if the price is greater than 0
    if (price <= 0) {
        *error += "The price must be greater than 0.\n";
        state = false;
    }

    // Check if start and destination are empty or the same
    if (depart.empty() || destination.empty()) {
        if (depart.empty()) {
            *error += "Start cannot be Empty.\n";
            state = false;
        }
        if (destination.empty()) {
            *error += "Destination cannot be Empty.\n";
            state = false;
        }
    } else if (depart == destination) {
        *error += "Start and destination cannot be the same.\n";
        state = false;
    }

    // Check if available_seats is greater than 0
    if (available_seats <= 0) {
        *error += "The number of available seats must be greater than 0.\n";
        state = false;
    }

    // // Check if the date is in the future
    // QDateTime currentDateTime = QDateTime::currentDateTime();
    // // Use the custom date format
    // QDateTime tripDateTime = QDateTime::fromString(QString::fromStdString(date_time), "dd-MMM-yy h:mm AP");

    // if (!tripDateTime.isValid()) {
    //     *error += "Invalid date format.\n";
    //     state = false;
    // } else if (tripDateTime < currentDateTime) {
    //     *error += "The trip date must be in the future.\n";
    //     state = false;
    // }

    return state;
}


bool Traject::saveTrajectToDB() {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qWarning() << "Database is not open!";
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO trajects (driver_id, depart, destination, date_time, available_seats, price, car_model, status) "
                  "VALUES (:driver_id, :depart, :destination, :date_time, :available_seats, :price, :car_model, :status)");

    query.bindValue(":driver_id", driver_id);
    query.bindValue(":depart", QString::fromStdString(depart));
    query.bindValue(":destination", QString::fromStdString(destination));
    query.bindValue(":date_time", QString::fromStdString(date_time));
    query.bindValue(":available_seats", available_seats);
    query.bindValue(":price", price);
    query.bindValue(":car_model", QString::fromStdString(car_model));
    query.bindValue(":status", QString::fromStdString(status));

    if (!query.exec()) {
        qWarning() << "Failed to insert traject:" << query.lastError().text();
        return false;
    }

    return true;
}
