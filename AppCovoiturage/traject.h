#ifndef TRAJECT_H
#define TRAJECT_H

#include <string>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>

class Traject
{
private:
    int id;
    int driver_id;
    std::string depart;
    std::string destination;
    std::string date_time;
    int available_seats;
    double price;
    std::string car_model;
    std::string status;

public:
    Traject(int id, int driver_id, std::string depart, std::string destination, std::string date_time,
            int available_seats, double price, std::string car_model, std::string status = "pending");

    // Getters
    int getId() const;
    int getDriverId() const;
    std::string getDepart() const;
    std::string getDestination() const;
    std::string getDateTime() const;
    int getAvailableSeats() const;
    double getPrice() const;
    std::string getCarModel() const;
    std::string getStatus() const;

    // Setters
    void setDepart(const std::string &newDepart);
    void setDestination(const std::string &newDestination);
    void setDateTime(const std::string &newDateTime);
    void setAvailableSeats(int seats);
    void setPrice(double newPrice);
    void setCarModel(const std::string &newCarModel);
    void setStatus(const std::string &newStatus);

    bool saveTrajectToDB();
    bool isValid(QString* error) const;
};

#endif // TRAJECT_H
