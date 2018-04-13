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
        void oscilar(int esquerda, int direita);
    private:
        int x;
        int y;
        int direcaoMovimento;

};

#endif // INIMIGO_H
