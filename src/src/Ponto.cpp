#include "Ponto.h"

Ponto::Ponto(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Ponto::~Ponto()
{

}

float Ponto::getX()
{
    return this->x;
}

float Ponto::getY()
{
    return this->y;
}

float Ponto::getZ()
{
    return this->z;
}

