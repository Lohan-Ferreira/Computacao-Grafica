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
        //glScalef(1,1,0.1);
        glTranslatef(this->x, this->y, this->z-18);
        glBegin(GL_QUADS);
                glTexCoord2f(0.0,0.0);
                glVertex3f(-this->tamanho/2, 0, 0);
                glTexCoord2f(1.0,0.0);
                glVertex3f(this->tamanho/2, 0, 0);
                glTexCoord2f(1,1);
                glVertex3f(this->tamanho/2, this->tamanho,0);
                glTexCoord2f(0.0,1);
                glVertex3f(-this->tamanho/2,this->tamanho, 0);
        glEnd();
        //glutSolidCube(this->tamanho);
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


bool Combustivel::colisaoP(double xp, double yp)
{
        if(sqrt((xp-x)*(xp-x)+(yp-y)*(yp-y))<= 20 )
            return true;
    return false;
}
