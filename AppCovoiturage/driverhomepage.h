#ifndef DRIVERHOMEPAGE_H
#define DRIVERHOMEPAGE_H

#include "drivercreatetrip.h"
#include "driverhistoryoftraject.h"
#include "user.h"

#include <QWidget>

namespace Ui {
class DriverHomePage;
}

class DriverHomePage : public QWidget
{
    Q_OBJECT

public:
    explicit DriverHomePage(User* user, QWidget *parent = nullptr);
    ~DriverHomePage();

private:
    Ui::DriverHomePage *ui;
};

#endif // DRIVERHOMEPAGE_H
