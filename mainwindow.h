#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "sqlpraceropid.h"
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

private:
    Ui::MainWindow *ui;
    SqlDotazyModel sqlDotazyModel;
    XmlRopidImportStream xmlRopidImportStream;

    QVector<Zastavka> seznamZastavek;

    QString otevriSouborXmlDialog();
    void nastavLabelCestyXml();
    void slotVypisChybu(QString vstup);
    void vsechnyConnecty();


    QString nahradZnacky(QString vstup);

signals:
    void signalNactiSoubor(QString cesta);
};
#endif // MAINWINDOW_H
