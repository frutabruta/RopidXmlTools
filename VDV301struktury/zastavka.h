#ifndef SEZNAMZASTAVEK_H
#define SEZNAMZASTAVEK_H

#include "pasmo.h"
#include <QMainWindow>
#include <QObject>
#include "prestup.h"


class Zastavka
{
public:
    int StopIndex=0;
    int cisloCis=0;
    int cisloU=0;
    int cisloZ=0;
    QString ids="";
    QString StopName="";
    int DestinationCis=0;
    QString DepartureTime="";
    QString NameFront="";
    QString NameFront2="";
    QString NameSide="";
    QString NameLcd="";
    QString NameRear="";
    QString NameInner="";
    bool prestupVlak=0;
    bool prestupMetroA=0;
    bool prestupMetroB=0;
    bool prestupMetroC=0;
    bool prestupMetroD=0;
    bool prestupLetadlo=0;
    bool prestupPrivoz=0;
    bool naZnameni=0;
    bool zsol=0; //prujezdna konecna
    QString additionalTextMessage="";

    int cisloOis=0;
    int nacestna=0;
    Zastavka();
    QVector<Pasmo> seznamPasem;
    QVector<QString> seznamPiktogramu;
    QVector<Prestup> seznamPrestupu;
   // Zastavka *cil=nullptr;




};


#endif // SEZNAMZASTAVEK_H
