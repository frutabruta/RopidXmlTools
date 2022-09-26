#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "sqlpraceropid.h"
#include "xmlropidparser.h"

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

private:
    Ui::MainWindow *ui;
    SqlPraceRopid sqlPraceRopid;
    XmlRopidParser xmlRopidParser;

    QVector<Zastavka> seznamZastavek;

    QString otevriSouborXmlDialog();
    void nastavLabelCestyXml();
    void slotVypisChybu(QString vstup);
    void vsechnyConnecty();


    void vypisZastavky(QVector<Zastavka> seznamZastavek);
};
#endif // MAINWINDOW_H
