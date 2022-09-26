#include "prestup.h"
#include <QObject>
Prestup::Prestup()
{
mainMode="";
subMode="";
connectionType="";
destinationName="";
//expectedDepartureTime="";
//scheduledDepartureTime="";
}



int Prestup::minutDoOdjezdu(QDateTime aktCas)
{
    int vysledek= -expectedDepartureTime.secsTo(aktCas)/60 ;

   // QDateTime::fromString(vstupniDokument.firstChildElement("CustomerInformationService.GetAllDataResponse").firstChildElement("AllData").firstChildElement("TimeStamp").firstChildElement("Value").firstChild().nodeValue() ,Qt::ISODate);


return vysledek;
}

QString Prestup::expectedDepartureTimeQString()
{
return expectedDepartureTime.toString(Qt::ISODate);
}

QString Prestup::scheduledDepartureTimeQString()
{
return scheduledDepartureTime.toString(Qt::ISODate);
}
