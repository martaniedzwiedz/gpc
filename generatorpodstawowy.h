#ifndef GENERATORPODSTAWOWY_H
#define GENERATORPODSTAWOWY_H

#include<vector>
#include <string>

/////////////////////////////////
/// \brief GeneratorPodstawowy
///abstrakcyjna klasa generatorow, z ktorej dziedziczą wszystkie generatory
////////////////////////////////
///
class GeneratorPodstawowy
{
public:
    ////////////////////
    /// \brief getGenerator();
    /// zwrócenie wskaźnika do obiektu typu GeneratorPodstawowy - metoda wirtualna, będzie nadpisywana w
    /// kolejnych metodach dekorujących
    ////////////////////
    virtual GeneratorPodstawowy *getGenerator()=0;
    ////////////////////
    /// \brief ~GeneratorPodstawowy();
    /// wirtualny destruktor
    ////////////////////
    virtual ~GeneratorPodstawowy();
    ////////////////////
    /// \brief generuj
    /// metoda służąca do generowania, zaimplementowana w metodach pochodnych - metoda wirtualna
    /// \param t czas
    ////////////////////
    virtual double generuj(int t) = 0;
};

#endif // GENERATORPODSTAWOWY_H
