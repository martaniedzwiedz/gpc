#ifndef OBSERWOWANY_H
#define OBSERWOWANY_H
#include <Obserwator.h>
#include <vector>

class Obserwowany
{
    public:
        void attach(Obserwator *ob); ///metoda dołączająca obiekty do listy obserwatorów
        void detach(Obserwator *ob); ///metoda usuwająca obiekty z listy obserwatorów
        void notify(); ///metoda informująca o zmianie wyjścia
        void notifyParam(); ///metoda informująca o zmianie parametrów
        virtual ~Obserwowany() = 0;
    protected:
        std::vector<Obserwator*>observers; ///utworzenie wektora przechowującego wskaźniki do obiektów obserwatorów
};

#endif // OBSERWOWANY_H
