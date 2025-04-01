#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <QString>
#include <QByteArray>
#include <QCryptographicHash>
#include <QDataStream>
#include <QFile>
#include <QCryptographicHash>
#include <QByteArray>

class encryption
{
public:
    static QString encrypt(const QString& input);
    static QString decrypt(const QString& input);

private:
    static const QByteArray secretKey;
};

#endif // ENCRYPTION_H
