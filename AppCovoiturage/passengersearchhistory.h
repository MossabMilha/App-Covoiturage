#ifndef PASSENGERSEARCHHISTORY_H
#define PASSENGERSEARCHHISTORY_H


#include "user.h"
#include "search.h"

#include <QWidget>
#include <QDebug>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QMessageBox>


namespace Ui {
class PassengerSearchHistory;
}

class PassengerSearchHistory : public QWidget
{
    Q_OBJECT

public:
    explicit PassengerSearchHistory(User* user, QWidget *parent = nullptr);
    ~PassengerSearchHistory();

private:
    Ui::PassengerSearchHistory *ui;
};

#endif // PASSENGERSEARCHHISTORY_H
