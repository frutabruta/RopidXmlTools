#ifndef BLABLA_H
#define BLABLA_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QDate>
#include "linka.h"
#include "obeh.h"
#include "specialnihlaseni.h"

class CestaUdaje
{

public:
    explicit CestaUdaje(QWidget *parent = nullptr);
    QString doorState="AllDoorsClosed";
    QString locationState="AtStop";
    QString routeDeviation="onroute";
    QString vehicleSubMode="BusSubmode";
    QString vehicleMode="regionalBus";
    QString razziaState="norazzia";
    bool VehicleStopRequested=false;
    bool prestupy=false;
    int indexAktZastavky;
    int indexSpojeNaObehu=0;;
    int pocetZastavek;
    Linka aktlinka;
    Obeh aktObeh;
    //int aktlinka;
    Spoj aktspoj;
    int cisloVozu=1234;
    int otevreneDvere=0;
    int vystupniStrana=0;
    bool zobrazZmenuPasma=false;
    int vymaz();
    QDate pracovniDatum;
    int pocetZastavekAktualnihoSpoje();
    Spoj aktualniSpojNaObehu();
    SpecialniHlaseni aktivniSpecialniHlaseni;
    bool jeSpecialniHlaseni=false;



signals:

public slots:
};

#endif // BLABLA_H
