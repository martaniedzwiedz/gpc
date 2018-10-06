#ifndef KOMPOZYTROWNOLEGLY_H
#define KOMPOZYTROWNOLEGLY_H

#include "Komponent.h"

class KompozytRownolegly : public Komponent
{
    public:
        virtual ~KompozytRownolegly();
        double symuluj(double) override;
        void dolacz(Komponent *);
        void odlacz(Komponent *);
        void ustawParam(std::vector<double>, std::vector<double>, int, double) override;
        void dodajWektor(std::vector<double>, std::vector<double>) override;
        void zmienObiekt() override;

    private:
        std::vector<Komponent *> obiekty;
};

#endif // KOMPOZYTROWNOLEGLY_H
