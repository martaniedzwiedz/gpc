#include "impulsdekorator.h"

ImpulsDekorator::ImpulsDekorator(GeneratorPodstawowy *nKomp, double wartImp):wartoscImp(wartImp),GeneratorDekorator(nKomp)
{

}

double ImpulsDekorator::generuj( int t)
{
    return generator->generuj(t) + ((t==0) ? wartoscImp:0);
}
