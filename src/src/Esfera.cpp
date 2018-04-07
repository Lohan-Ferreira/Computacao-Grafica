#include "Esfera.h"

Esfera::Esfera(GLdouble radius, GLdouble slices, GLdouble stacks, int x, int y)
{
    this->radius = radius;
    this->slices = slices;
    this->stacks = stacks;
    this->x = x;
    this->y = y;
    this->movimentando = false;
}

Esfera::~Esfera()
{
    //dtor
}

void Esfera::renderizar()
{
    glPushMatrix();
        this->transladar(this->x, this->y, 0.0);
        this->desenhar();
    glPopMatrix();
}

void Esfera::transladar(GLfloat x, GLfloat y, GLfloat z)
{
    glTranslatef(x, y, z);
}

void Esfera::desenhar()
{
    glutSolidSphere(this->radius, this->slices, this->stacks);
}

bool Esfera::estaDentro(int x, int y)
{
     return ( ( x >= this->x - this->radius ) && ( x <= this->x + this->radius ) )
                                              &&
            ( ( y >= this->y - this->radius ) && ( y <= this->y + this->radius ) );

}

bool Esfera::colideComEsfera(Esfera *esfera)
{
    float distancia = sqrt( pow( (this->x - esfera->getX()), 2) + pow( (this->y - esfera->getY()), 2) );
    if(distancia < this->getRadius() + esfera->getRadius()) {
        return true;
    }
    else {
        return false;
    }
}

bool Esfera::colideComPlano(Plano *plano)
{
   float distancia = (this->y - this->radius) - plano->getAltura();
   if(distancia <= 0.0) {
    return true;
   }
   else {
    return false;
   }
}

bool Esfera::foiColetada()
{
    return this == NULL ? true : false;
}

int Esfera::getX()
{
    return this->x;
}

int Esfera::getY()
{
    return this->y;
}

void Esfera::setX(int x)
{
    this->x = x;
}

void Esfera::setY(int y)
{
    this->y = y;
}

GLdouble Esfera::getRadius()
{
    return this->radius;
}

bool Esfera::emMovimento()
{
    return this->movimentando;
}

void Esfera::movimentar()
{
    this->movimentando = true;
}

void Esfera::coletar()
{
    delete this;
}
