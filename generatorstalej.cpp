#include "generatorstalej.h"

GeneratorStalej::~GeneratorStalej()
{}

GeneratorStalej::GeneratorStalej(double stala)
{
    wartosc=stala;
}

double GeneratorStalej::generuj(int)
{
    return wartosc;
}

GeneratorPodstawowy* GeneratorStalej::getGenerator()
{
    return 0;
}

