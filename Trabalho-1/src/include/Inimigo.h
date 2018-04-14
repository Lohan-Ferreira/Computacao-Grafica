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
        bool colisaoN( double x1,double y1, double x2, double y2, double x3, double y3 );
        bool colisaoP(double xp, double yp);
    private:
        int x;
        int y;
        int direcaoMovimento;

};

#endif // INIMIGO_H
