#ifndef PASMO_H
#define PASMO_H
#include <QObject>


class Pasmo
{
public:
    Pasmo();
    QString nazev="";
    QString system="";
    static bool podminkaHlasitZmenuPasma(QVector<Pasmo> seznamPasem1, QVector<Pasmo> seznamPasem2);
    static QVector<Pasmo> vratPidPasma(QVector<Pasmo> vstup, QString hledanePasmo);
};

#endif // PASMO_H
