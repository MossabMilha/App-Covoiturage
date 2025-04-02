#ifndef DRIVERCREATETRIP_H
#define DRIVERCREATETRIP_H

#include <QWidget>
#include <QMessageBox>

#include "user.h"
#include "traject.h"

namespace Ui {
class DriverCreateTrip;
}

class DriverCreateTrip : public QWidget
{
    Q_OBJECT

public:
    explicit DriverCreateTrip(User* user, QWidget *parent = nullptr);
    ~DriverCreateTrip();

private:
    Ui::DriverCreateTrip *ui;
    QStringList cities = {
        "Amsterdam", "Athens", "Belgrade", "Berlin", "Bratislava", "Brussels", "Bucharest", "Budapest", "Chisinau", "Copenhagen",
        "Dublin", "Helsinki", "Kiev", "Lisbon", "Ljubljana", "London", "Luxembourg", "Madrid", "Malta", "Minsk", "Monaco",
        "Moscow", "Oslo", "Paris", "Podgorica", "Prague", "Reykjavik", "Riga", "Rome", "Sarajevo", "Skopje", "Sofia", "Stockholm",
        "Tallinn", "Tirana", "Valletta", "Vienna", "Vilnius", "Warsaw", "Zagreb"
    };
    QStringList places = {"1","2","3","4"};
};

#endif // DRIVERCREATETRIP_H
