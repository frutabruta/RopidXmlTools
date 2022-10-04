#include "sqldotazymodel.h"

SqlDotazyModel::SqlDotazyModel()
{

}




int SqlDotazyModel::stahniZastavkyNavaznySpoj(QVector<Zastavka> &docasnySeznamZastavek)
{
    qDebug() <<  Q_FUNC_INFO;

    docasnySeznamZastavek.clear();

    this->otevriDB();

    QString queryString2="";
    queryString2+="SELECT DISTINCT z.n, z.cis, z.ois, z.u, z.z ";
    queryString2+="FROM sp_po ";
    queryString2+="INNER JOIN (SELECT * FROM (SELECT   s_id,x.u,x.z, z.n, xorder FROM x LEFT JOIN z ON x.u=z.u AND x.z=z.z ORDER BY  s_id ASC, xorder DESC )   GROUP BY s_id ) AS lol ON sp_po.s=lol.s_id ";
    queryString2+="INNER JOIN z ON lol.z = z.z AND lol.u=z.u ";
    queryString2+="WHERE pokrac=1 ORDER BY z.n ASC ";


    //QSqlQuery query(queryString2,this->mojeDatabaze);
    QSqlQuery query;
    query.exec(queryString2);

    int pocetZastavek=0;
    qDebug().noquote()<<queryString2;

    int citacD=0;

    while (query.next())
    {
        citacD++;

        if (query.value(0).toString()!="")
        {

            Zastavka aktZast;

            qDebug()<<"poradi Vysledku SQL dotazu "<<QString::number(pocetZastavek);

            // z.n, z.cis, z.ois, z.u, z.z

            aktZast.StopName=query.value( query.record().indexOf("z.n")).toString();

            aktZast.cisloCis=query.value( query.record().indexOf("z.cis")).toInt();
            aktZast.cisloOis=query.value(query.record().indexOf("z.ois")).toUInt();

            aktZast.cisloU=query.value(query.record().indexOf("z.u")).toUInt();
            aktZast.cisloZ=query.value(query.record().indexOf("z.z")).toUInt();


            docasnySeznamZastavek.push_back(aktZast);

            qDebug()<<"nactena zastavka:"<<aktZast.StopName<<" "<<aktZast.cisloCis;
        }
    }

    pocetZastavek=docasnySeznamZastavek.length();
    this->zavriDB();
    if (pocetZastavek ==0)
    {
        return 0;
    }


    return 1;
}



int SqlDotazyModel::stahniSeznamSpojuBezNacestnych(QVector<QMap<QString,QString>> &spoje)
{
    qDebug() <<  Q_FUNC_INFO;

    spoje.clear();

    this->otevriDB();

    QString queryString2="";

    queryString2+="SELECT s.s, s.l, s.p, s.c,  vyber.pocet, vyber.nacestne ";
    queryString2+="FROM s ";
    queryString2+="LEFT JOIN ( SELECT xalias.s_id, SUM(xalias.na) AS nacestne, COUNT(*) AS pocet FROM x AS xalias GROUP BY xalias.s_id ) ";
    queryString2+="AS vyber ON s.s=vyber.s_id ";
    queryString2+="WHERE pocet>5 AND nacestne=0 ;";
    QSqlQuery query;
    query.exec(queryString2);

    qDebug()<<"lasterror"<<  query.lastError();

    int pocetZastavek=0;
    qDebug().noquote()<<queryString2;

    int citacD=0;

    while (query.next())
    {
        citacD++;

        if (1)//(query.value(0).toString()!="")
        {

              QMap<QString,QString> aktSpoj;

            qDebug()<<"poradi Vysledku SQL dotazu "<<QString::number(citacD);
            aktSpoj["s"]=query.value( query.record().indexOf("s.s")).toString();
            aktSpoj["l"]=query.value( query.record().indexOf("s.l")).toString();
            aktSpoj["p"]=query.value( query.record().indexOf("s.p")).toString();
            aktSpoj["c"]=query.value( query.record().indexOf("s.c")).toString();
           aktSpoj["pocet"] =QString::number(query.value(query.record().indexOf("pocet")).toInt() );
           aktSpoj["nacestne"]=QString::number(query.value( query.record().indexOf("nacestne")).toInt());
            spoje.push_back(aktSpoj);

         qDebug()<<" "<<aktSpoj["s"]<<" "<<aktSpoj["l"]<<" "<<aktSpoj["pocet"]<<" "<<aktSpoj["nacestne"];
        }

    }

    pocetZastavek=spoje.length();
    this->zavriDB();
    if (pocetZastavek ==0)
    {
        return 0;
    }
    return 1;
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

    model->setQuery(queryString2);
    model->setHeaderData(0, Qt::Horizontal, tr("s"));
    model->setHeaderData(1, Qt::Horizontal, tr("l"));
    model->setHeaderData(2, Qt::Horizontal, tr("p"));
    model->setHeaderData(3, Qt::Horizontal, tr("c"));
    model->setHeaderData(4, Qt::Horizontal, tr("pocet"));
    model->setHeaderData(5, Qt::Horizontal, tr("nacestne"));
   // QTableView *view = new QTableView;

    return model;

}

QSqlQueryModel* SqlDotazyModel::stahniSeznamVicenasobneSpoje()
{
    qDebug() <<  Q_FUNC_INFO;

    pripoj();
    QSqlQueryModel *model = new QSqlQueryModel;


    QString queryString2="";
    queryString2+="SELECT  COUNT(*),l, c ";
    queryString2+="FROM s ";
    queryString2+="GROUP BY l,c ";
    queryString2+="HAVING COUNT(*)>1 AND man=0 ";
    queryString2+="ORDER BY l";



    model->setQuery(queryString2);
    model->setHeaderData(0, Qt::Horizontal, tr("Počet"));
    model->setHeaderData(1, Qt::Horizontal, tr("l"));
    model->setHeaderData(2, Qt::Horizontal, tr("c"));


   // QTableView *view = new QTableView;

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

    model->setQuery(queryString2);
    model->setHeaderData(0, Qt::Horizontal, tr("Název"));
    model->setHeaderData(1, Qt::Horizontal, tr("CIS"));
    model->setHeaderData(2, Qt::Horizontal, tr("OIS"));
    model->setHeaderData(3, Qt::Horizontal, tr("uzel"));
    model->setHeaderData(4, Qt::Horizontal, tr("sloupek"));

   // QTableView *view = new QTableView;

    return model;

}












