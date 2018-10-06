#ifndef PROSTOKATDEKORATOR_H
#define PROSTOKATDEKORATOR_H

#include <generatordekorator.h>

///////////////////////////////////////
/// \brief ProstokatDekorator
///klasa generująca sygnał prostokątny o zadanej amplitudzie okresie i wypełnieniu
//////////////////////////////////

class ProstokatDekorator:public GeneratorDekorator
{
public:    
    /////////////
    /// \brief ProstokatDekorator konstruktor
    /// \param GeneratorPodstawowy* wskaźnik do obiektu klasy generator podstawowy w celu sumowania
    /// \param nampl wartość amplitudy
    /// \param nokres wartość okresu
    /// \param nwyp wypełnienie
    /////////////
    ProstokatDekorator(double nampl, int nokres, double nwyp, GeneratorPodstawowy*);
    /////////////
    /// \brief generuj generuje sygnał prostokątny
    /// \param t aktualna probka czasu
    /// \return zwraca sumę wartosci sygnalu prostokątnego i zwroconej przez generator
    /////////////
    double generuj(int t) override;
private:
    double amplituda, wypelnienie;
    int okres;
};

#endif // PROSTOKATDEKORATOR_H
