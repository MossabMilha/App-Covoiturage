#ifndef PASSENGERSHOWSEARCHRESULT_H
#define PASSENGERSHOWSEARCHRESULT_H

#include "traject.h"
#include "user.h"

#include <QWidget>
#include <QProcess>
#include <QDebug>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QList>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonParseError>
#include <QMessageBox>

namespace Ui {
class PassengerShowSearchResult;
}

class PassengerShowSearchResult : public QWidget
{
    Q_OBJECT

public:
    explicit PassengerShowSearchResult(User* user,int SearchId, QWidget *parent = nullptr);
    QList<int> getSearchResult(int searchId);
    ~PassengerShowSearchResult();

private:
    Ui::PassengerShowSearchResult *ui;
};

#endif // PASSENGERSHOWSEARCHRESULT_H
