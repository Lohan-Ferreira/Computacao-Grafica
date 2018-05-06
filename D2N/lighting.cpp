#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include "Object.h"
#include <stdlib.h>
#include <cstdio>

using namespace std;

fstream file;

bool idleOn = true;
int width  = 800;
int height = 600;
float rotationX = 0.0, rotationY = 0.0;
int   last_x, last_y;
Object *cow,*bunny,*budda,*dragon,*snowman;
int option = 1;
bool mode = true;
bool fullscreen = false;
float z = 5;
char *c = new char[50];

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
   GLfloat objeto_ambient[]   = { 0.05f,0.05f,0.0f,1.0f };
   GLfloat objeto_difusa[]    = {0.5f,0.5f,0.4f,1.0f};
   GLfloat objeto_especular[] = {0.7f,0.7f,0.04f,1.0f };
   GLfloat objeto_brilho[]    = { 10.0f };

   // Define os parametros da superficie a ser iluminada
   glMaterialfv(GL_FRONT, GL_AMBIENT, objeto_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, objeto_difusa);
   glMaterialfv(GL_FRONT, GL_SPECULAR, objeto_especular);
   glMaterialfv(GL_FRONT, GL_SHININESS, objeto_brilho );
}

void setMaterial2(void)
{
   // Material do objeto (neste caso, ruby). Parametros em RGBA
   GLfloat objeto_ambient[]   = { 0.2125f, 0.1275f, 0.054f, 1.0f };
   GLfloat objeto_difusa[]    = { 0.714f, 0.4284f, 0.18144f, 1.0f };
   GLfloat objeto_especular[] = { 0.393548f, 0.271906f, 0.166721f, 1.0f };
   GLfloat objeto_brilho[]    = { 25.6f };

   // Define os parametros da superficie a ser iluminada
   glMaterialfv(GL_FRONT, GL_AMBIENT, objeto_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, objeto_difusa);
   glMaterialfv(GL_FRONT, GL_SPECULAR, objeto_especular);
   glMaterialfv(GL_FRONT, GL_SHININESS, objeto_brilho );
}



void setMaterial3(void)
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


void setMaterial4(void)
{
   // Material do objeto (neste caso, ruby). Parametros em RGBA
   GLfloat objeto_ambient[]   = { 0.0215f, 0.1745f, 0.0215f, 0.55f };
   GLfloat objeto_difusa[]    = {0.07568f, 0.61424f, 0.07568f, 0.55f };
   GLfloat objeto_especular[] = {0.633f, 0.727811f, 0.633f, 0.55f };
   GLfloat objeto_brilho[]    = { 76.8f };

   // Define os parametros da superficie a ser iluminada
   glMaterialfv(GL_FRONT, GL_AMBIENT, objeto_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, objeto_difusa);
   glMaterialfv(GL_FRONT, GL_SPECULAR, objeto_especular);
   glMaterialfv(GL_FRONT, GL_SHININESS, objeto_brilho );
}



void setMaterial5(void)
{
   // Material do objeto (neste caso, ruby). Parametros em RGBA
   GLfloat objeto_ambient[]   = { 0.05f,0.05f,0.05f,1.0f };
   GLfloat objeto_difusa[]    = { 0.5f,0.5f,0.5f,1.0f};
   GLfloat objeto_especular[] = { 0.7f,0.7f,0.7f,1.0f};
   GLfloat objeto_brilho[]    = { 5.0f };

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
   gluLookAt (0.0, 0.0, z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   // Movimenta a camera em torno do objeto
   // Luz fica fixa na posicao (0, 0, 5) inicialmente
   glRotatef( rotationY, 1.0, 0.0, 0.0 );
   glRotatef( rotationX, 0.0, 1.0, 0.0 );

   // Define o material a ser utilizado pelo objeto abaixo

  glColor3f(1,0,0);

    if(option == 1)
    {
        snprintf(c,50,"Numero de triangulos: %d",cow->n_max);
        glutSetWindowTitle(c);
        setMaterial();
        cow->desenha(mode);
    }
    if(option == 2)
    {
        snprintf(c,50,"Numero de triangulos: %d",bunny->n_max);
        glutSetWindowTitle(c);
        setMaterial2();
        bunny->desenha(mode);
    }
    if(option == 3)
    {
        snprintf(c,50,"Numero de triangulos: %d",budda->n_max);
        glutSetWindowTitle(c);
        setMaterial3();
        budda->desenha(mode);
    }
    if(option == 4)
    {
        snprintf(c,50,"Numero de triangulos: %d",dragon->n_max);
        glutSetWindowTitle(c);
        setMaterial4();
        dragon->desenha(mode);
    }
    if(option == 5)
    {
        snprintf(c,50,"Numero de triangulos: %d",snowman->n_max);
        glutSetWindowTitle(c);
        setMaterial5();
        snowman->desenha(mode);
    }



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

   switch(key)
   {
       case '1': option = 1; break;
       case '2': option = 2; break;
       case '3': option = 3; break;
       case '4': option = 4; break;
       case '5': option = 5; break;
       case 'w': mode = false; break;
       case 's': mode = true; break;
       case 'm':
        {
            if(!fullscreen)
            {
                fullscreen=true;
                glutFullScreen();
            }

            else
            {
                fullscreen = false;
                glutReshapeWindow(800, 600);
            }
            break;
        }
   }
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

void mouse(int button, int state, int x, int y)
{
    float TAXA_VARIACAO_ZOOM = 0.25;
    if(button == 4 && z <= 25) {
        z += TAXA_VARIACAO_ZOOM;
    }
    if(button == 3 && z >= 2.5) {
        z -= TAXA_VARIACAO_ZOOM;
    }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (800, 600);
   glutInitWindowPosition (100, 100);
   glutCreateWindow("");
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutMotionFunc( motion );
   glutIdleFunc(idle);
   glutMouseFunc(mouse);
   glutKeyboardFunc(keyboard);
    cow = new Object("ply/cow.ply");
    bunny = new Object("ply/bunny.ply");
    budda = new Object("ply/budda.ply");
    dragon = new Object("ply/dragon.ply");
    snowman =new Object("ply/snowman.ply");

    cout<<"Controles:"<<endl;
    cout<<"1 : Vaca"<<endl;
    cout<<"2 : Coelho"<<endl;
    cout<<"3 : Buda"<<endl;
    cout<<"4 : Dragon"<<endl;
    cout<<"5 : Boneco de Neve"<<endl;
    cout<<"w : Visualizar em wireframe"<<endl;
    cout<<"s : Visualizar em superficie"<<endl;
    cout<<"Mouse Scroll : Zoom IN/OUT"<<endl;
    cout<<"m : FullScreen ON/OFF";

   glutMainLoop();
   return 0;
}
