#include "szumdekorator.h"

SzumDekorator::SzumDekorator(double nwar, GeneratorPodstawowy *nKomp):wariancja(nwar),GeneratorDekorator(nKomp)
{

}

double SzumDekorator::generuj(int t)
{
    std::normal_distribution<double> e(0,wariancja);
    return generator->generuj(t)+e(gen);
}
