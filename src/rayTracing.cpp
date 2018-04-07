/*
  Raytracing Project
  Copyright:   Version 0.1
  Author:      Rodrigo Luis de Souza da Silva
  Last Update: 23/10/2014
  Release:     23/10/2004
  Description: Simple Raytracing Project
               This project is an adaptation of the source code available here:
               https://code.google.com/p/glraytracer/
*/
#include "rayTracer.h"

using namespace std;
char cenario[] = {"../data/rayTracingScene01.txt"};

void init();
void display();
void keyboard(unsigned char key, int x, int y);
void specialKey(int key, int x, int y){};
void mouseButton(int button, int state, int x, int y){};
void idleFunc(){glutPostRedisplay();}

// Globals
glraytracer *glProject = NULL;

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

   // set up the physical window size
   glutInitWindowSize(WIDTH, HEIGHT);

   // set the name of the window and try to create it
   int window = glutCreateWindow("GL Raytracer");

	// Create Orthographic projection Matrix
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0, WIDTH, 0, HEIGHT);

   /* create project and read input file */
   glProject = new glraytracer(WIDTH, HEIGHT);
   glProject->readDatabase(cenario);
   glProject->setWindow(window);

	// Compute raytrace only once
   glProject->raytrace();

   glutKeyboardFunc(keyboard);
   glutSpecialFunc(specialKey);
   glutMouseFunc(mouseButton);
   glutDisplayFunc(display);
   glutIdleFunc(idleFunc);

   glutMainLoop();
   return (0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glProject->draw();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key)
   {
      case 27 :
         exit(0);
      break;
   }
   glutPostRedisplay();
}
