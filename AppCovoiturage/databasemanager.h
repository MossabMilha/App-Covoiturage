#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QCoreApplication>

class DataBaseManager
{
public:
    static bool openDatabase();
    static void closeDatabase();
    static bool executeQuery(const QString &queryStr);

private:
    static QSqlDatabase db;
};


#endif // DATABASEMANAGER_H
