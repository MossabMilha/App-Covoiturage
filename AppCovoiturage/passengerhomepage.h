#ifndef PASSENGERHOMEPAGE_H
#define PASSENGERHOMEPAGE_H

#include <QWidget>

namespace Ui {
class PassengerHomePage;
}

class PassengerHomePage : public QWidget
{
    Q_OBJECT

public:
    explicit PassengerHomePage(QWidget *parent = nullptr);
    ~PassengerHomePage();

private:
    Ui::PassengerHomePage *ui;
};

#endif // PASSENGERHOMEPAGE_H
