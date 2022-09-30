#ifndef SQLDOTAZYMODEL_H
#define SQLDOTAZYMODEL_H
#include "sqlpraceropid.h"

class SqlDotazyModel : public SqlPraceRopid
{
public:
    SqlDotazyModel();
    int stahniZastavkyNavaznySpoj(QVector<Zastavka> &docasnySeznamZastavek);
    int stahniSeznamSpojuBezNacestnych(QVector<QMap<QString,QString>> &spoje);



    QSqlQueryModel *stahniSeznamSpojuBezNacestnychNew();
    QSqlQueryModel *stahniZastavkyNavaznySpojNew();
};

#endif // SQLDOTAZYMODEL_H
