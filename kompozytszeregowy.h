#ifndef KOMPOZYTSZEREGOWY_H
#define KOMPOZYTSZEREGOWY_H


#include "Komponent.h"


class KompozytSzeregowy : public Komponent
{
    public:
        virtual ~KompozytSzeregowy();
        double symuluj(double) override;
        void dolacz(Komponent *);
        void odlacz(Komponent *);
        void ustawParam(std::vector<double>, std::vector<double>, int, double) override;
        void dodajWektor(std::vector<double>, std::vector<double>) override;
        void zmienObiekt() override;
    private:
        std::vector<Komponent *> obiekty;
};

#endif // KOMPOZYTSZEREGOWY_H
