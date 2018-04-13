#include "Inimigo.h"

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
