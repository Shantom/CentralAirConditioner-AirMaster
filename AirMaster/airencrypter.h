#ifndef AIRENCRYPTER_H
#define AIRENCRYPTER_H

#include <QCryptographicHash>
#include <QString>

class AirEncrypter
{
public:
    static QString encryptString(const QString& inStr);
private:
    AirEncrypter();

    static QCryptographicHash hasher;
};

#endif // AIRENCRYPTER_H
