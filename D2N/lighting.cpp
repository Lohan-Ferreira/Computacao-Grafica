/*
  Name:        iluminacao_simples.cpp
  Copyright:   Version 0.1
  Author:      Rodrigo Luis de Souza da Silva
  Last Update:	29/11/2013
  Date:        16/09/2004
  Description: Codigo simples com apenas uma fonte de luz.
*/

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include "Object.h"

// Globals
#define NUM 180
#define PI 3.1415927

using namespace std;


fstream file;
float current = 0;
float angle = 0;
float raio = 1.5;
float dir = 1;
bool idleOn = true;
int width  = 800;
int height = 600;
float rotationX = 0.0, rotationY = 0.0;
int   last_x, last_y;
Object* cow;

void init(void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);               // Habilita Z-buffer
   glEnable(GL_LIGHTING);                 // Habilita luz
   glEnable(GL_LIGHT0);                   // habilita luz 0

   // Cor da fonte de luz (RGBA)
   GLfloat cor_luz[]     = { 1.0, 1.0, 1.0, 1.0};
   GLfloat cor_luz2[]     = {0.2,0.2,0.2,1.0f};
   // Posicao da fonte de luz. Ultimo parametro define se a luz sera direcional (0.0) ou tera uma posicional (1.0)
   GLfloat posicao_luz[] = { 5.0, 5.0, 5.0, 1.0};

   // Define parametros da luz
   glLightfv(GL_LIGHT0, GL_AMBIENT,cor_luz2);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, cor_luz);
   glLightfv(GL_LIGHT0, GL_SPECULAR, cor_luz);
   glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz);
}

void setMaterial(void)
{
   // Material do objeto (neste caso, ruby). Parametros em RGBA
   GLfloat objeto_ambient[]   = { 0.32, 0.22, 0.02, 1.0 };
   GLfloat objeto_difusa[]    = { 0.78, .56, .11, 1.0 };
   GLfloat objeto_especular[] = { .99, .94, .8, 1.0 };
   GLfloat objeto_brilho[]    = { 27.98f };

   // Define os parametros da superficie a ser iluminada
   glMaterialfv(GL_FRONT, GL_AMBIENT, objeto_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, objeto_difusa);
   glMaterialfv(GL_FRONT, GL_SPECULAR, objeto_especular);
   glMaterialfv(GL_FRONT, GL_SHININESS, objeto_brilho );
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(45.0, (GLfloat) width/(GLfloat) height, 1.0, 200.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity ();
   gluLookAt (0.0, 0.0, 5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   // Movimenta a camera em torno do objeto
   // Luz fica fixa na posicao (0, 0, 5) inicialmente
   glRotatef( rotationY, 1.0, 0.0, 0.0 );
   glRotatef( rotationX, 0.0, 1.0, 0.0 );

   // Define o material a ser utilizado pelo objeto abaixo
  setMaterial();
  glColor3f(1,0,0);
   float g;
   int i;
    cow->desenha(false);


   glutSwapBuffers();
}

void reshape (int w, int h)
{
   width = w;
   height = h;
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
}

void keyboard (unsigned char key, int x, int y)
{
   if(tolower(key) == 27) exit(0);
}

// Motion callback
void motion(int x, int y )
{
   rotationY += (float) (y - last_y);
   rotationX += (float) (x - last_x);

   last_x = x;
   last_y = y;
   glutPostRedisplay();
}


void idle()
{

   glutPostRedisplay();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (width, height);
   glutInitWindowPosition (100, 100);
   glutCreateWindow("Simple Ilumination");
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutMotionFunc( motion );
   glutIdleFunc(idle);
   glutKeyboardFunc(keyboard);
    cow = new Object();
    cow->lerArq("snowman.ply");

   glutMainLoop();
   return 0;
}
