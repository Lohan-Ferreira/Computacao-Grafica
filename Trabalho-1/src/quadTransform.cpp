/*
  Name:        quad_transform.cpp
  Copyright:   Version 0.1
  Author:      Rodrigo Luis de Souza da Silva
  Date:        16/09/2004
  Description: Transformations using of OpenGL commands


#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define TRANSLATION_RATE 3
#define SCALE_RATE 1
#define ANGLE_RATE 5

float angle = 0, scale = 1.0;
float xtrans = 0, ytrans = 0, ztrans = 0;

void display(void);
void init (void);
void desenhaEixos();
void specialKeysPress(int key, int x, int y);
void keyboard(unsigned char key, int x, int y);
void showMenu();

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
   glutInitWindowSize (300, 300);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Exercicio 1 - Aula 04");
   init ();
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(specialKeysPress);
   glutMainLoop();
   return 0;
}

void showMenu()
{
   system("clear");
   printf("======= MENU ========\n");
   printf("1 - Pressione as setas direcionais do teclado para mover o objeto\n");
   printf("2 - Pressione '+' para aumentar a escala do objeto e '-' para reduzir\n");
   printf("3 - Pressione 'R' pra rotacionar o objeto no sentido horário e 'T' para rotacionar no sentido anti-horário\n");
}

void desenhaEixos()
{
   glColor3f (0.0, 1.0, 0.0);
   glBegin(GL_LINES);
      glVertex2f (0.0, -100.0);
      glVertex2f (0.0, 100.0);
      glVertex2f (-100.0, 0.0);
      glVertex2f (100.0, 0.0);
   glEnd();
}

void display(void)
{
   // Limpar todos os pixels
   glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glLoadIdentity(); // Inicializa com matriz identidade

   desenhaEixos();

   glColor3f (1.0, 0.0, 0.0);

   glPushMatrix();
      glTranslatef(xtrans, ytrans, 0.0);
      glRotatef(angle, 0.0, 0.0, 1.0);
      glScalef(scale, scale, scale);
      glutWireCube(10);
   glPopMatrix();

   glutSwapBuffers ();
   glutPostRedisplay();
}

void init (void)
{
   // selecionar cor de fundo (preto)
   glClearColor (0.0, 0.0, 0.0, 0.0);
   // inicializar sistema de viz.
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   showMenu();

}

void specialKeysPress(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_RIGHT:
            xtrans += TRANSLATION_RATE;
        break;
        case GLUT_KEY_LEFT:
            xtrans -= TRANSLATION_RATE;
        break;
        case GLUT_KEY_UP:
            ytrans += TRANSLATION_RATE;
        break;
        case GLUT_KEY_DOWN:
            ytrans -= TRANSLATION_RATE;
        break;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case '+':
            if(scale >= 1.0)
                scale += SCALE_RATE;
        break;
        case '-':
            if(scale > 1.0)
                scale -= SCALE_RATE;
        break;
        case 'R':
            angle += ANGLE_RATE;
        break;
        case 'T':
            angle -= ANGLE_RATE;
        break;
    }
    glutPostRedisplay();
}
*/


/*
  Name:        quad_transform.cpp
  Copyright:   Version 0.1
  Author:      Rodrigo Luis de Souza da Silva
  Date:        16/09/2004
  Description: Transformations using of OpenGL commands
*/

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <../shared/glcFPSViewer.h>

float desiredFPS = 60;
float var = 0.0f;
float dir = 1.0f;
glcFPSViewer *fpsViewer = new glcFPSViewer((char*) "Triangle Animation. ", (char*) " - Press ESC to Exit");
float angle = 0, angleRate = 0, scale = 1.0f;
float xtrans = 0, ytrans = 0, ztrans = 0, xtransRate = 0, ytransRate = 0;
int enableMenu = 0;
float scaleRate = 1.0f;

void display(void);
void init (void);
void desenhaEixos();
void showMenu();
void mouse(int button, int state, int x, int y);
void idle();


int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
   glutInitWindowSize (300, 300);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("hello");
   glutMouseFunc( mouse );
   glutIdleFunc(idle);
   init ();
   printf("Posicione as janelas e clique na janela do OpenGL para habilitar o menu.\n");
   glutDisplayFunc(display);
   glutMainLoop();

   return 0;
}

void idle()
{
    float t, desiredFrameTime, frameTime;
    static float tLast = 0.0;

    // Get elapsed time
    t = glutGet(GLUT_ELAPSED_TIME);
    // convert milliseconds to seconds
    t /= 1000.0;

    // Calculate frame time
    frameTime = t - tLast;
    // Calculate desired frame time
    desiredFrameTime = 1.0 / (float) (desiredFPS);

    // Check if the desired frame time was achieved. If not, skip animation.
    if( frameTime <= desiredFrameTime)
        return;

    /*
     *UPDATE ANIMATION VARIABLES
     */

    if(scaleRate < scale)
    {
        scaleRate += 0.05;
    }

    if(xtransRate < xtrans) {
        xtransRate += 0.5;
    }
    else if(xtransRate > xtrans ) {
        xtransRate -= 0.5;
    }

    if(ytransRate < ytrans) {
        ytransRate += 0.5;
    }
    else if(ytransRate > ytrans) {
        ytransRate -= 0.5;
    }

    if(angleRate < angle) {
        angleRate += 0.5;
    }
    /* Update tLast for next time, using static local variable */
    tLast = t;

    glutPostRedisplay();
}

// Mouse callback
void mouse(int button, int state, int x, int y)
{
   if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
      enableMenu = 1;
}

void showMenu()
{
   int op;
   system("clear");
   printf("\n=== MENU ===");
   printf("\n1 - Translacao");
   printf("\n2 - Rotacao");
   printf("\n3 - Escala");
   printf("\n4 - Sair");
   printf("\nOpcao: ");
   scanf("%d", &op);
   switch(op)
   {
      case 1:
         printf("\n\nInforme o vetor de translacao (entre -100.0 e 100.0)");
         printf("\nX : ");
         scanf("%f", &xtrans);
         printf("Y : ");
         scanf("%f", &ytrans);
      break;
      case 2:
         printf("\n\nInforme o angulo de rotacao (em graus): ");
         scanf("%f", &angle);
      break;
      case 3:
         printf("Informe o fator de escala: ");
         scanf("%f", &scale);
      break;
      case 4:
         exit(1);
      break;
      default:
         printf("\n\nOpcao invalida\n\n");
      break;
   }
}

void desenhaEixos()
{
   glColor3f (0.0, 1.0, 0.0);
   glBegin(GL_LINES);
      glVertex2f (0.0, -100.0);
      glVertex2f (0.0, 100.0);
      glVertex2f (-100.0, 0.0);
      glVertex2f (100.0, 0.0);
   glEnd();
}

void display(void)
{
   // Limpar todos os pixels
   glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glLoadIdentity(); // Inicializa com matriz identidade

   desenhaEixos();

   glColor3f (1.0, 0.0, 0.0);

   glPushMatrix();
      glTranslatef(xtransRate, ytransRate, 0.0);
      glRotatef(angleRate, 0.0, 0.0, 1.0);
      glScalef(scaleRate, scaleRate, scaleRate);
      glutWireCube(10);
   glPopMatrix();
   glutSwapBuffers ();

   if(enableMenu) showMenu();

   // Print FPS
   fpsViewer->drawFPS();
}

void init (void)
{
   // selecionar cor de fundo (preto)
   glClearColor (0.0, 0.0, 0.0, 0.0);

   // inicializar sistema de viz.
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

