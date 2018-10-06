#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "obserwator.h"
#include "obserwowany.h"
#include "obiektsiso.h"
#include "komponent.h"
#include "obiektdyskretny.h"
#include "regulator.h"
#include <generatorstalej.h>
#include <prostokatdekorator.h>
#include <sinusdekorator.h>
#include <trojkatdekorator.h>
#include <szumdekorator.h>
#include <impulsdekorator.h>
#include <regulatorp.h>
#include <petlasterowania.h>
#include "regulatorpid.h"
#include "identyfikacja.h"
#include "regulatorgpc.h"

#include <QMainWindow>
#include <QTimer>
#include <vector>
#include <QListWidgetItem>
#include <string>


///////////////////////////////////////
/// \brief MainWindow.h - Klasa interfejsu użytkownika.
/// Klasa MainWindow jest obserwatorem.
///  W klasie wykorzystany został QTimer generujący sygnał co określony czas możliwy do regulacji - domyślna wartością jest 100ms, a wartością maksymalną jest jedna sekunda.
///  W prywatnych wektorach przechowywane są wartości wykorzystywane do prezentacji danych na wykresie.
///////////////////////////////////////

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public Obserwator
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    ///////////////////////////////////////
    /// \brief update
    /// metoda obserwatora, za pomocą której uaktualniana jest wartość wyjścia
    /// \param wy- aktualizowane wyjście obiektu
    ///////////////////////////////////////
    void update(double wy) override;
    ///////////////////////////////////////
    /// \brief ustawRegulator
    /// metoda pozwalająca na zmianę typu regulatora
    /// \param regulator* reg wskaźnik do obiektu klasy regulator
    ///////////////////////////////////////
    void ustawRegulator(regulator* reg);

public slots:
    ///////////////////////////////////////
    /// \brief addData();
    ///funkcja prezentująca wektory na wykresie
    ///////////////////////////////////////
    void addData();

private slots:
    ///////////////////////////////////////
    /// \brief makePlot1()
    ///metoda ustawiająca parametry wykresu wyjscia
    ///////////////////////////////////////
    void makePlot1();
    ///////////////////////////////////////
    /// \brief makePlot2()
    ///metoda ustawiająca parametry wykresu sterowania
    ///////////////////////////////////////
    void makePlot2();
    ///////////////////////////////////////
    /// \brief on_horizontalSlider_valueChanged(int)
    ///metoda ustawiająca prędkość symulacji
    /// \param time prędkość symulacji
    ///////////////////////////////////////
    void on_horizontalSlider_valueChanged(int time);
    ///////////////////////////////////////
    /// \brief on_startButton_clicked()
    ///metoda uruchamiająca i zatrymująca symulacje, bez restartuj
    ///////////////////////////////////////
    void on_startButton_clicked();
    ///////////////////////////////////////
    /// \brief on_ZapiszY_clicked()
    ///metoda zapisująca stan układu(tj.y i u) do pliku .json
    ///////////////////////////////////////
    void on_ZapiszY_clicked();
    ///////////////////////////////////////
    /// \brief on_WczytajPlik_clicked()
    ///metoda wywołująca metodę \fn wczytajObiekt() powodującą ponowne wczytanie parametrów z pliku
    ///////////////////////////////////////
    void on_WczytajPlik_clicked();
    ///////////////////////////////////////
    /// \brief blad(std::string tekst)
    /// \param tekst
    /// metoda zgłaszająca nieprawidłowości w działaniu programu
    ///////////////////////////////////////
    void blad(std::string tekst);
    ///////////////////////////////////////
    /// \brief on_pushButton_clicked()
    /// metoda wdrażająca i zapisująca wybraną konfiguracje generatorów
    ///////////////////////////////////////
    void on_pushButton_clicked();
    ///////////////////////////////////////
    /// \brief on_zastosujP_clicked()
    /// metoda zapisująca parametry regulatora P
    ///////////////////////////////////////
    void on_zastosujP_clicked();
    void zapiszRegP();
    void zapiszRegPID();
    void pobierzGenerator();

    void on_odczytajGPC_clicked();

private:
    Ui::MainWindow *ui;
    QTimer timer;
    ///////////////////////////////////////
    /// \brief replot()
    ///metoda uaktualniajaca wykres
    ///////////////////////////////////////
    void replot();
    ///////////////////////////////////////
    /// \brief wczytajObiekt()
    ///metoda wczytująca na nowo parametry obiektu z pliku
    ///////////////////////////////////////
    void wczytajObiekt();
    ///////////////////////////////////////
    /// \brief updateParam(std::vector<double>, std::vector<double>, double, double, int, int)
    ///metoda uaktualniająca parametry obiektu na GUI
    ///////////////////////////////////////
    void updateParam(std::vector<double>, std::vector<double>, double, double, int, int);
    void wczytajGPC();
    int speedValue = 100;
    QVector<double> vec_i={0}, vec_y={0}, vec_w={0}, vec_u={0};

    Komponent *ObiektRegulacji=0;
    int stac;
    bool rodzajReg;
    regulator *Regulator=0;
    PetlaSterowania* petla=0;

    boost::numeric::ublas::vector<double> OmegaIdent;
    Identyfikacja* id=0;
};

#endif // MAINWINDOW_H
