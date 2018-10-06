#include "obserwowany.h"

Obserwowany::~Obserwowany()
{
    //dtor
}

void Obserwowany::attach(Obserwator *ob){
    observers.push_back(ob);
}

void Obserwowany::detach(Obserwator *ob){
    observers.pop_back();
}

void Obserwowany::notify()
{

}

void Obserwowany::notifyParam()
{

}


