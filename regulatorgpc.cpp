#include "regulatorgpc.h"
#include <algorithm>
#include <iomanip>//setprecision
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <iostream>


RegulatorGPC::RegulatorGPC(unsigned int nH, unsigned int nL, double na, double np,unsigned int nk,unsigned int nA,unsigned int nB,Identyfikacja* Id):
    H(nH), L(nL), a(na), p(np),k(nk), Identyfikator(Id)
{
    if (nL>nH)
        throw "L>H ";
    WielomianU.init(nB+1);
    WielomianH.init(std::max(nH,nA));
    YOstatnieObiektu.init(nA+1);
    URzeczywiste.init(nB+nk+1);
    dURzeczywiste.init(nB+nk+1);
    UPrzejsciowe.init(std::max(nH,nB+nk+1));
    YPrzejsciowe.init(std::max(nH,nA+1));

    //inicjalizacja macierzy i wektorów
    Q=zero_matrix<double>(H,L);
    identity_matrix<double> I(L);
    if(p==0)
        Ixp=zero_matrix<int>(L);
    Ixp = I*p;

    w=vector<double>(H);
    w0=vector<double>(H);
    y0=vector<double>(H);
    P=matrix<double>(L,L);
    Pinv=matrix<double>(L,L);
    ones=zero_vector<int>(L);
    ones(0)=1;
    qtrans=vector<double>(H);

}

RegulatorGPC::~RegulatorGPC()
{
    delete Identyfikator;
}

double RegulatorGPC::symuluj(double val)
{
    zmianaWartosciZadanej(val);

    //krok 0 - identyfikacja
    Identyfikator->getY().dolacz(wyjscie);// dodaje wartość wyjścia obiektu
    Identyfikator->Identyfikuj(); //uruchomienie procesu identyfikacji
    std::vector<double> A = Identyfikator->getA(); //współczynniki wektora A
    std::vector<double> B = Identyfikator->getB(); //współczynniki wektora B

    //wyznaczenie odp skokowej modelu zidentyfikowanego
    WielomianH.zeruj();//co próbkę zerowe warunki początkowe
    for(unsigned int i=0;i<H;i++)
    {
        WielomianU.dolacz(1);
        WielomianH.dolacz(WielomianU.mnozenie(B,0)- WielomianH.mnozenie(A,0));
    }

    //wypełnienie macierzy Q
    for(unsigned int i=0; i<H; ++i)
    {
        for(unsigned int j=0;j<=std::min(i,L-1);j++)
        {
            Q(i,j) = (*WielomianH.get_queue())[H-1-i+j];
        }
    }

    //obliczenie macierzy P
    P=prod(trans(Q),Q)+Ixp;

    //obliczanie macierzy odwrotnej P i qtrans
    InvertMatrix(P,Pinv);
    qtrans=prod(ones,prod(Pinv,trans(Q)));

    //oblicznie trajektorii odniesienia i odpowiedzi swobodnej
    std::for_each(dURzeczywiste.get_queue()->rbegin(),dURzeczywiste.get_queue()->rend(),[this](double val){UPrzejsciowe.dolacz(val);});
    std::for_each(YOstatnieObiektu.get_queue()->rbegin(),YOstatnieObiektu.get_queue()->rend(),[this](double val){YPrzejsciowe.dolacz(val);});
    UPrzejsciowe.dolacz(0);

    double w00=a*wyjscie+(1-a)*val;//w00 wartosc w0 w chwili i-1

    double y00 = UPrzejsciowe.mnozenie(B,k) - YPrzejsciowe.mnozenie(A,0) + YPrzejsciowe.mnozenie(A,1) + YPrzejsciowe.get_queue()->front();
    UPrzejsciowe.dolacz(0);
    YPrzejsciowe.dolacz(y00);

    w0(0) = a*w00+(1-a)*w(0);
    y0(0) = UPrzejsciowe.mnozenie(B,k) - YPrzejsciowe.mnozenie(A,0) + YPrzejsciowe.mnozenie(A,1) + YPrzejsciowe.get_queue()->front();


    for(unsigned int i=1; i<H; ++i)
    {
        YPrzejsciowe.dolacz(y0(i-1));
        w0(i) = a*w0(i-1)+(1-a)*w(i);//trajektoria odniesienia
        y0(i) = UPrzejsciowe.mnozenie(B,k) - YPrzejsciowe.mnozenie(A,0) + YPrzejsciowe.mnozenie(A,1) + YPrzejsciowe.get_queue()->front();//odpowiedź swobodną
    }
    //wyznaczenie nowego sterowania U
    double dU =inner_prod(qtrans,w0-y0);
    double U = URzeczywiste.get_queue()->front()+dU; //nowa wartość sterowania
    dURzeczywiste.dolacz(dU);
    Identyfikator->getU().dolacz(U);// dodaje wartosc sterowania zadaną z generatora
    URzeczywiste.dolacz(U);
    sterowanie=U;
    return U;
}

double RegulatorGPC::generuj(int t)
{
    if(generator==0)
    {
        std::string wyjatek="Brak Generatora";
        throw wyjatek;
    }

    int i=0;
    std::generate(w.begin(),w.end(),[this,&i,&t]{++i;return generator->generuj(t+i);});
    return generator->generuj(t);
}

void RegulatorGPC::update(double wy)
{
    wyjscie=wy;
    YOstatnieObiektu.dolacz(wy);
}

double const RegulatorGPC::odczytSterowania(){
    return sterowanie;
}

template<class T>
bool RegulatorGPC::InvertMatrix (const matrix<T>& input, matrix<T>& inverse) {
    typedef permutation_matrix<std::size_t> pmatrix;
    matrix<T> A(input);
    pmatrix pm(A.size1());
    int res = lu_factorize(A,pm);
    if( res != 0 )
        return false;
    inverse.assign(identity_matrix<T>(A.size1()));
    lu_substitute(A, pm, inverse);
    return true;
}

void RegulatorGPC::zmianaNastaw(double,double, double,double,double)
{

}

void RegulatorGPC::zmienIdentyfikator(Identyfikacja *n)
{
    delete Identyfikator;
    Identyfikator=n;
}

Identyfikacja * RegulatorGPC::getIdentyfikator()
{
    return Identyfikator;
}


regulator* RegulatorGPC::wczytajRegGPC()
{
    boost::property_tree::ptree tree;
    boost::property_tree::read_json("../test1/identyfikacja.json", tree);
    vector<double> v = zero_vector<double>(tree.get<double>("dA")+tree.get<double>("dB")+1);
    std::fill_n(v.begin(),tree.get<double>("dA"),0.5);
    Identyfikacja* id = new Identyfikacja(tree.get<double>("dA"),tree.get<double>("dB"),tree.get<double>("k"),tree.get<double>("alfa"),tree.get<double>("lambda"),tree.get<double>("maxP"),v);

    boost::property_tree::ptree tree1;
    boost::property_tree::read_json("../test1/regulatorGPC.json", tree1);

    RegulatorGPC *tempR= new RegulatorGPC(tree1.get<double>("H"),tree1.get<double>("L"),tree1.get<double>("a"),tree1.get<double>("p"),tree1.get<double>("k"),tree1.get<double>("stA"),tree1.get<double>("stB"),id);
    return tempR;
}




