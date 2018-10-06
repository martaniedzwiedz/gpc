#ifndef OBSERWATOR_H
#define OBSERWATOR_H

#include<string>
#include <vector>
///////////////
/// \brief Obserwator.h
/// Klasę Obserwatora w wzorcu projektowym Obserwator.
/// Klasa Obserwator zawiera metody, które swoją funkcję spełniają tylko dla niektórych klas spośród obserwatorów.
/// Jest klasą abstrakcyjną i zawiera same metody wirtualne.
///////////////

class Obserwator
{
    public:
        ///////////////
        /// \brief update()
        /// metoda wirtualna
        /// \param a aktualizowana wartość wyjścia
        ///////////////
        virtual void update(double a) = 0;
        ///////////////
        /// \brief updateParamupdate()
        ///metoda aktualizaująca parametry symulowanego obiektu na GUI
        ///////////////
        virtual void updateParam(std::vector<double>, std::vector<double>, double, double, int, int) = 0;
        virtual ~Obserwator() = 0;
        ///////////////
        /// \brief blad(std::string tekst)
        ///metoda informująca o wystąpieniu wyjątku
        /// \param tekst  rodzaj błędu
        ///////////////
        virtual void blad(std::string tekst);
};


#endif // OBSERWATOR_H
