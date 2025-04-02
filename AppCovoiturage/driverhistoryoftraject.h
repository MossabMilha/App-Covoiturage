#ifndef DRIVERHISTORYOFTRAJECT_H
#define DRIVERHISTORYOFTRAJECT_H


#include "user.h"
#include "traject.h"


#include <QDebug>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QMessageBox>
#include <QWidget>
namespace Ui {
class DriverHistoryOfTraject;
}

class DriverHistoryOfTraject : public QWidget
{
    Q_OBJECT

public:
    explicit DriverHistoryOfTraject(User* user, QWidget *parent = nullptr);
    ~DriverHistoryOfTraject();

private:
    Ui::DriverHistoryOfTraject *ui;
};

#endif // DRIVERHISTORYOFTRAJECT_H
