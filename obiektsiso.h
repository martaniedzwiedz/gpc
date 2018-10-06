#ifndef OBIEKTSISO_H
#define OBIEKTSISO_H
/*!
 * \brief ObiektSISO.h - Abstrakcyjna klasa
 *
 * Jest klasą bazową dla każdej klasy reprezentującej obiekt o jednym wejściu i jednym wyjściu.
 * Posiada wyłacznie metody wirtualne oraz wirtualny destruktor
 *
 */
class ObiektSISO
{
    public:

    virtual double symuluj(double) = 0; ///wirtualna metoda nie posiadająca implementacji, stanowiąca podstawę do rozwoju w klasach dziedziczących
    virtual ~ObiektSISO();///wirtualny destruktor
};


#endif // OBIEKTSISO_H
