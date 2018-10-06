#include "regulator.h"
#include "QDebug"
#include <string>
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/lu.hpp>

regulator::~regulator()
{
    delete generator;
}

void regulator::stworzGenerator(GeneratorPodstawowy *gen)
{
    generator=gen;
}

void regulator::update(double wy){
    wyjscie = wy;
}

double const regulator::odczytUchybu(){
    return uchyb;
}

double const regulator::odczytWartosciZadanej(){
    return zad;
}

double const regulator::odczytWyjscia(){
    return wyjscie;
}

void regulator::zmianaWartosciZadanej(double nzad)
{
    zad=nzad;
    uchybpoprzedni();
    uchyb=zad-wyjscie;
}
void regulator::uchybpoprzedni()
{
    uchybP=uchyb;
}
double regulator::odczytuchybpoprzedni()
{
    return uchybP;
}

double regulator::generuj(int t)
{
    if(generator==0)
    {
        std::string wyjatek="Brak Generatora";
        throw wyjatek;
    }
    return generator->generuj(t);
}

void regulator::zmienGenerator(GeneratorPodstawowy *ngenerator)
{
    delete generator;
    generator = ngenerator;
}

void regulator::aktualizacjaParametrow(std::vector<double>, std::vector<double>, double, double, int, int){

}

