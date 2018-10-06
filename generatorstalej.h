#ifndef GENERATORSTALEJ_H
#define GENERATORSTALEJ_H

#include <generatorpodstawowy.h>

/////////////////////////////////
/// \brief GeneratorStalej
///klasa generująca synganał stały
////////////////////////////////
///
class GeneratorStalej:public GeneratorPodstawowy
{
public:
    ////////////////////
    /// \brief GeneratorStalej konstruktor
    /// \param stala podana generowana stała wartość
    ////////////////////
    GeneratorStalej(double stala);
    ////////////////////
    /// \brief ~GeneratorStalej destruktor
    ////////////////////
    ~GeneratorStalej();
    ////////////////////
    /// \brief generuj
    /// metoda służąca do generowania, zwraca wartość podaną w parametrze
    /// \param t czas
    ////////////////////
    double generuj(int) override;
    ////////////////////
    /// \brief getGenerator();
    /// zwrócenie wskaźnika do obiektu typu GeneratorPodstawowy
    ////////////////////
    GeneratorPodstawowy *getGenerator() override;
protected:
    double wartosc;
};

#endif // GENERATORSTALEJ_H
