#ifndef GENERATORDEKORATOR_H
#define GENERATORDEKORATOR_H

#include <generatorpodstawowy.h>

///////////////////////////////////////
/// \brief GeneratorDekorator
/// abstrakcyjna klasa dekorujaca GeneratorPodstawowy
//////////////////////////////////

class GeneratorDekorator : public GeneratorPodstawowy
{
public:
    ////////////////////
    /// \brief GeneratorDekorator konstruktor
    /// konieczne jest na końcu ciągu wskaźników wstawić sygnał stały
    /// \param GeneratorPodstawowy* wskaźnik na obiekt typu GeneratorPodstawowy służący do składania sygnałów
    ////////////////////
    GeneratorDekorator(GeneratorPodstawowy*);
    ////////////////////
    /// \brief ~GeneratorDekorator
    /// wirtualny destruktor zwalnia pamięć generetora
    ////////////////////
    virtual ~GeneratorDekorator();
    ////////////////////
    /// \brief generuj
    /// metoda służąca do generowania, zaimplementowana w metodach pochodnych
    /// \param t czas
    ////////////////////
    double generuj(int t) = 0;
    ////////////////////
    /// \brief getGenerator();
    /// zwrócenie wskaźnika do obiektu typu GeneratorPodstawowy
    ////////////////////
    GeneratorPodstawowy* getGenerator();
protected:
    GeneratorPodstawowy *generator;
};

#endif // GENERATORDEKORATOR_H
