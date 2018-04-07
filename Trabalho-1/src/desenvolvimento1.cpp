/*
 * Autores: Diego Paiva e Lohan Ferreira
 * Data de criação: 07/04/2018
 * Descrição: Trabalho 1 - River Raid
*/

#include <GL/glut.h>
#include <iostream>
#include <string.h>

#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 600

#define QUANTIDADE_ESFERAS_A_COLETAR 100

void init();
void display();
void imprimirTexto(char const *texto, int x, int y);
void mouse(int button, int state, int x, int y);
void idle();
void motion(int x, int y);

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
   glutInitWindowPosition(200, 100);
   glutCreateWindow("River Raid");
   init();
   glutDisplayFunc(display);
   glutIdleFunc(idle);
   glutMainLoop();
   return 0;
}

void init()
{
   glClearColor (0.0, 0.0, 1.0, 0.0);

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();

   glOrtho(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT, -30.0, 30.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity ();
}


void display()
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glutSwapBuffers();
}

void imprimirTexto(char const *texto, int x, int y)
{
   int length = (int) strlen(texto);

   // Posição do texto na tela
   glRasterPos3f(x, y, 0.0);

   for(int i = 0; i < length; i++) {
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, texto[i]);
   }

}


void motion(int x, int y)
{
	// Inverte mouse para que origem fique no canto inferior esquerdo da janela
	// (por default, a origem é no canto superior esquerdo)
	y = WINDOW_HEIGHT - y;

}

void idle()
{
    float t, dt;
    static float tLast = 0.0;

    /* Get elapsed time and convert to s */
    t = glutGet(GLUT_ELAPSED_TIME);

    t /= 1000.0;

    /* Calculate delta t */
    dt = t - tLast;

    /* Update velocity and position */

    /* Update tLast for next time, using static local variable */
    tLast = t;

    /* Ask glut to schedule call to display function */
    glutPostRedisplay();
}
