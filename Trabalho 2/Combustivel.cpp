#include "Combustivel.h"

Combustivel::Combustivel(int x, int y)
{
    this->tamanho = 20;
    this->x = x;
    this->y = y;
    this->z = this->tamanho / 2;
}

Combustivel::~Combustivel()
{
    //dtor
}

void Combustivel::desenhar()
{
    glColor3f(0.8, 0.25, 0.75);
    glPushMatrix();
        glTranslatef(this->x, this->y, this->z);
        glutSolidCube(this->tamanho);
    glPopMatrix();
}

int Combustivel::getX()
{
    return this->x;
}

int Combustivel::getY()
{
    return this->y;
}

int Combustivel::getTamanho()
{
    return this->tamanho;
}