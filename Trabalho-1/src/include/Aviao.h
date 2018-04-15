#ifndef AVIAO_H
#define AVIAO_H

#include <GL/glut.h>
#include <string>

class Aviao
{
    private:
        int x1, x2, x3;
        int y1, y2, y3;
    public:
        Aviao();
        ~Aviao();
        void desenhar();
        int getX1();
        int getX2();
        int getX3();
        int getY1();
        int getY2();
        int getY3();
        void moverEsquerda();
        void moverDireita();
        void setComponente(std::string componente, int valor);
};

#endif // AVIAO_H
