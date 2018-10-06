#include "generatordekorator.h"

GeneratorDekorator::GeneratorDekorator(GeneratorPodstawowy *ngen):generator(ngen)
{

}

GeneratorDekorator::~GeneratorDekorator()
{
    delete generator;
}

GeneratorPodstawowy* GeneratorDekorator::getGenerator()
{
    return generator;
}
