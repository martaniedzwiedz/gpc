#ifndef IMPULSDEKORATOR_H
#define IMPULSDEKORATOR_H

#include "generatordekorator.h"

///////////////
/// \brief ImpulsDekorator
///klasa generująca impuls
///////////////

class ImpulsDekorator : public GeneratorDekorator
{
public:
    /////////////
    /// \brief ImpulsDekorator konstruktor
    /// \param GeneratorPodstawowy* wskaźnik do obiektu klasy generator podstawowy w celu sumowania
    /// \param wartImp wartość impulsu
    /////////////
    ImpulsDekorator(GeneratorPodstawowy*, double wartImp=10000);
    /////////////
    /// \brief generuj generuje impuls
    /// \param t aktualna probka czasu
    /// \return zwraca sumę wartosci szumu i zwroconej przez generator
    /////////////
    double generuj(int t) override;
private:
    double wartoscImp;
};

#endif // IMPULSDEKORATOR_H
