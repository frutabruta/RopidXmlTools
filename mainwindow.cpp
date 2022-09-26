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
    sqlPraceRopid.pripoj();
    sqlPraceRopid.stahniZastavkyNavaznySpoj(seznamZastavek);
    vypisZastavky(seznamZastavek);
}


void MainWindow::vypisZastavky(QVector<Zastavka> seznamZastavek)
{
    qDebug()<<"Seznam zastavek na hranici navazneho spoje:";
    foreach(Zastavka zastavka,seznamZastavek)
    {
        slotVypisChybu(zastavka.StopName+" cis:"+QString::number(zastavka.cisloCis)+" ois:"+QString::number(zastavka.cisloOis)+" u:"+QString::number(zastavka.cisloU)+" u:"+ QString::number(zastavka.cisloZ));
    }
}


void MainWindow::slotVypisChybu(QString vstup)
{
     qDebug() <<  Q_FUNC_INFO;
    ui->textEdit_vypisChyb->setText(ui->textEdit_vypisChyb->toPlainText() +vstup+"\n");
}

