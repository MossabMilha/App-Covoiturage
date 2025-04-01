#include "encryption.h"

const QByteArray encryption::secretKey = "Dexter";


QString encryption::encrypt(const QString& input) {
    QByteArray byteArray = input.toUtf8();

    for (int i = 0; i < byteArray.size(); ++i) {
        byteArray[i] ^= secretKey[i % secretKey.size()];
    }
    return QString(byteArray.toBase64());
}


QString encryption::decrypt(const QString& input) {
    QByteArray byteArray = QByteArray::fromBase64(input.toUtf8());
    for (int i = 0; i < byteArray.size(); ++i) {
        byteArray[i] ^= secretKey[i % secretKey.size()];
    }
    return QString(byteArray);
}
