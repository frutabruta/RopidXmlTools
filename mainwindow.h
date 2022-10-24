#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTableView>
#include "XmlRopidImportStream/xmlropidimportstream.h"
#include "sqldotazymodel.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pushButton_selectFile_clicked();

    void on_pushButton_start_clicked();

    void on_pushButton_navazZast_clicked();

    void on_pushButton_nacestneStart_clicked();

    void on_pushButton_nasobneSpoje_clicked();

    void on_pushButton_vsechnyTesty_clicked();

    void on_pushButton_clear_clicked();

    void slotNastavProgress(int hodnota);
    void slotNastavProgressMax(int hodnota);
    void slotVypisSqlSelectChybu(QString vstup);
    void handleResults(QString vstup);


    void slotAktivujTlacitka();
     void slotDeaktivujTlacitka();
     void on_pushButton_poznamky_clicked();


     void on_pushButton_bezCis_clicked();

     void on_pushButton_sql_clicked();


     void on_pushButton_zastPlatnost_clicked();

     void on_pushButton_vymazDB_clicked();

private:
    Ui::MainWindow *ui;
    SqlDotazyModel sqlDotazyModel;
  //  XmlRopidImportStream xmlRopidImportStream;



    QString otevriSouborXmlDialog();
    void nastavLabelCestyXml();
    void slotVypisChybu(QString vstup);
    void vsechnyConnecty();

    QString cestaSouboru="";


    QString nahradZnacky(QString vstup);

    void resetujProgressBar();
    void startWorkInAThread();

    void spustDotazSpolecne(QSqlQueryModel *model2, QTableView *tableView, QString text);
    bool existujeLastError(QSqlQueryModel *model);
signals:
    void signalNactiSoubor(QString cesta);
    void signalSqlChyba(QString vstup);
};
#endif // MAINWINDOW_H
