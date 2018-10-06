#ifndef TROJKATDEKORATOR_H
#define TROJKATDEKORATOR_H

#include "generatordekorator.h"

///////////////////////////////////////
/// \brief TrojkatDekorator
///klasa generująca sygnał trojkatny o zadanej amplitudzie okresie
//////////////////////////////////

class TrojkatDekorator : public GeneratorDekorator
{
public:
    /////////////
    /// \brief TrojkatDekorator konstruktor
    /// \param GeneratorPodstawowy* wskaźnik do obiektu klasy generator podstawowy w celu sumowania
    /// \param nampl wartość amplitudy
    /// \param nokres wartość okresu
    /////////////
    TrojkatDekorator(double nampl, int nokres, GeneratorPodstawowy*);
    /////////////
    /// \brief generuj generuje sygnał trojkątny
    /// \param t aktualna probka czasu
    /// \return zwraca sumę wartosci sygnalu trójkątnego i zwroconej przez generator
    /////////////
    double generuj(int t) override;
private:
    double amplituda;
    int okres;
};

#endif // TROJKATDEKORATOR_H
