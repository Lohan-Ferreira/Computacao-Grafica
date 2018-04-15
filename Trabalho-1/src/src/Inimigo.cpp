#include "Inimigo.h"
#include "math.h"

Inimigo::Inimigo(int x, int y)
{
    this->x = x;
    this->y = y;
    this->direcaoMovimento = 1; // Inimigo começa se movendo para a direita
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

void Inimigo::oscilar(int esquerda, int direita)
{
    if(this->x - 9 < esquerda || this->x + 9 > direita) {
        this->direcaoMovimento *= -1;
    }

    this->x += this->direcaoMovimento;

}

bool Inimigo::colisaoN(Aviao *aviao)
{
    if( (aviao->getX1() <= x + 9 && aviao->getX1() >= x-9) && (aviao->getY1() <= y + 9 && aviao->getY1() >= y - 9) )
        return true;
    if( (aviao->getX2() <= x + 9 && aviao->getX2() >= x-9) && (aviao->getY2() <= y + 9 && aviao->getY2() >= y - 9) )
        return true;
    if( (aviao->getX3() <= x + 9 && aviao->getX3() >= x-9) && (aviao->getY3() <= y + 9 && aviao->getY3() >= y - 9) )
        return true;

    return false;
}

bool Inimigo::colisaoP(double xp, double yp)
{
    if(sqrt((xp-x)*(xp-x)+(yp-y)*(yp-y))<= 12 )
        return true;
    return false;
}


