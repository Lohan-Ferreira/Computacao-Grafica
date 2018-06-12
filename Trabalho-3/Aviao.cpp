#include "Aviao.h"

Aviao::Aviao()
{
    o = new Object("plane.ply");
    this->x1 = -8;
    this->y1 = 20;

    this->x2 = 8;
    this->y2 = 20;

    this->x3 = 0;
    this->y3 = 40;
}

Aviao::~Aviao()
{
    //dtor
}

void Aviao::desenhar()
{
    glColor3f(1.0, 1.0, 1.0);
        o->desenha(true);

}

int Aviao::getX1()
{
    return this->x1;
}

int Aviao::getX2()
{
    return this->x2;
}

int Aviao::getX3()
{
    return this->x3;
}

int Aviao::getY1()
{
    return this->y1;
}

int Aviao::getY2()
{
    return this->y2;
}

int Aviao::getY3()
{
    return this->y3;
}

void Aviao::moverEsquerda()
{
    this->x1 -= 2;
    this->x2 -= 2;
    this->x3 -= 2;
}

void Aviao::moverDireita()
{
    this->x1 += 2;
    this->x2 += 2;
    this->x3 += 2;
}

void Aviao::setComponente(std::string componente, int valor)
{
    if(componente == "x1") {
        this->x1 = valor;
    }
    else if(componente == "x2") {
        this->x2 = valor;
    }
    else if(componente == "x3") {
        this->x3 = valor;
    }
    else if(componente == "y1") {
        this->y1 = valor;
    }
    else if(componente == "y2") {
        this->y2 = valor;
    }
    else if(componente == "y3") {
        this->y3 = valor;
    }
}

bool Aviao::colideComCombustivel(Combustivel *combustivel)
{
    int metadeTamanho = combustivel->getTamanho()/2;

    if( (this->x1 <= combustivel->getX() + metadeTamanho && this->x1 >= combustivel->getX() - metadeTamanho)
                                             &&
        (this->y1 <= combustivel->getY() + metadeTamanho && this->y1 >= combustivel->getY() - metadeTamanho) ) {
            return true;
        }

    if( (this->x2 <= combustivel->getX() + metadeTamanho && this->x2 >= combustivel->getX() - metadeTamanho)
                                             &&
        (this->y2 <= combustivel->getY() + metadeTamanho && this->y2 >= combustivel->getY() - metadeTamanho) ) {
            return true;
        }

    if( (this->x3 <= combustivel->getX() + metadeTamanho && this->x3 >= combustivel->getX() - metadeTamanho)
                                             &&
        (this->y3 <= combustivel->getY() + metadeTamanho && this->y3 >= combustivel->getY() - metadeTamanho) ) {
            return true;
        }

    return false;
}
