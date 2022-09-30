#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "sqlpraceropid.h"
#include "xmlropidparser.h"
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


private:
    Ui::MainWindow *ui;
    SqlDotazyModel sqlDotazyModel;
    XmlRopidParser xmlRopidParser;

    QVector<Zastavka> seznamZastavek;

    QString otevriSouborXmlDialog();
    void nastavLabelCestyXml();
    void slotVypisChybu(QString vstup);
    void vsechnyConnecty();


};
#endif // MAINWINDOW_H
