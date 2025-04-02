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

namespace Ui {
class PassengerHomePage;
}

class PassengerHomePage : public QWidget
{
    Q_OBJECT

public:
    explicit PassengerHomePage(QWidget *parent = nullptr);
    ~PassengerHomePage();
private slots:
    void on_profilButton_clicked();      // Fonction du bouton Profil
    void on_deconnecterButton_clicked();
    void onDateButtonClicked();
    void onCalendarDateSelected(const QDate &date);
    void onVilleChanged();
    void onVilleArriveeChanged();
    void onNombrePlacesChanged();
    void on_appliquerButton_clicked();


private:
    Ui::PassengerHomePage *ui;
    void displayTheResult();
};

#endif // PASSENGERHOMEPAGE_H
