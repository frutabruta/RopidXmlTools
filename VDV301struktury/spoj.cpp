#include "spoj.h"

Spoj::Spoj()
{

}

void Spoj::vymaz()
{

    linka.vymaz();
    cislo=0;
    cisloRopid=0;
    globalniSeznamZastavek.clear();
    navazujici=false;
}
