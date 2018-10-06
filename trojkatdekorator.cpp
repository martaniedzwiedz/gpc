#include "trojkatdekorator.h"

TrojkatDekorator::TrojkatDekorator(double nampl, int nokres, GeneratorPodstawowy *nKomp):amplituda(nampl),okres(nokres),GeneratorDekorator(nKomp)
{

}

double TrojkatDekorator::generuj( int t)
{
    unsigned int resztaO = t % okres;
    double wspolczynnikA =(amplituda / (okres / 2.0));
    return  generator->generuj(t) + ((resztaO >= (okres / 2.0)) ? 2*amplituda - (wspolczynnikA * resztaO) : wspolczynnikA * resztaO);
}
