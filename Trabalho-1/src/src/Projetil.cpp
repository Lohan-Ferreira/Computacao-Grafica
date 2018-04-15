#include "Projetil.h"

Projetil::Projetil(double x, double y)
{
    this->x = x;
    this->y = y;
}

Projetil::~Projetil()
{
    //dtor
}

double Projetil::getX()
{
    return this->x;
}

double Projetil::getY()
{
    return this->y;
}

void Projetil::setX(double x)
{
    this->x = x;
}

void Projetil::setY(double y)
{
    this->y = y;
}
