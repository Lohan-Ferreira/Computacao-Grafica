#include "Plano.h"

Plano::Plano(int xInicial, int xFinal, int altura)
{
    this->xInicial = xInicial;
    this->xFinal = xFinal;
    this->altura = altura;
}

Plano::~Plano()
{
    //dtor
}

void Plano::desenhar()
{
    for(int i = 0; i < this->xFinal; i += xFinal/50) {
        glBegin(GL_TRIANGLES);
            glVertex3f(i, 0.0, 0.0);
            glVertex3f(i, altura, 0.0);
            glVertex3f(i+40, 0.0, 0.0);
        glEnd();
        glBegin(GL_TRIANGLES);
            glVertex3f(i+40, 0.0, 0.0);
            glVertex3f(i, altura, 0.0);
            glVertex3f(i+40, altura, 0.0);
        glEnd();
    }
}

int Plano::getAltura()
{
    return this->altura;
}
