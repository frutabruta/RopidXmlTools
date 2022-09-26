#ifndef ZASTAVKACIL_H
#define ZASTAVKACIL_H
#include "VDV301struktury/zastavka.h"
#include "VDV301struktury/linka.h"
//#include "VDV301struktury/spoj.h"


class ZastavkaCil
{
public:
    ZastavkaCil();
    Zastavka zastavka;
    Zastavka cil;
    Linka linka;
    QVector<Zastavka> nacestneZastavky;
    //Spoj spoj;
};

#endif // ZASTAVKACIL_H
