#include "petlasterowania.h"

PetlaSterowania::PetlaSterowania(ObiektSISO* ob, regulator* reg, Identyfikacja *Id):psOb(ob),psReg(reg),myIdent(Id)
{
    time = 0;
}

void PetlaSterowania::krokPetli()
{

    double zadana = psReg->generuj(time++);
    double U = psReg->symuluj(zadana);
    double Y = psOb->symuluj(U);
}


void PetlaSterowania::ustawObiekt(ObiektSISO* ob)
{
    psOb=ob;
}

void PetlaSterowania::ustawRegulator(regulator *reg)
{
    psReg=reg;
}

double PetlaSterowania::odczytWartZad()
{
    return psReg->odczytWartZad();
}
double PetlaSterowania::odczytSterowania(){
    return psReg->odczytSterowania();
}

void PetlaSterowania::zmienGenerator(GeneratorPodstawowy *gen)
{
    psReg->zmienGenerator(gen);
}
Identyfikacja* PetlaSterowania::getIdenty()
{
    return myIdent;
}
void PetlaSterowania::zmienIdentyfikator(Identyfikacja* id)
{
    myIdent=id;
}


