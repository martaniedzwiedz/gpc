#ifndef KOMPONENT_H
#define KOMPONENT_H
#include <algorithm>
#include "obiektsiso.h"
#include "wielomian.h"
#include "obserwowany.h"

class Komponent : public ObiektSISO, public Obserwowany
{
    public:
        double symuluj(double)=0;
        virtual ~Komponent();
        virtual void ustawParam(std::vector<double>, std::vector<double>, int, double) = 0;
        virtual void dodajWektor(std::vector<double>, std::vector<double>) = 0;
        virtual void zmienObiekt() = 0;
};

#endif // KOMPONENT_H
