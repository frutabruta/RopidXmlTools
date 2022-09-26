#include "cestaudaje.h"
#include<iostream>
#include <QDebug>
using namespace std;
CestaUdaje::CestaUdaje(QWidget *parent)
{
qDebug()<<"CestaUdaje::CestaUdaje";
    vymaz();

}


int CestaUdaje::vymaz()
{
    qDebug()<<"CestaUdaje::vymaz()";

    //prestupy=false;

    indexSpojeNaObehu=0;


    //int aktlinka;
    aktspoj.vymaz();
    cisloVozu=1234;
    otevreneDvere=false;
    vystupniStrana=0;
    zobrazZmenuPasma=false;


    doorState="AllDoorsClosed";
    locationState="AtStop";
    VehicleStopRequested=false;
    indexAktZastavky=0;
    pocetZastavek=0;
    aktlinka.LineNumber="";
    aktObeh.vymaz();
    //aktspoj=0;
   return 1;
}

int CestaUdaje::pocetZastavekAktualnihoSpoje()
{
    int vysledek=0;
    vysledek=this->aktObeh.seznamSpoju.at(this->indexSpojeNaObehu).globalniSeznamZastavek.count();

    return vysledek;
}

Spoj CestaUdaje::aktualniSpojNaObehu()
{
  return this->aktObeh.seznamSpoju.at(this->indexSpojeNaObehu);
}


