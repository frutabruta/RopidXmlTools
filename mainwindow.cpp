#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    vsechnyConnecty();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::vsechnyConnecty()
{
    connect(&sqlPraceRopid,&SqlPraceRopid::odesliChybovouHlasku,this,&MainWindow::slotVypisChybu);
    connect(&xmlRopidParser,&XmlRopidParser::odesliChybovouHlasku,this,&MainWindow::slotVypisChybu);
}


void MainWindow::on_pushButton_selectFile_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    xmlRopidParser.vstupniXmlSouborCesta=otevriSouborXmlDialog();
    nastavLabelCestyXml();
}

/*!

*/
void MainWindow::nastavLabelCestyXml()
{
    qDebug() <<  Q_FUNC_INFO;
    ui->label_xmlPath->setText(xmlRopidParser.vstupniXmlSouborCesta);

}


QString MainWindow::otevriSouborXmlDialog()
{
    qDebug() <<  Q_FUNC_INFO;
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Otevři soubor"), "",
                                                    tr("XML Ropid JŘ (*.xml);;All Files (*)"));
    return fileName;
}


// SELECT sp_po.l , sp_po.p , sp_po.s, lol.z, lol.u, z.n FROM sp_po  INNER JOIN (SELECT * FROM (SELECT   s_id,x.u,x.z, z.n, xorder FROM x   LEFT JOIN z ON x.u=z.u AND x.z=z.z ORDER BY  s_id ASC, xorder DESC )   GROUP BY s_id ) AS lol ON sp_po.s=lol.s_id INNER JOIN z ON lol.z = z.z AND lol.u=z.u  WHERE pokrac=1
void MainWindow::on_pushButton_start_clicked()
{
     qDebug() <<  Q_FUNC_INFO;
    xmlRopidParser.truncateAll();
    xmlRopidParser.otevriSoubor(xmlRopidParser.vstupniXmlSouborCesta);

}


void MainWindow::vypisZastavky(QVector<Zastavka> seznamZastavek)
{
    ui->tableWidget_zastavkyNavazujici->setRowCount(0);



    qDebug()<<"Seznam zastavek na hranici navazneho spoje:";
    foreach(Zastavka zastavka,seznamZastavek)
    {
        qint32 row;

        row = ui->tableWidget_zastavkyNavazujici->rowCount();
        ui->tableWidget_zastavkyNavazujici->insertRow(row);

         QTableWidgetItem *cell;

        cell = new QTableWidgetItem(zastavka.StopName );
        ui->tableWidget_zastavkyNavazujici->setItem(row, 0, cell);

        cell = new QTableWidgetItem(QString::number(zastavka.cisloCis));
        ui->tableWidget_zastavkyNavazujici->setItem(row, 1, cell);

        cell = new QTableWidgetItem(QString::number(zastavka.cisloOis ));
        ui->tableWidget_zastavkyNavazujici->setItem(row, 2, cell);

        cell = new QTableWidgetItem(QString::number(zastavka.cisloU));
        ui->tableWidget_zastavkyNavazujici->setItem(row, 3, cell);

        cell = new QTableWidgetItem(QString::number(zastavka.cisloZ));
        ui->tableWidget_zastavkyNavazujici->setItem(row, 4, cell);



        slotVypisChybu(zastavka.StopName+" cis:"+QString::number(zastavka.cisloCis)+" ois:"+QString::number(zastavka.cisloOis)+" u:"+QString::number(zastavka.cisloU)+" u:"+ QString::number(zastavka.cisloZ));
    }
        ui->tableWidget_zastavkyNavazujici->resizeColumnsToContents();
}









void MainWindow::slotVypisChybu(QString vstup)
{
     qDebug() <<  Q_FUNC_INFO;
    ui->textEdit_vypisChyb->setText(ui->textEdit_vypisChyb->toPlainText() +vstup+"\n");
}


void MainWindow::on_pushButton_navazZast_clicked()
{
    sqlPraceRopid.pripoj();
    sqlPraceRopid.stahniZastavkyNavaznySpoj(seznamZastavek);
    vypisZastavky(seznamZastavek);
}

