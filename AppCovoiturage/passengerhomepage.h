#ifndef PASSENGERHOMEPAGE_H
#define PASSENGERHOMEPAGE_H

#include <QWidget>
#include <QCoreApplication>
#include <QMessageBox>
#include <QDebug>
#include <QProcess>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QDialog>
#include <QDate>
#include "user.h"
namespace Ui {
class PassengerHomePage;
}

class PassengerHomePage : public QWidget
{
    Q_OBJECT

public:
    explicit PassengerHomePage(User* user, QWidget *parent = nullptr);
    ~PassengerHomePage();



private:
    Ui::PassengerHomePage *ui;
    QStringList cities = {
        "Amsterdam", "Athens", "Belgrade", "Berlin", "Bratislava", "Brussels", "Bucharest", "Budapest", "Chisinau", "Copenhagen",
        "Dublin", "Helsinki", "Kiev", "Lisbon", "Ljubljana", "London", "Luxembourg", "Madrid", "Malta", "Minsk", "Monaco",
        "Moscow", "Oslo", "Paris", "Podgorica", "Prague", "Reykjavik", "Riga", "Rome", "Sarajevo", "Skopje", "Sofia", "Stockholm",
        "Tallinn", "Tirana", "Valletta", "Vienna", "Vilnius", "Warsaw", "Zagreb"
    };
    QStringList places = {"1","2","3","4"};
};

#endif // PASSENGERHOMEPAGE_H
