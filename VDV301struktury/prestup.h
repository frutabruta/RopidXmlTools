#ifndef PRESTUP_H
#define PRESTUP_H
#include <QObject>
#include <QDateTime>
#include "linka.h"


//VDV301 prestupy
class Prestup
{
public:
    Prestup();


    QString mainMode="";
    QString subMode="";
    QString connectionProperty="";
    QString connectionType="";
    QString destination="";
    Linka line;
    QString destinationName="";
    QDateTime expectedDepartureTime;
    QDateTime scheduledDepartureTime;
    QString platform="";
    int minutDoOdjezdu(QDateTime aktCas);
    QString expectedDepartureTimeQString();
    QString scheduledDepartureTimeQString();
};

#endif // PRESTUP_H
