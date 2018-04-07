#ifndef PLANO_H
#define PLANO_H

#include <GL/glut.h>

class Plano
{
    public:
        Plano(int xInicial, int xFinal, int altura);
        ~Plano();
        void desenhar();
        int getAltura();
    private:
        int xInicial;
        int xFinal;
        int altura;
};

#endif // PLANO_H
