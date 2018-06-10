#ifndef INIMIGO_H
#define INIMIGO_H

#define TAMANHO 20

#include <GL/glut.h>
#include "Aviao.h"

class Inimigo
{
    public:
        Inimigo(int x, int y);
        ~Inimigo();
        void desenhar(Object *o, double y1, double y2);
        void oscilar(int esquerda, int direita);
        bool colisaoN(Aviao *aviao);
        bool colisaoP(double xp, double yp);
        bool isCheckPoint;
        int getY(){return y;}
    private:
        int x;
        int y;
        int direcaoMovimento;


};

#endif // INIMIGO_H
