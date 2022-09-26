#ifndef SPECIALNIHLASENI_H
#define SPECIALNIHLASENI_H

#include <QObject>
class SpecialniHlaseni
{
public:
    SpecialniHlaseni();
    QString type="";
    QString title="";
    QString text="";
    QString displayName="";
    QVector<QString> mp3;
};

#endif // SPECIALNIHLASENI_H
