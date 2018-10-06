#include "sinusdekorator.h"
#include <cmath>

SinusDekorator::SinusDekorator(double nampl, int nokres, GeneratorPodstawowy *nKomp):amplituda(nampl),okres(nokres),GeneratorDekorator(nKomp)
{

}

double SinusDekorator::generuj( int t)
{
    return  generator->generuj(t)+(amplituda*std::sin((static_cast<double>(t % okres) / okres) *6.28 ));
}
