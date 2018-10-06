#include "kompozytrownolegly.h"

KompozytRownolegly::~KompozytRownolegly()
{
}

void KompozytRownolegly::dolacz(Komponent *o)
{

    obiekty.push_back(o);
}

void KompozytRownolegly::odlacz(Komponent *o)
{

    std::remove_if(obiekty.begin(),obiekty.end(),[&o](Komponent* oo){if(oo==o) return true;
                 else return false;});
}

double KompozytRownolegly::symuluj(double wejscie)
{
    double suma=0;
    std::for_each(obiekty.begin(),obiekty.end(),[&suma,wejscie](Komponent * ob){suma+=ob->symuluj(wejscie);});
    return suma;
}

void KompozytRownolegly::ustawParam(std::vector<double>, std::vector<double>, int, double){}
void KompozytRownolegly::dodajWektor(std::vector<double>, std::vector<double>){}
 void KompozytRownolegly::zmienObiekt(){}
