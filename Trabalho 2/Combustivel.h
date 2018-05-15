#ifndef COMBUSTIVEL_H
#define COMBUSTIVEL_H

#include <GL/glut.h>
#include <math.h>

class Combustivel
{
    private:
            int tamanho;
            int x;
            int y;
            int z;
    public:
        Combustivel(int x, int y);
        ~Combustivel();
        void desenhar();
        int getX();
        int getY();
        int getTamanho();
};

#endif // COMBUSTIVEL_H
