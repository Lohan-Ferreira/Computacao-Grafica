#include "Inimigo.h"

Inimigo::Inimigo(int x, int y)
{
    this->x = x;
    this->y = y;
}

Inimigo::~Inimigo()
{
    //dtor
}

void Inimigo::desenhar()
{
    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
        glTranslatef(this->x, this->y, 9);
        glutSolidCube(18);
    glPopMatrix();
}
