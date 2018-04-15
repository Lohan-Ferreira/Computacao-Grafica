#include "Combustivel.h"

Combustivel::Combustivel(int x, int y)
{
    this->x = x;
    this->y = y;
}

Combustivel::~Combustivel()
{
    //dtor
}

void Combustivel::desenhar()
{
    glColor3f(0.8, 0.25, 0.75);
    glPushMatrix();
        glTranslatef(this->x, this->y, 40);
        glutSolidSphere(40, 100, 100);
    glPopMatrix();
}
