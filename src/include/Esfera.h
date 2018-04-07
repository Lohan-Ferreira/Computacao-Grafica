#ifndef ESFERA_H
#define ESFERA_H

#include <GL/glut.h>
#include <math.h>
#include "Plano.h"

class Esfera
{
    public:
        Esfera(GLdouble radius, GLdouble slices, GLdouble stacks, int x, int y);
        ~Esfera();
        void renderizar();
        void setX(int x);
        void setY(int y);
        int getX();
        int getY();
        bool estaDentro(int x, int y);
        bool colideComEsfera(Esfera *esfera);
        bool colideComPlano(Plano *plano);
        bool foiColetada();
        bool emMovimento();
        void movimentar();
        void coletar();
        GLdouble getRadius();
    private:
        GLdouble radius;
        GLdouble slices;
        GLdouble stacks;
        int x;
        int y;
        bool movimentando;
        void desenhar();
        void transladar(GLfloat x, GLfloat y, GLfloat z);
};

#endif // ESFERA_H
