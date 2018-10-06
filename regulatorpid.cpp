#include "qDebug"
#include "regulatorpid.h"
#include <regulatorp.h>
#include <regulatorgpc.h>

RegulatorPID::RegulatorPID(double wzm,double nTi,double nTd,double nB,double nN,double nTp):
    k(wzm),Ti(nTi),Td(nTd),N(nN),b(nB),Tp(nTp)
{}

double RegulatorPID::symuluj(double t)
{
    zmianaWartZad(t);
    uchybP=odczytuchybpoprzedni();
    double P=k*(t*b-wyjscie);
    if(Ti==0)
        I=0;
    else
        I=I+k*Tp*uchybP/Ti;

    if(Td==0)
        D=0;
    else
    {
        if(N*Tp+Td==0)
        {
            std::string wyj="dzielenie przez 0, ujemne Td lub N lub Tp";
            throw wyj;
        }
        double czlon=Td/(N*Tp+Td);

        D=D*czlon-k*N*(wyjscie-wyjscieP)*czlon;
    }
    sterowanie = P+I+D;
    return sterowanie;
}

void RegulatorPID::zmianaNastaw(double nk, double nTi, double nTd,double nb,double nN)
{
    k=nk;
    Ti=nTi;
    Td=nTd;
    b=nb;
    N=nN;
}

void RegulatorPID::update(double wy)
{
    wyjscieP=wyjscie;
    wyjscie=wy;
}
double const RegulatorPID::odczytSterowania(){
    return sterowanie;
}

regulator* RegulatorPID::wczytajRegPID()
{
    boost::property_tree::ptree tree1;
    boost::property_tree::read_json("../test1/regulator.json", tree1);
    RegulatorPID *tempR= new RegulatorPID(tree1.get<double>("k"),tree1.get<double>("Ti"), tree1.get<double>("Td"), tree1.get<double>("N"), tree1.get<double>("B"), tree1.get<double>("Tp"));
    return tempR;
}

regulator *regulator::odczyt_ustawien(bool path){
    if(path)
    {
        return RegulatorGPC::wczytajRegGPC();
    }else{
    boost::property_tree::ptree tree1;
    boost::property_tree::read_json("../test1/regulator.json", tree1);
    if(tree1.get<std::string>("regulator")=="P"){
       return RegulatorP::wczytajRegP();
    } else if(tree1.get<std::string>("regulator")=="PID"){
        return RegulatorPID::wczytajRegPID();
    }

    }
}

