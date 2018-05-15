#include "Object.h"
#include <GL/glut.h>
#include <fstream>
#include <cstring>
#include <iostream>
#include <cmath>

Object::Object(char* fileName)
{
    n_max = 0;
    n_atual = 0;
    this->lerArq(fileName);

}


void Object::addFace(Face *f)
{
    if(n_atual < n_max)
    {
        faces[n_atual] = f;
        n_atual++;
    }
}

void Object::desenha(bool kind)
{
    GLenum mode;
    if(n_atual == n_max)
    {

        for(int i=0; i<n_max;i++)
        {
            if(kind == 0) mode = GL_LINE_LOOP;
            else if(faces[i]->n_max == 4) mode = GL_QUADS;
            else mode = GL_TRIANGLES;
            glNormal3f(faces[i]->normal->x, faces[i]->normal->y,faces[i]->normal->z);
            glBegin(mode);
                for(int j=0; j<faces[i]->n_max;j++)
                    glVertex3f(faces[i]->lista[j]->x,faces[i]->lista[j]->y,faces[i]->lista[j]->z);
            glEnd();
        }
    }
}


void Object::lerArq(char* fileName)
{
    int n_vert;
    int n_faces;

    std::fstream file;
    file.open(fileName, std::ios::in | std::ios::out);
    file.clear();
    file.seekg(0, std::ios::beg);

    char *c = new char [100];
    file>>c;

    while ( strcmp(c,"vertex") != 0 )
    {

        file>>c;

    }

    file>>n_vert;
        while ( strcmp(c,"face") != 0 )
    {
        file>>c;
    }
    file>>n_faces;
    while ( strcmp(c,"end_header") != 0 ){file>>c;}

    std::cout<<n_vert<<" "<<n_faces<<std::endl;

    Vertex** vertices = new Vertex* [n_vert];
    faces = new Face* [n_faces];
    n_max = n_faces;

    float x,y,z;
    for(int i=0; i<n_vert;i++)
    {
        file>>x>>y>>z;
        vertices[i] = new Vertex(x,y,z);
        file.getline(c,100);
    }

    int qnt;
    int pos;

    for(int i=0; i<n_faces;i++)
    {

        file>>qnt;

        faces[i] = new Face(qnt);
        n_atual++;
        for(int j=0; j<qnt; j++)
        {

            file>>pos;

            faces[i]->addVert(vertices[pos]);

        }

    }

    file.close();

    float maior=0;

    //Centralizando Objeto
   float avx=0,avy=0,avz=0;
   for(int i=0; i<n_vert ; i++)
   {
       avx += vertices[i]->x;
       avy += vertices[i]->y;
       avz += vertices[i]->z;

   }
   avx = avx / (float) n_vert;
   avy = avy / (float) n_vert;
   avz = avz / (float) n_vert;

   for(int i = 0 ; i<n_vert ; i++)
   {
       vertices[i]->x -= avx;

       if(maior < std::abs(vertices[i]->x)) maior = std::abs(vertices[i]->x);

       vertices[i]->y -= avy;

        if(maior < std::abs(vertices[i]->y)) maior = std::abs(vertices[i]->y);

       vertices[i]->z -= avz;

       if(maior < std::abs(vertices[i]->y)) maior = std::abs(vertices[i]->z);
   }


      for(int i = 0 ; i<n_vert ; i++)
   {
       vertices[i]->x /= maior;


       vertices[i]->y /= maior;


       vertices[i]->z /= maior;

   }


}

Object::~Object()
{
    //dtor
}
