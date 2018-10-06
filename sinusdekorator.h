#ifndef SINUSDEKORATOR_H
#define SINUSDEKORATOR_H

#include <generatordekorator.h>

///////////////////////////////////////
/// \brief SinusDekorator
///klasa generująca sygnał sinusoidalny o zadanej amplitudzie okresie
//////////////////////////////////
///
class SinusDekorator : public GeneratorDekorator
{
public:
    /////////////
    /// \brief SinusDekorator konstruktor
    /// \param GeneratorPodstawowy* wskaźnik do obiektu klasy generator podstawowy w celu sumowania
    /// \param nampl wartość amplitudy
    /// \param nokres wartość okresu
    /////////////
    SinusDekorator(double nampl, int nokres, GeneratorPodstawowy*);
    /////////////
    /// \brief generuj generuje sygnał sinusoidalny
    /// \param t aktualna probka czasu
    /// \return zwraca sumę wartosci sygnalu sinusoidalnego i zwroconej przez generator
    /////////////
    double generuj(int t) override;
private:
    double amplituda;
    int okres;
};

#endif // SINUSDEKORATOR_H
