#include "sqldotazymodel.h"

SqlDotazyModel::SqlDotazyModel()
{

}


QSqlQueryModel* SqlDotazyModel::stahniSeznamCisCisloShoda()
{
    qDebug() <<  Q_FUNC_INFO;

    pripoj();
    QSqlQueryModel *model = new QSqlQueryModel;

    QString queryString2="";
    queryString2+="SELECT z.u, z.z, z.cis AS zcis, t.cis AS tcis, z.n ";
    queryString2+="FROM z ";
    queryString2+="LEFT JOIN t ON z.u=t.u AND z.z=t.z ";
    queryString2+="WHERE z.cis<>t.cis ";


    qDebug().noquote()<<queryString2;

    model->setQuery(queryString2);
    /*
    model->setHeaderData(0, Qt::Horizontal, tr("uzel"));
    model->setHeaderData(1, Qt::Horizontal, tr("sloupek"));
    model->setHeaderData(2, Qt::Horizontal, tr("kj"));
    model->setHeaderData(3, Qt::Horizontal, tr("název"));
    model->setHeaderData(4, Qt::Horizontal, tr("číslo\nCIS"));
    model->setHeaderData(5, Qt::Horizontal, tr("číslo\nOIS"));
    */


    return model;

}

QSqlQueryModel* SqlDotazyModel::stahniSeznamSpojuBezNacestnychNew()
{
    qDebug() <<  Q_FUNC_INFO;

    pripoj();
    QSqlQueryModel *model = new QSqlQueryModel;

    QString queryString2="";

    queryString2+="SELECT s.s, s.l, s.p, s.c,  vyber.pocet, vyber.nacestne ";
    queryString2+="FROM s ";
    queryString2+="LEFT JOIN ( SELECT xalias.s_id, SUM(xalias.na) AS nacestne, COUNT(*) AS pocet FROM x AS xalias GROUP BY xalias.s_id ) ";
    queryString2+="AS vyber ON s.s=vyber.s_id ";
    queryString2+="WHERE pocet>5 AND nacestne=0 ;";

     qDebug().noquote()<<queryString2;

    model->setQuery(queryString2);
    model->setHeaderData(0, Qt::Horizontal, tr("s"));
    model->setHeaderData(1, Qt::Horizontal, tr("l"));
    model->setHeaderData(2, Qt::Horizontal, tr("p"));
    model->setHeaderData(3, Qt::Horizontal, tr("c"));
    model->setHeaderData(4, Qt::Horizontal, tr("pocet"));
    model->setHeaderData(5, Qt::Horizontal, tr("nacestne"));



    return model;

}

QSqlQueryModel* SqlDotazyModel::stahniSeznamZastavekBezCisCisla()
{
    qDebug() <<  Q_FUNC_INFO;

    pripoj();
    QSqlQueryModel *model = new QSqlQueryModel;

    QString queryString2="";
    queryString2+="SELECT  z.u, z.z, z.n,  z.pop, z.kj ";
    queryString2+="FROM z ";
    queryString2+="WHERE z.cis IS NULL AND tu IS NULL ";


    qDebug().noquote()<<queryString2;

    model->setQuery(queryString2);
    model->setHeaderData(0, Qt::Horizontal, tr("uzel"));
    model->setHeaderData(1, Qt::Horizontal, tr("sloupek"));
    model->setHeaderData(2, Qt::Horizontal, tr("název"));
     model->setHeaderData(3, Qt::Horizontal, tr("popis"));
    model->setHeaderData(4, Qt::Horizontal, tr("kalendář jízd"));


    return model;

}

QSqlQueryModel* SqlDotazyModel::stahniSeznamZastavekPlatnost()
{
    qDebug() <<  Q_FUNC_INFO;

    pripoj();
    QSqlQueryModel *model = new QSqlQueryModel;

    QString queryString2="";
    queryString2+="SELECT  z.u, z.z,z.kj, z.n,  z.cis, z.ois ";
    queryString2+="FROM z ";
    queryString2+="WHERE z.kj LIKE '%0%' ";


    qDebug().noquote()<<queryString2;

    model->setQuery(queryString2);
    model->setHeaderData(0, Qt::Horizontal, tr("uzel"));
    model->setHeaderData(1, Qt::Horizontal, tr("sloupek"));
    model->setHeaderData(2, Qt::Horizontal, tr("kj"));
    model->setHeaderData(3, Qt::Horizontal, tr("název"));
    model->setHeaderData(4, Qt::Horizontal, tr("číslo\nCIS"));
    model->setHeaderData(5, Qt::Horizontal, tr("číslo\nOIS"));


    return model;

}


