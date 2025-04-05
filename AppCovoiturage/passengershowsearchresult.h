#ifndef PASSENGERSHOWSEARCHRESULT_H
#define PASSENGERSHOWSEARCHRESULT_H

#include <QWidget>
#include "user.h"
namespace Ui {
class PassengerShowSearchResult;
}

class PassengerShowSearchResult : public QWidget
{
    Q_OBJECT

public:
    explicit PassengerShowSearchResult(User* user,int SearchId, QWidget *parent = nullptr);
    ~PassengerShowSearchResult();

private:
    Ui::PassengerShowSearchResult *ui;
};

#endif // PASSENGERSHOWSEARCHRESULT_H
