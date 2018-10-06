#include "identyfikacja.h"
#include"QDebug"
#include <math.h>
#include <iomanip>
Identyfikacja::Identyfikacja(int stA, int stB,  int nK, double nA, double nl, double nmaxP, vector<double> startowe)
{
    K=nK;
    dA=sA;
    dB=stB;
    L=nl;
    A=nA;
    maxP=nmaxP;
    Omega= zero_vector<double>(dA + dB + 1);

    u.init(dB+1+K);
    y.init(dA+1);

    identity_matrix<int> I(dA+dB+1);
    P = I * L; //(32.9) Warunek początkowy dla macierzy kowariancji

    vec = new vector<double>(dA+dB+1);

    if(startowe.size()==dA+dB+1)
        Omega = startowe;
    else
        std::fill_n(Omega.begin(),dB+1, 0.5);
}

Identyfikacja::~Identyfikacja()
{
    delete vec;
}

void Identyfikacja::toVector( Wielomian const &A, Wielomian const &B)
{

    unsigned int i=0;
    std::for_each( const_cast<Wielomian&>(A).get_queue()->begin()+K, const_cast<Wielomian&>(A).get_queue()->end(),
                  [this, &i](double t)
                    {(*vec)(i)=t;++i;});

    std::for_each( const_cast<Wielomian&>(B).get_queue()->begin()+1, const_cast<Wielomian&>(B).get_queue()->end(),
                  [this,&i](double t)
                    {(*vec)(i)=-t;++i;});

}


void Identyfikacja::Identyfikuj()
{
    toVector(u,y);//Identyfikator.getU(),Identyfikator.getY()
    double y=getY().get_queue()->front();
    Eps=y-inner_prod(Omega,*vec); //wyznaczenie błędu predykcji jednokrokowej

    if(A==0)
        throw "Alfa=0";    //dzielenie przez 0
    else if(A>1)
        throw "Alfa>1";

    vector<double>temp = prod(*vec,P);
    vector<double>temp1 = prod(P,*vec);
    matrix<double>temp2 = outer_prod(temp1,temp);
    double temp3 = A+inner_prod(temp,*vec);

    P=(1/A)*(P - temp2/temp3); //aktualizacja macierzy kowariancji

    zabezpieczPrzedwybuchem(P);
    ki=prod(P,*vec); //nowy wektor wzmocnień (32.6)
    Omega=Omega+Eps*ki; //aktualizacja wektora estymowanych parametrów
    VecBA.push_back(Omega);
    std::cout<<Omega<< std::endl;
}

boost::numeric::ublas::vector<double> Identyfikacja::getOmega(){
    OmegaOdczyt = Omega;
    return OmegaOdczyt;
}

void Identyfikacja::zabezpieczPrzedwybuchem(symmetric_matrix< double> &m)
{
    double maxM=0;
    do{
        maxM=0;
        for(unsigned i = 0; i < m.size1(); ++ i)
        {
            if(fabs(m(i,i))>maxM)
                maxM=fabs(m(i,i));
        }

        if (maxM>maxP)
            m/=sqrt(maxM);
    }while(maxM>maxP);
}
void Identyfikacja::zmienParametry(int stA, int stB, int nK,double nAlfa, double nlambd, double nmaxP)
{
 dA=stA;
 dB=stB;
 K=nK;
 L=nl;
 A=nA;
 maxP=nmaxP;

}
Wielomian& Identyfikacja::getU()
{
    return u;
}

Wielomian& Identyfikacja::getY()
{
    return y;
}

std::vector<double> Identyfikacja::getB()
{
    std::vector<double> B;
    std::for_each(VecBA.back().begin(),VecBA.back().begin()+dB+1,[&B](double val){B.push_back(val);});
    return B;
}

std::vector<double> Identyfikacja::getA()
{
    std::vector<double> A;
    std::for_each(VecBA.back().begin()+dB+1,VecBA.back().end(),[&A](double val){A.push_back(val);});
    return A;
}
