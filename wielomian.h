#ifndef WIELOMIAN_H
#define WIELOMIAN_H

#include <vector>
#include <deque>
#include <numeric>

class Wielomian
{
    public:
        void dolacz(double element); ///metoda dodająca kolejne współczynniki wielomianu
        double mnozenie(std::vector<double> &wek, int k); ///metoda wykonująca równanie wyjścia symulowanego obiektu
        void init(int zero); ///metoda przygotowująca przestrzeń w wektorze, wypełniająca go zerami i nieusuwająca poprzednich elementów
        std::deque<double>* get_queue();
        void zeruj();
private:
        std::deque<double> wektor; ///kolejka przechowywująca kolejne wartości u i y
};
#endif // WIELOMIAN_H
