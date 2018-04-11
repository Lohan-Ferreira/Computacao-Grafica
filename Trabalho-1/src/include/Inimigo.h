#ifndef INIMIGO_H
#define INIMIGO_H

#define TAMANHO 20

#include <GL/glut.h>

class Inimigo
{
    public:
        Inimigo(int x, int y);
        ~Inimigo();
        void desenhar();
    private:
        int x;
        int y;

};

#endif // INIMIGO_H
