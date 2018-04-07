/*
  Name:        animationBase.cpp
  Copyright:   Version 0.1
  Author:      Rodrigo Luis de Souza da Silva
  Last Update:	23/08/2016
  Date:        23/08/2016
  Description: Arquivo base para o exercício da auila de animação
*/

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "extras.h"

#define ACELERATION 9.8

// Globals
int width  = 1000;
int height = 500;
float rotationX = 0.0, rotationY = 0.0;
int x = 40, y = 450;
int y0 = 450;
int direction = 1;
float vx = 0, vy = 8;

void init();
void display();
void reshape(int w, int h);
void motion(int x, int y);
void keyboard(unsigned char key, int x, int y);
void idle();

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (width, height);
   glutInitWindowPosition (100, 100);
   glutCreateWindow("Animation Base");
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutMotionFunc( motion );
   glutKeyboardFunc(keyboard);
   glutIdleFunc(idle);
   glutMainLoop();
   return 0;
}

void init(void)
{
   glClearColor (0.5, 0.5, 0.5, 0.0);
   glShadeModel (GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);               // Habilita Z-buffer
   initLight(width, height);
}

void display(void)
{
   float sphereSize = 30.0;
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glOrtho(0.0, width, 0.0, height, -sphereSize, sphereSize);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity ();

   setMaterial();

   glTranslatef(x, y, 0.0); // Posicionamento inicial da esfera
   glutSolidSphere(20.0, 100, 100);

   glutSwapBuffers();
}

void reshape (int w, int h)
{
   width = w;
   height = h;
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
}

void motion(int x, int y)
{
   glutPostRedisplay();
}

void keyboard (unsigned char key, int x, int y)
{
   if(tolower(key) == 27) exit(0);
}

void idle()
{
   float t, dt;
   static float time = 0.0;
   static float tLast = 0.0;

   /* Get elapsed time and convert to s */
   t = glutGet(GLUT_ELAPSED_TIME);
   t /= 1000.0;

   /* Calculate delta t */
   dt = t - tLast;

   /* Update velocity and position */
   if(y <= 0 || y >= height) {
     direction *= -1;
   }

   printf("%f\n", time);
   time += 0.01;

   y = ((y0 + vy*time) - ((ACELERATION*time*time)/2)) * direction;

   vy = (vy - ACELERATION*time);

   x++;

   /* Update tLast for next time, using static local variable */
   tLast = t;

   /* Ask glut to schedule call to display function */
   glutPostRedisplay();
}
