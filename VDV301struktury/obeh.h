#ifndef OBEH_H
#define OBEH_H
#include "linka.h"
#include "spoj.h"

class Obeh
{
public:
    Obeh();
    Linka kmenovaLinka;
    int p=0;
    QVector<Spoj> seznamSpoju;

    void vymaz();
};







#endif // OBEH_H
