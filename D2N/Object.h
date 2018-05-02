#ifndef OBJECT_H
#define OBJECT_H
#include "Face.h"
#include "Vertex.h"
#include <fstream>
#include <GL/glut.h>



class Object
{
    public:
        Object();
        ~Object();

        Face **faces;
        void addFace(Face *f);
        void desenha(bool kind);
        void lerArq(char* name);
        int n_atual;
        int n_max;

};

#endif // OBJECT_H