QSqlQueryModel* SqlDotazyModel::stahniSeznamPoznamky()
{
    qDebug() <<  Q_FUNC_INFO;

    pripoj();
    QSqlQueryModel *model = new QSqlQueryModel;

    QString queryString2="";


    queryString2+="SELECT  d.n, x_po.s,s.l, s.c, x_po.po, COUNT(*) AS pocetPozn, pocetZast , po.t ";
    queryString2+="FROM x_po ";
    queryString2+="LEFT JOIN (SELECT x.s_id, COUNT(*) AS pocetZast FROM x GROUP BY x.s_id) ";
   queryString2+="AS zastpocet ";
   queryString2+="ON x_po.s=zastpocet.s_id ";
   queryString2+="LEFT JOIN s ON x_po.s=s.s ";
   queryString2+="LEFT JOIN po ON x_po.po=po.c ";
   queryString2+="LEFT JOIN d ON s.d=d.c ";
  queryString2+="WHERE neve=0 ";
  queryString2+="AND po.ois=1 ";
  queryString2+="GROUP BY x_po.s, x_po.po ";
  queryString2+="HAVING pocetPozn>1 ";
  queryString2+="ORDER BY pocetPozn DESC ";


    qDebug().noquote()<<queryString2;

    model->setQuery(queryString2);
    model->setHeaderData(0, Qt::Horizontal, tr("dopravce"));
    model->setHeaderData(1, Qt::Horizontal, tr("spoj\nid"));
    model->setHeaderData(2, Qt::Horizontal, tr("linka"));
    model->setHeaderData(3, Qt::Horizontal, tr("spoj\nčíslo"));
    model->setHeaderData(4, Qt::Horizontal, tr("ID\npoznámky"));
    model->setHeaderData(5, Qt::Horizontal, tr("počet\npoznámek"));
    model->setHeaderData(6, Qt::Horizontal, tr("počet\nzastávek"));
    model->setHeaderData(7, Qt::Horizontal, tr("text"));


    return model;
}

QSqlQueryModel* SqlDotazyModel::stahniSeznamVicenasobneSpoje()
{
    qDebug() <<  Q_FUNC_INFO;

    pripoj();
    QSqlQueryModel *model = new QSqlQueryModel;

    QString queryString2="";
    queryString2+="SELECT  COUNT(*),l, c, p, GROUP_CONCAT(s.s) ";
    queryString2+="FROM s ";
    queryString2+="GROUP BY l,c ";
    queryString2+="HAVING COUNT(*)>1 AND man=0 ";
    queryString2+="ORDER BY l";

    qDebug().noquote()<<queryString2;

    model->setQuery(queryString2);
    model->setHeaderData(0, Qt::Horizontal, tr("Počet"));
    model->setHeaderData(1, Qt::Horizontal, tr("l"));
    model->setHeaderData(2, Qt::Horizontal, tr("c"));
    model->setHeaderData(4, Qt::Horizontal, tr("id spojů"));

    return model;

}

QSqlQueryModel* SqlDotazyModel::stahniZastavkyNavaznySpojNew()
{
    qDebug() <<  Q_FUNC_INFO;

    pripoj();
    QSqlQueryModel *model = new QSqlQueryModel;

    QString queryString2="";
    queryString2+="SELECT DISTINCT z.n, z.cis, z.ois, z.u, z.z ";
    queryString2+="FROM sp_po ";
    queryString2+="INNER JOIN (SELECT * FROM (SELECT   s_id,x.u,x.z, z.n, xorder FROM x LEFT JOIN z ON x.u=z.u AND x.z=z.z ORDER BY  s_id ASC, xorder DESC )   GROUP BY s_id ) AS lol ON sp_po.s=lol.s_id ";
    queryString2+="INNER JOIN z ON lol.z = z.z AND lol.u=z.u ";
    queryString2+="WHERE pokrac=1 ORDER BY z.n ASC ";

    qDebug().noquote()<<queryString2;

    model->setQuery(queryString2);
    model->setHeaderData(0, Qt::Horizontal, tr("Název"));
    model->setHeaderData(1, Qt::Horizontal, tr("CIS"));
    model->setHeaderData(2, Qt::Horizontal, tr("OIS"));
    model->setHeaderData(3, Qt::Horizontal, tr("uzel"));
    model->setHeaderData(4, Qt::Horizontal, tr("sloupek"));

    return model;

}


QSqlQueryModel* SqlDotazyModel::stahniSqlDotaz(QString dotaz)
{
    qDebug() <<  Q_FUNC_INFO;

    pripoj();
    QSqlQueryModel *model = new QSqlQueryModel;

    QString queryString2=dotaz;


    qDebug().noquote()<<queryString2;

    model->setQuery(queryString2);



               /*
    model->setHeaderData(0, Qt::Horizontal, tr("uzel"));
    model->setHeaderData(1, Qt::Horizontal, tr("sloupek"));
    model->setHeaderData(2, Qt::Horizontal, tr("název"));
     model->setHeaderData(3, Qt::Horizontal, tr("popis"));
    model->setHeaderData(4, Qt::Horizontal, tr("kalendář jízd"));

*/
    return model;

}
