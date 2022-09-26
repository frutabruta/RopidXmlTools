#ifndef LINKA_H
#define LINKA_H

#include <QObject>
#include <QWidget>

class Linka
{
public:
    Linka();
    int c=0;
    int lc=0;
    QString n="";
    QString LineNumber="";
    QString LineName="";
    int kli=0;
    QString typLinky="";
    bool isDiversion=false;
    bool isNight=false;
    bool isReplacement=false;
    bool isSpecial=false;
    bool isWheelchair=false;
    bool isSchool=false; //ignorování zastávek na znamení
    void vymaz();
};

#endif // LINKA_H
