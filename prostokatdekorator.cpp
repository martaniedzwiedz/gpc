#include "prostokatdekorator.h"
#include "QDebug"

ProstokatDekorator::ProstokatDekorator(double nampl, int nokres, double nwyp, GeneratorPodstawowy *nKomp):amplituda(nampl),okres(nokres),wypelnienie(nwyp),GeneratorDekorator(nKomp)
{
}

double ProstokatDekorator::generuj(int t)
{
    //qDebug() << t % okres;
    //qDebug() << wypelnienie * okres;
    //qDebug() << ((t % okres) < (wypelnienie * okres)) ? amplituda : 0;
    return generator->generuj(t)+((t % okres) < (wypelnienie * okres)) ? amplituda : 0;
}
