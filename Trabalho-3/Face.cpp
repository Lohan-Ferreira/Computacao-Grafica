#include "Face.h"
#include <iostream>
#include <math.h>
Face::Face(int n)
{
    n_max=n;
    n_atual=0;
   lista = new Vertex* [n];

}


void Face::addVert(Vertex *v)
{

    if(n_atual < n_max)
    {
        lista[n_atual] = v;
        n_atual++;

        if(n_atual == n_max)
        {

            calculaNormal();

        }
    }

}

void Face::calculaNormal()
{


    float u[3],v[3];
    u[0] = lista[1]->x - lista[0]->x;
    u[1] = lista[1]->y - lista[0]->y;
    u[2] = lista[1]->z - lista[0]->z;

    v[0] = lista[n_max-1]->x - lista[0]->x;
    v[1] = lista[n_max-1]->y - lista[0]->y;
    v[2] = lista[n_max-1]->z - lista[0]->z;

    normal = new Vertex(0,0,0);
    normal->x =  u[1]*v[2] - v[1] * u[2];
    normal->y = - (u[0]*v[2]-v[0]*u[2]) ;
    normal->z = u[0]*v[1] - v[0] * u[1];

    float modulo = sqrt((normal->x * normal->x)+(normal->y * normal->y)+(normal->z * normal->z));
    normal->x /= modulo;
    normal->y /= modulo;
    normal->z /= modulo;
}

Face::~Face()
{
    //dtor
}
