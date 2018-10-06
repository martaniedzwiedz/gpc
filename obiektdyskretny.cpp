#include "obiektdyskretny.h"

#include "iostream"
#include <vector>

#include <QDebug>

ObiektDyskretny::ObiektDyskretny(std::vector<double> i_wektorA, std::vector<double> i_wektorB, int i_k, double i_wariancja)
{
    ustawParam(i_wektorA, i_wektorB, i_k, i_wariancja);
}

void ObiektDyskretny::ustawParam(std::vector<double> ni_wektorA, std::vector<double> ni_wektorB, int ni_k, double ni_wariancja)
{
    wektorA = ni_wektorA;
    wektorB = ni_wektorB;
    k = ni_k;
    wariancja = ni_wariancja;

    dA = wektorA.size();
    dB = wektorB.size()-1;

    int liczba=dB+ni_k+1;
    u.init(liczba);
    liczba=dA+1;
    y.init(liczba);

    notifyParam();
}

ObiektDyskretny::~ObiektDyskretny()
{
    //dtor
}

void ObiektDyskretny::dodajWektor(std::vector<double> ni_wektorA, std::vector<double> ni_wektorB)
{
    wektorA_2 = ni_wektorA;
    wektorB_2 = ni_wektorB;
}

double ObiektDyskretny::symuluj(double wartosc)
{
    u.dolacz(wartosc);

    double wynik;
    wynik = u.mnozenie(wektorB,k)-y.mnozenie(wektorA,0) + zaklocenie();

    y.dolacz(wynik);
    wyjscie = wynik;

    notify();

    return wynik;
}

double ObiektDyskretny::zaklocenie(){
    std::normal_distribution<double> normalna(0,wariancja);
    auto gen = std::bind(normalna,silnik);
    return gen();
}

void ObiektDyskretny::notify()
{
    std::for_each(observers.begin(), observers.end(),[this](Obserwator *n){n->update(wyjscie);});
}

void ObiektDyskretny::notifyParam()
{
    std::for_each(observers.begin(), observers.end(),[this](Obserwator *n){n->aktualizacjaParametrow(wektorA, wektorB, k, wariancja, dA, dB);});
}


void ObiektDyskretny::zmienObiekt(){
    ustawParam(wektorA_2,wektorB_2,k,wariancja);
}

void ObiektDyskretny::blad(std::string blad)
{
    std::for_each(observers.begin(),observers.end(),[this,&blad](Obserwator *b){ b->blad(blad); });
}
