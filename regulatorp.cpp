#include "regulatorp.h"

RegulatorP::RegulatorP(double nP): P(nP)
{}

RegulatorP::~RegulatorP()
{}

void RegulatorP::zmianaNastaw(double nP, double , double, double, double)
{
    P=nP;
}

double RegulatorP::symuluj(double a)
{
    zmianaWartosciZadanej(a);
    sterowanie = P*odczytUchybuReg();
    return sterowanie;
}
double const RegulatorP::odczytSterowania(){
    return sterowanie;
}

regulator* RegulatorP::wczytajRegP()
{
    boost::property_tree::ptree tree1;
    boost::property_tree::read_json("../test1/regulator.json", tree1);
    RegulatorP *tempR= new RegulatorP(tree1.get<double>("k"));
    return tempR;
}

