/*
 * Autores: Diego Paiva e Lohan Ferreira
 * Data de criação: 07/04/2018
 * Descrição: Trabalho 1 - River Raid
 *
*/

#include <GL/glut.h>
#include <iostream>
#include <string.h>

#define WINDOW_WIDTH  900
#define WINDOW_HEIGHT 600

void init();
void display();
void imprimirTexto(char const *texto, int x, int y);
void mouse(int button, int state, int x, int y);
void idle();
void motion(int x, int y);

int orthoFirstY = 0;
int orthoLastY = 750;

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

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity ();
}

void display()
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();

   glOrtho(-200, 200, orthoFirstY, orthoLastY, -1.0, 1.0);

   glColor3f(0.1, 1.0, 0.4);
   glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(80,  0,    0);
    glVertex3f(200, 0,    0);
    glVertex3f(80,  300,  0);
    glVertex3f(200, 300,  0);
    glVertex3f(120, 500,  0);
    glVertex3f(200, 500,  0);
    glVertex3f(120, 1000, 0);
    glVertex3f(200, 1000, 0);
    glVertex3f(80,  1200, 0);
    glVertex3f(200, 1200, 0);
    glVertex3f(80,  1500, 0);
    glVertex3f(200, 1500, 0);
    glVertex3f(110, 1700, 0);
    glVertex3f(200, 1700, 0);
    glVertex3f(110, 1900, 0);
    glVertex3f(200, 1900, 0);
    glVertex3f(120, 2000, 0);
    glVertex3f(200, 2000, 0);
    glVertex3f(120, 2100, 0);
    glVertex3f(200, 2100, 0);
    glVertex3f(110, 2200, 0);
    glVertex3f(200, 2200, 0);
    glVertex3f(110, 2500, 0);
    glVertex3f(200, 2500, 0);
    glVertex3f(120, 2600, 0);
    glVertex3f(200, 2600, 0);
    glVertex3f(120, 2800, 0);
    glVertex3f(200, 2800, 0);
    glVertex3f(140, 3000, 0);
    glVertex3f(200, 3000, 0);
    glVertex3f(140, 3500, 0);
    glVertex3f(200, 3500, 0);
    glVertex3f(120, 4000, 0);
    glVertex3f(200, 4000, 0);
    glVertex3f(120, 4200, 0);
    glVertex3f(200, 4200, 0);
    glVertex3f(140, 4400, 0);
    glVertex3f(200, 4400, 0);
    glVertex3f(140, 5000, 0);
    glVertex3f(200, 5000, 0);
    glVertex3f(160, 5300, 0);
    glVertex3f(200, 5300, 0);
    glVertex3f(160, 7000, 0);
    glVertex3f(200, 7000, 0);
    glVertex3f(140, 7300, 0);
    glVertex3f(200, 7300, 0);
    glVertex3f(140, 7600, 0);
    glVertex3f(200, 7600, 0);
    glVertex3f(160, 7600, 0);
    glVertex3f(200, 8000, 0);
    glVertex3f(160, 8000, 0);
    glVertex3f(200, 9000, 0);
    glVertex3f(80,  9000, 0);
    glVertex3f(200, 10000, 0);
    glVertex3f(80,  10000, 0);
    glVertex3f(200, 10300, 0);
    glVertex3f(120, 10300, 0);
    glVertex3f(200, 12000, 0);
    glVertex3f(120, 12000, 0);
    glVertex3f(200, 12300, 0);
    glVertex3f(80,  12300, 0);
    glVertex3f(200, 12600, 0);
    glVertex3f(80,  12600, 0);
    glVertex3f(200, 12800, 0);
    glVertex3f(120, 12800, 0);
    glVertex3f(200, 13000, 0);
    glVertex3f(120, 13000, 0);
    glVertex3f(200, 14000, 0);
    glVertex3f(80,  14000, 0);
    glVertex3f(200, 15000, 0);
    glVertex3f(80,  15000, 0);
   glEnd();

   glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(-80, 0, 0);
    glVertex3f(-200, 0, 0);
    glVertex3f(-80, 300, 0);
    glVertex3f(-200, 300, 0);
    glVertex3f(-120, 500, 0);
    glVertex3f(-200, 500, 0);
    glVertex3f(-120, 1000, 0);
    glVertex3f(-200, 1000, 0);
    glVertex3f(-80, 1200, 0);
    glVertex3f(-200, 1200, 0);
    glVertex3f(-80, 1500, 0);
    glVertex3f(-200, 1500, 0);
    glVertex3f(-110, 1700, 0);
    glVertex3f(-200, 1700, 0);
    glVertex3f(-110, 1900, 0);
    glVertex3f(-200, 1900, 0);
    glVertex3f(-120, 2000, 0);
    glVertex3f(-200, 2000, 0);
    glVertex3f(-120, 2100, 0);
    glVertex3f(-200, 2100, 0);
    glVertex3f(-110, 2200, 0);
    glVertex3f(-200, 2200, 0);
    glVertex3f(-110, 2500, 0);
    glVertex3f(-200, 2500, 0);
    glVertex3f(-120, 2600, 0);
    glVertex3f(-200, 2600, 0);
    glVertex3f(-120, 2800, 0);
    glVertex3f(-200, 2800, 0);
    glVertex3f(-140, 3000, 0);
    glVertex3f(-200, 3000, 0);
    glVertex3f(-140, 3500, 0);
    glVertex3f(-200, 3500, 0);
    glVertex3f(-120, 4000, 0);
    glVertex3f(-200, 4000, 0);
    glVertex3f(-120, 4200, 0);
    glVertex3f(-200, 4200, 0);
    glVertex3f(-140, 4400, 0);
    glVertex3f(-200, 4400, 0);
    glVertex3f(-140, 5000, 0);
    glVertex3f(-200, 5000, 0);
    glVertex3f(-160, 5300, 0);
    glVertex3f(-200, 5300, 0);
    glVertex3f(-160, 7000, 0);
    glVertex3f(-200, 7000, 0);
    glVertex3f(-140, 7300, 0);
    glVertex3f(-200, 7300, 0);
    glVertex3f(-140, 7600, 0);
    glVertex3f(-200, 7600, 0);
    glVertex3f(-160, 7600, 0);
    glVertex3f(-200, 8000, 0);
    glVertex3f(-160, 8000, 0);
    glVertex3f(-200, 9000, 0);
    glVertex3f(-80, 9000, 0);
    glVertex3f(-200, 10000, 0);
    glVertex3f(-80, 10000, 0);
    glVertex3f(-200, 10300, 0);
    glVertex3f(-120, 10300, 0);
    glVertex3f(-200, 12000, 0);
    glVertex3f(-120, 12000, 0);
    glVertex3f(-200, 12300, 0);
    glVertex3f(-80,  12300, 0);
    glVertex3f(-200, 12600, 0);
    glVertex3f(-80,  12600, 0);
    glVertex3f(-200, 12800, 0);
    glVertex3f(-120, 12800, 0);
    glVertex3f(-200, 13000, 0);
    glVertex3f(-120, 13000, 0);
    glVertex3f(-200, 14000, 0);
    glVertex3f(-80,  14000, 0);
    glVertex3f(-200, 15000, 0);
    glVertex3f(-80,  15000, 0);
   glEnd();

   // Primeiro obstaculo que fica dentro da parte azul
   glBegin(GL_POLYGON);
    glVertex3f(-30, 3050, 0);
    glVertex3f(-30, 3400, 0);
    glVertex3f(30, 3400, 0);
    glVertex3f(30, 3050, 0);
   glEnd();

   // Segundo obstaculo que fica dentro da parte azul
   glBegin(GL_POLYGON);
    glVertex3f(0, 4100, 0);
    glVertex3f(-60, 4200, 0);
    glVertex3f(-60, 4400, 0);
    glVertex3f(-25, 4500, 0);
    glVertex3f(-25, 4700, 0);
    glVertex3f(0, 4800, 0);
    glVertex3f(25, 4700, 0);
    glVertex3f(25, 4500, 0);
    glVertex3f(60, 4400, 0);
    glVertex3f(60, 4200, 0);
   glEnd();

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

    // 15000 = ortho maximo y
    if(orthoLastY < 15000) {
        orthoLastY+=2;
        orthoFirstY+=2;
    }


    /* Update tLast for next time, using static local variable */
    tLast = t;

    /* Ask glut to schedule call to display function */
    glutPostRedisplay();
}
