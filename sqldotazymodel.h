#ifndef SQLDOTAZYMODEL_H
#define SQLDOTAZYMODEL_H
#include "XmlRopidImportStream/sqlitezaklad.h"

class SqlDotazyModel : public SqLiteZaklad
{
public:
    SqlDotazyModel();

    QSqlQueryModel *stahniSeznamSpojuBezNacestnychNew();
    QSqlQueryModel *stahniZastavkyNavaznySpojNew();
    QSqlQueryModel *stahniSeznamVicenasobneSpoje();
    QSqlQueryModel *stahniSeznamPoznamky();
    QSqlQueryModel *stahniSeznamZastavekBezCisCisla();
    QSqlQueryModel *stahniSqlDotaz(QString dotaz);

signals:
    void signalSqlChyba(QString vstup);
};

#endif // SQLDOTAZYMODEL_H
