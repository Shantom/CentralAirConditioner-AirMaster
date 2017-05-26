#include "airencrypter.h"

QString AirEncrypter::encryptString(const QString &inStr)
{
    hasher.addData(inStr.toUtf8());
    return QString(hasher.result());
}

AirEncrypter::AirEncrypter()
{

}

QCryptographicHash AirEncrypter::hasher(QCryptographicHash::Sha1);
