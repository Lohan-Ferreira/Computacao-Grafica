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

bool Inimigo::colisaoN(double x1,double y1, double x2, double y2, double x3, double y3)
{
    if( (x1 <= x + 9 && x1 >= x-9) && (y1 <= y + 9 && y1 >= y - 9) )
        return true;
    if( (x2 <= x + 9 && x2 >= x-9) && (y2 <= y + 9 && y2 >= y - 9) )
        return true;
    if( (x3 <= x + 9 && x3 >= x-9) && (y3 <= y + 9 && y3 >= y - 9) )
        return true;

        return false;

}

bool Inimigo::colisaoP(double xp, double yp)
{
    if(sqrt((xp-x)*(xp-x)+(yp-y)*(yp-y))<= 12 )
        return true;
    return false;
}


