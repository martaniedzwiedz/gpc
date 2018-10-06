#include "kompozytszeregowy.h"

KompozytSzeregowy::~KompozytSzeregowy()
{}

void KompozytSzeregowy::dolacz(Komponent *o)
{
    obiekty.push_back(o);
}

void KompozytSzeregowy::odlacz(Komponent *o)
 {
     std::remove_if(obiekty.begin(),obiekty.end(),[&o](Komponent* oo){if(oo==o) return true;
                 else return false;});
 }

 double KompozytSzeregowy::symuluj(double wejscie)
 {
     std::for_each(obiekty.begin(),obiekty.end(),[&wejscie](Komponent * ob){wejscie=ob->symuluj(wejscie);});
    return wejscie;
 }

 void KompozytSzeregowy::ustawParam(std::vector<double>, std::vector<double>, int, double){}
 void KompozytSzeregowy::dodajWektor(std::vector<double>, std::vector<double>){}
 void KompozytSzeregowy::zmienObiekt(){}
