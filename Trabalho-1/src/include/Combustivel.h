#ifndef COMBUSTIVEL_H
#define COMBUSTIVEL_H

#include <GL/glut.h>

class Combustivel
{
    public:
        Combustivel(int x, int y);
        ~Combustivel();
        void desenhar();
    private:
        int x;
        int y;
};

#endif // COMBUSTIVEL_H
