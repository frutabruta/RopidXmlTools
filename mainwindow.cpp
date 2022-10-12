#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    vsechnyConnecty();
    ui->tabWidget_mainSwitcher->setCurrentWidget(ui->tab_load);

    QString compilationTime = QString("%1T%2").arg(__DATE__,__TIME__);
    ui->label_verze->setText(compilationTime);

    resetujProgressBar();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::vsechnyConnecty()
{
    connect(&sqlDotazyModel,&SqlDotazyModel::odesliChybovouHlasku,this,&MainWindow::slotVypisChybu);




    //QHeaderView::sortIndicatorChanged() signal to the QTableView::sortByColumn()
}


void MainWindow::handleResults(QString vstup)
{
    qDebug()<<"vysledky dorazily z vlakna "<<vstup;
}

/*!

*/
void MainWindow::nastavLabelCestyXml()
{
    qDebug() <<  Q_FUNC_INFO;
    ui->label_xmlPath->setText(cestaSouboru);

}


void MainWindow::on_pushButton_selectFile_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    cestaSouboru=otevriSouborXmlDialog();
    nastavLabelCestyXml();
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

    startWorkInAThread();
}


void MainWindow::slotVypisChybu(QString vstup)
{
    qDebug() <<  Q_FUNC_INFO;
    ui->textEdit_vypisChyb->setText(ui->textEdit_vypisChyb->toPlainText() +vstup+"\n");
}


void MainWindow::on_pushButton_navazZast_clicked()
{
    spustDotazSpolecne(sqlDotazyModel.stahniZastavkyNavaznySpojNew(),ui->tableView_navazne,"Počet zastávek mezi nácestnými spoji: ");
}


void MainWindow::on_pushButton_nacestneStart_clicked()
{
    spustDotazSpolecne(sqlDotazyModel.stahniSeznamSpojuBezNacestnychNew(),ui->tableView_nacestne,"Počet spojů bez nácestných: ");
}


void MainWindow::on_pushButton_nasobneSpoje_clicked()
{
    spustDotazSpolecne(sqlDotazyModel.stahniSeznamVicenasobneSpoje(),ui->tableView_nasobneSpoje,"Počet násobných spojů: ");
}

void MainWindow::on_pushButton_poznamky_clicked()
{
    spustDotazSpolecne(sqlDotazyModel.stahniSeznamPoznamky(),ui->tableView_poznamky,"Počet spojů s poznámkami na celém spoji: ");
}


void MainWindow::on_pushButton_vsechnyTesty_clicked()
{
    on_pushButton_nacestneStart_clicked();
    on_pushButton_nasobneSpoje_clicked();
    on_pushButton_navazZast_clicked();
    on_pushButton_poznamky_clicked();
}


void MainWindow::on_pushButton_clear_clicked()
{
    ui->textEdit_vypisChyb->clear();
}

void MainWindow::resetujProgressBar()
{
    ui->progressBar->setMinimum(0);
    //   ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(0);
}



void MainWindow::slotNastavProgress(int hodnota)
{
    ui->progressBar->setValue(hodnota);
    // qDebug()<<QString::number(hodnota)<<"/"<<QString::number(ui->progressBar->maximum());
}


void MainWindow::slotNastavProgressMax(int hodnota)
{
    //resetujProgressBar();
    qDebug()<<Q_FUNC_INFO<<" "<<QString::number(hodnota);
    ui->progressBar->setMaximum(hodnota);
}

void MainWindow::slotAktivujTlacitka()
{
    ui->pushButton_start->setDisabled(false);
    ui->pushButton_selectFile->setDisabled(false);
    ui->pushButton_vsechnyTesty->setDisabled(false);
}

void MainWindow::slotDeaktivujTlacitka()
{
    ui->pushButton_start->setDisabled(true);
    ui->pushButton_selectFile->setDisabled(true);
    ui->pushButton_vsechnyTesty->setDisabled(true);
}


void MainWindow::spustDotazSpolecne(QSqlQueryModel *model2,QTableView* tableView,QString text)
{
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
  //  QSortFilterProxyModel proxyModel ;

    while ( model2->canFetchMore())
    {
        model2->fetchMore();
    }
    proxyModel->setSourceModel(model2);
    tableView->setModel(proxyModel);
    tableView->show();
    tableView->resizeColumnsToContents();
 //   tableView->setSortingEnabled(true);
    connect(tableView->horizontalHeader(),SIGNAL(sortIndicatorChanged(int, Qt::SortOrder )),tableView,SLOT(sortByColumn(int, Qt::SortOrder )));
    int pocet= proxyModel->rowCount();
    qDebug()<<"pocet vysledku: "<<QString::number(pocet);
    slotVypisChybu(text+QString::number(pocet));
}



void MainWindow::startWorkInAThread()
{
    //XmlRopidImportStream *workerThread = &xmlRopidImportStream;
    slotDeaktivujTlacitka();

    XmlRopidImportStream *xmlRopidImportStream =  new XmlRopidImportStream();

    xmlRopidImportStream->truncateAll();

    xmlRopidImportStream->vstupniXmlSouborCesta=cestaSouboru;

    connect(xmlRopidImportStream,&XmlRopidImportStream::resultReady, this, &MainWindow::handleResults);
    connect(xmlRopidImportStream,&XmlRopidImportStream::finished, xmlRopidImportStream, &QObject::deleteLater);
    connect(xmlRopidImportStream,&XmlRopidImportStream::finished, this, &MainWindow::slotAktivujTlacitka);

    connect(xmlRopidImportStream,&XmlRopidImportStream::odesliChybovouHlasku,this,&MainWindow::slotVypisChybu);
    connect(xmlRopidImportStream,&XmlRopidImportStream::signalNastavProgress,this,&MainWindow::slotNastavProgress);
    connect(xmlRopidImportStream,&XmlRopidImportStream::signalNastavProgressMax,this,&MainWindow::slotNastavProgressMax);

    xmlRopidImportStream->start();
}


