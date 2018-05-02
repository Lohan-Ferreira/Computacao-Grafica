#ifndef FACE_H
#define FACE_H
#include "Vertex.h"

class Face
{
    public:
        Face(int n);
        ~Face();
    void addVert(Vertex *v);
    Vertex **lista; //Lista de vertices
    Vertex *normal; //Vetor normal representado como um elemento vertex  por facilidade
    int n_max;
    int n_atual;

    private:
    void calculaNormal();

};

#endif // FACE_H
