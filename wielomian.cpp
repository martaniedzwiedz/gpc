#include "wielomian.h"
#include<iostream>

#include <numeric> //inner_product
#include <algorithm>

void Wielomian::dolacz(double element)
{
    wektor.push_front(element);
    wektor.pop_back();
}

double Wielomian::mnozenie(std::vector<double> &wek, int k)
{
    if(k<0)
        throw("k<0!");
    return std::inner_product(wek.begin(),wek.end(),wektor.begin()+k,0.0);
}

void Wielomian::init(int zero)
{
    int x=zero-this->wektor.size();
    for(int i=0;i<x;i++)
    {
        this->wektor.push_back(0);
    }
}
std::deque<double> *Wielomian::get_queue()
{
    return &wektor;
}
void Wielomian::zeruj()
{
    std::fill(wektor.begin(),wektor.end(),0);
}
