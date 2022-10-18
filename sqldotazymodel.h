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
};

#endif // SQLDOTAZYMODEL_H
