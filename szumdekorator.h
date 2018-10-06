#ifndef SZUMDEKORATOR_H
#define SZUMDEKORATOR_H

#include <random>
#include "generatordekorator.h"

///////////////
/// \brief SzumDekorator
///klasa generująca szum o zadane wariancji
///////////////

class SzumDekorator : public GeneratorDekorator
{
public:
    /////////////
    /// \brief SzumDekorator konstruktor
    /// \param GeneratorPodstawowy* wskaźnik do obiektu klasy generator podstawowy w celu sumowania
    /// \param wariancja wartość wariancji
    /////////////
    SzumDekorator(double wariancja, GeneratorPodstawowy*);
    /////////////
    /// \brief generuj generuje szum o zadane wariancji
    /// \param t aktualna probka czasu
    /// \return zwraca sumę wartosci szum i zwroconej przez generator
    /////////////
    double generuj(int t) override;
private:
    double wariancja;
    std::default_random_engine gen;
};

#endif // SZUMDEKORATOR_H
