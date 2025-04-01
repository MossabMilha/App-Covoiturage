#include "databasemanager.h"
#include <QCoreApplication>
#include <QDebug>

QSqlDatabase DataBaseManager::db;

bool DataBaseManager::openDatabase() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString currentDir = QCoreApplication::applicationDirPath();
    QString db_path = currentDir + "/../../../../DataBase/AppCovoiturage.db";
    db.setDatabaseName(db_path);

    if (!db.open()) {
        qDebug() << "Error: Unable to open database" << db.lastError();
        return false;
    }

    qDebug() << "Database connected successfully!";
    return true;
}

void DataBaseManager::closeDatabase() {
    if (db.isOpen()) {
        db.close();
        qDebug() << "Database closed successfully!";
    }
}

bool DataBaseManager::executeQuery(const QString &queryStr) {
    QSqlQuery query;
    if (!query.exec(queryStr)) {
        qDebug() << "Error executing query:" << query.lastError();
        return false;
    }
    return true;
}
