#ifndef OBIEKTDYSKRETNY_H
#define OBIEKTDYSKRETNY_H
#include "obiektSISO.h"
#include "obserwowany.h"
#include "wielomian.h"
#include "komponent.h"
#include <vector>

#include <random>
#include <functional>

class ObiektDyskretny : public Komponent
{
    public:
        ObiektDyskretny(std::vector<double> i_wektorA = {0}, std::vector<double> i_wektorB = {0}, int i_k ={1}, double i_wariancja = 0); ///konstruktor obiektu, wywoływany z parametrami domyślnymi
        ~ObiektDyskretny();
        double symuluj(double wartosc); ///metoda symulująca odpowiedź układu
        void notify(); ///metoda informująca obserwatorów o zmianie wyjścia
        void ustawParam(std::vector<double> ni_wektorA, std::vector<double> ni_wektorB, int ni_k, double ni_wariancja); ///metoda ustawiająca parametry obiektu, wywoływana jest w konstruktorze
        void notifyParam(); ///metoda informująca obserwatorów (GUI) o obecnych parametrach układu
        void dodajWektor(std::vector<double>, std::vector<double>); ///metoda przekazująca parametry drugiego obiektu w przypadku niestacjonarności
        void zmienObiekt(); ///metoda pozwalająca na rezalizację niestacjonarności - wywłuje funkcję ustawParam()
        void blad(std::string blad); ///metoda informująca o wystąpieniu wyjątku
    private:
        Wielomian u, y; ///stworzenie obiektów klasy wielomian
        std::vector<double> wektorA, wektorB, wektorA_2, wektorB_2;
        int dA, dB, k;
        double wariancja, wyjscie;
        std::default_random_engine silnik; ///utworzenie generatora losowego
        double zaklocenie(); ///metoda generująca losowe zakłócenie
};
#endif // OBIEKTDYSKRETNY_H
