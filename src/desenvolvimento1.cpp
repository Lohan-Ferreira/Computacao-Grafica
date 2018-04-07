/*
 * Autor: Diego Paiva
 * Data de criação: 30/03/2018
 * Descrição: Desenvolvimento 1 - Sistema de colisão
 *
 * Fonte utilizada para estudo da colisão esfera-esfera: http://www.swiftless.com/tutorials/opengl/collision.html
 *
 * Fontes utilizadas para geração de números aleatórios: http://www.cplusplus.com/reference/cstdlib/srand/
 *                                                       http://www.cplusplus.com/reference/cstdlib/rand/
 *
 * Fontes utilizadas para imprimir texto (pontuação e gameover) na tela: https://stackoverflow.com/questions/2183270/what-is-the-easiest-way-to-print-text-to-screen-in-opengl
 *                                                                       http://www.cplusplus.com/reference/string/to_string/
 *
 * Fonte utilizada para mudar material (esmeralda) das esferas que caem: http://devernay.free.fr/cours/opengl/materials.html
*/

#include <GL/glut.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string.h>
#include "extras.h"
#include "Esfera.h"
#include "Plano.h"

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

#define QUANTIDADE_ESFERAS_A_COLETAR 100

void init();
void inicializarEsferas();
void display();
void desenharVidas();
bool ehPrimeiraEsfera(int index);
void gameOver();
void vitoria();
void imprimirTexto(char const *texto, int x, int y);
void mouse(int button, int state, int x, int y);
void idle();
void motion(int x, int y);


Esfera *esferaPrincipal  = new Esfera(30.0, 200, 200, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
Esfera *esferas[QUANTIDADE_ESFERAS_A_COLETAR];
Plano  *plano = new Plano(0.0, WINDOW_WIDTH, 50.0);
int pontos = 0;
int vidas = 3;
int esferasColididas = 0;

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
   glutInitWindowPosition(300, 100);
   glutCreateWindow("Coletor de esferas");
   srand(time(NULL));
   init();
   inicializarEsferas();
   glutDisplayFunc(display);
   glutMouseFunc(mouse);
   glutIdleFunc(idle);
   glutMainLoop();
   return 0;
}

void init()
{
   glClearColor (0.6, 0.4, 1.0, 0.0);

   glShadeModel (GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);
   initLight(WINDOW_WIDTH, WINDOW_HEIGHT);

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glOrtho(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT, -30.0, 30.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity ();
}

void inicializarEsferas()
{
    for(int i = 0; i < QUANTIDADE_ESFERAS_A_COLETAR; i++) {
        esferas[i] = new Esfera(rand() % 15 + 15, 200, 200, rand() % WINDOW_WIDTH-100 + 100, WINDOW_HEIGHT+30);
    }
}

void display()
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   char const *pontuacao = std::to_string(pontos).c_str();
   imprimirTexto(pontuacao, WINDOW_WIDTH - 30, WINDOW_HEIGHT - 30);

   plano->desenhar();

   desenharVidas();

   setRubyMaterial();
   esferaPrincipal->renderizar();

   setEmeraldMaterial();
   for(int i = 0; i < QUANTIDADE_ESFERAS_A_COLETAR; i++) {

       if(!esferas[i]->foiColetada()) {

           if(ehPrimeiraEsfera(i)) {
               esferas[i]->movimentar();
               esferas[i]->renderizar();
           }
           else if(!ehPrimeiraEsfera(i) && esferas[i-1]->foiColetada()) {
               esferas[i]->renderizar();
           }

           if(esferas[i]->colideComPlano(plano)) {
               esferas[i]->coletar();
               esferas[i] = NULL;
               esferas[i+1]->movimentar();
               vidas--;
               if(vidas <= 0) {
                  glutDisplayFunc(gameOver);
               }
               esferasColididas++;
           }
           else if(esferas[i]->colideComEsfera(esferaPrincipal)) {
               esferas[i]->coletar();
               esferas[i] = NULL;
               esferas[i+1]->movimentar();
               pontos++;
               esferasColididas++;
           }
       }
   }

   if(esferasColididas == QUANTIDADE_ESFERAS_A_COLETAR) {
        glutDisplayFunc(vitoria);
   }

   glutSwapBuffers();
}

bool ehPrimeiraEsfera(int index)
{
    return index == 0;
}

void desenharVidas()
{
    for(int k = 0; k < vidas; k++)
    {
        glPushMatrix();
            glColor3f(1.0, 0.0, 0.0);
            glTranslatef(30 + 50 * k, 570, 0.0);
            glutSolidSphere(20.0, 100, 100);
        glPopMatrix();
    }
}

void gameOver()
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0);

    char const *texto = "GAME OVER";
    imprimirTexto(texto, WINDOW_WIDTH/2 - 80, WINDOW_HEIGHT/2);

    glutSwapBuffers();
}

void vitoria()
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0);

    char const *texto = "VOCE VENCEU";
    imprimirTexto(texto, WINDOW_WIDTH/2 - 80, WINDOW_HEIGHT/2);

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

void mouse(int button, int state, int x, int y)
{
	// Inverte mouse para que origem fique no canto inferior esquerdo da janela
	// (por default, a origem é no canto superior esquerdo)
	y = WINDOW_HEIGHT - y;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
        if(esferaPrincipal->estaDentro(x, y)) {
           glutMotionFunc(motion);
        }
        else {
           glutMotionFunc(NULL);
        }
	}
}

void motion(int x, int y)
{
	// Inverte mouse para que origem fique no canto inferior esquerdo da janela
	// (por default, a origem é no canto superior esquerdo)
	y = WINDOW_HEIGHT - y;

    esferaPrincipal->setX(x);
    esferaPrincipal->setY(y);
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

    for(int i = 0; i < QUANTIDADE_ESFERAS_A_COLETAR; i++) {

        if(!esferas[i]->foiColetada() && esferas[i]->emMovimento()) {
            esferas[i]->setY(esferas[i]->getY() - (rand() % 20 + 1));
        }

    }

    /* Update tLast for next time, using static local variable */
    tLast = t;

    /* Ask glut to schedule call to display function */
    glutPostRedisplay();
}
