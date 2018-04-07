/*
  Name:        05_viewport
  Copyright:   Version 0.1
  Author:      Diego Paiva e Silva
  Date:        11/03/2018
  Description: Testing more than one viewports
*/

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WINDOW_SIZE_WIDTH 800
#define WINDOW_SIZE_HEIGHT 600

void init();
void display();
void keyboard(unsigned char key, int x, int y);
void desenhaEixosCoordenados();
void desenhaTrianguloSuperiorDireito();
void desenhaSimboloInferiorEsquerdo();
void desenhaTrianguloInferiorDireito();
void desenhaObjetos();

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT);
    glutInitWindowPosition(300, 100);
    glutCreateWindow("Exercício 3");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
}

void display()
{
   // Define viewport do canto inferior esquerdo
   glViewport ((int) 0, (int) 0, (int) WINDOW_SIZE_WIDTH/2, (int) WINDOW_SIZE_HEIGHT/2);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glOrtho(0.0, 0.55, 0.0, 0.55, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   desenhaObjetos();

   // Define viewport do canto superior direito
   glViewport ((int) 410, (int) 310, (int) WINDOW_SIZE_WIDTH/2, (int) WINDOW_SIZE_HEIGHT/2);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glOrtho(0.45, 1.05, 0.45, 1.05, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   desenhaObjetos();

   // Define viewport do cantor inferior direito
   glViewport ((int) 410, (int) 0, (int) WINDOW_SIZE_WIDTH/2, (int) WINDOW_SIZE_HEIGHT/2);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glOrtho(0.45, 1.05, 0.0, 0.55, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   desenhaObjetos();

   // Define viewport do cantor superior esquerdo
   glViewport ((int) 0, (int) 300, (int) WINDOW_SIZE_WIDTH/2, (int) WINDOW_SIZE_HEIGHT/2);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   desenhaObjetos();

   glutSwapBuffers();
   glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 27:
            exit(0);
        break;
    }
    glutPostRedisplay();
}

void desenhaObjetos()
{
    desenhaEixosCoordenados();
    desenhaTrianguloSuperiorDireito();
    desenhaTrianguloInferiorDireito();
    desenhaSimboloInferiorEsquerdo();
}

void desenhaEixosCoordenados()
{
    // Eixo x
    glColor3f(0.50, 0.75, 1.0);
    glBegin(GL_LINES);
        glVertex3f(0.0, 0.5, 0.0);
        glVertex3f(1.0, 0.5, 0.0);
    glEnd();

    // Eixo y
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
        glVertex3f(0.5, 0.0, 0.0);
        glVertex3f(0.5, 1.0, 0.0);
    glEnd();
}

void desenhaTrianguloSuperiorDireito()
{
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex3f(0.60, 0.60, 0.0);
        glVertex3f(0.90, 0.60, 0.0);
        glVertex3f(0.60, 0.90, 0.0);
    glEnd();
}

void desenhaTrianguloInferiorDireito()
{
    glColor3f(0.0, 0.80, 0.50);
    glBegin(GL_LINE_LOOP);
        glVertex3f(0.60, 0.40, 0.0);
        glVertex3f(0.90, 0.40, 0.0);
        glVertex3f(0.60, 0.10, 0.0);
    glEnd();
}

void desenhaSimboloInferiorEsquerdo()
{
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);
        glVertex3f(0.40, 0.40, 0.0);
        glVertex3f(0.10, 0.40, 0.0);
        glVertex3f(0.40, 0.10, 0.0);
        glVertex3f(0.10, 0.10, 0.0);
    glEnd();
}


/*
float altura = 400, largura = 400;

void  DesenhaEixos();
void  DesenhaObjetos1();
void  DesenhaObjetos2();
void  display(void);
void  keyboard(unsigned char key, int x, int y);
void  init(void);

//////////////////////////////////////////////////
// Main Function
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
   glutInitWindowSize ((int)largura,(int)altura);
   glutInitWindowPosition (20,20);
   glutCreateWindow ("Viewport Test");
   init ();
   glutDisplayFunc(display);  // Eh quem ira chamar todo o restante das funçoes
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}

//////////////////////////////////////////////////
// Functions

// Inicializa opengl
void init(void)
{
   glClearColor(0.0,0.0, 0.0, 0.0);
   glShadeModel(GL_SMOOTH);
}

// Eixos coordenados
void DesenhaEixos()
{
   glBegin(GL_LINES);
      glColor3f (1.0, 0.0, 0.0);
      glVertex3f(-10.0, 0.0, 0.0);
      glVertex3f( 10.0, 0.0, 0.0);
      glColor3f (  0.0,   1.0, 0.0);
      glVertex3f(0.0, -10.0, 0.0);
      glVertex3f(0.0,  10.0, 0.0);
   glEnd();
}

void DesenhaObjetos()
{
   glColor3f(1.0, 1.0, 0.0);
   glBegin(GL_POLYGON);
      glVertex3f(2.0, 2.0, 0.0);
      glVertex3f(8.0, 2.0, 0.0);
      glVertex3f(2.0, 8.0, 0.0);
   glEnd();
}

///////////////////////////////////////////////////////////
// Glut and image functions
void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // Define viewport do canto inferior esquerdo
   glViewport ((int) 10, (int) 10, (int) 190, (int) 190);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glOrtho(-10.0, 10.0, -10.0, 10.0, -1, 1);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   DesenhaEixos();
   DesenhaObjetos();

   // Define segunda viewport
   glViewport ((int) 200, (int) 200, (int) 190, (int) 190);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glOrtho(1.0, 9.0, 1.0, 9.0, -1, 1);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   DesenhaEixos();
   DesenhaObjetos();

   glutSwapBuffers();
   glutPostRedisplay();
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
*/

