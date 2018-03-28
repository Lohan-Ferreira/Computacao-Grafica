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
#include <time.h>
#include <iostream>
#include <math.h>
#include <string>
#include <sstream>


// Globals
int width  = 700;
int height = 700;

double mainX=350,mainY=400, mRadius=30;     //Coordenadas iniciais e tamanho da esfera principal
int nballs = 100;                            //Numero de esferas a ser gerado pelo programa
int pontos = 0;
int vidas = 3;
int pressed = 0;                             //Verifica se houve um click dentro da esfera
double lastx,lasty;                          //coordenadas do ultimo clique para movimentação do mouse
//double planx, plany, planz;



class Ball
{
public:

    Ball(double cx,double cy,double rad,double sp)
    {
        x=cx;
        y=cy;
        radius=rad;
        speed = sp;
    }
    double x,y,radius,speed;
    int colisao()
    {
        //Verifica colisão com a esfera princnipal
        if(sqrt((x-mainX)*(x-mainX) + (y-mainY)*(y-mainY)) <= (mRadius + radius) )
        {
            return 1;
        }

        //Verifica colisão com o plano no final
        if(y - radius <= 20 )
        {
            return 2;
        }
        return 0;
    }
};


Ball **balls;


void idle()
{
   int state=0;
    //for(int i=0; i < nballs; i++)
    //{
    if (nballs > 0)
    {

        //Chama verificador de colisões
        state = balls[0]->colisao();
        balls[0]->y -= balls[0]->speed;

        //Se colidiu com a esfera principal
        if(state == 1)
        {

            pontos++;
            std::cout<<pontos;                 //Aumenta pontuação
            delete balls[0];            //Desaloca esfera
            balls[0] = balls[nballs-1]; //Reorganiza a fila de esferas
            nballs--;
            //i--;
        }


        //Se colidiu com o plano no fundo
        else if (state == 2)
        {
            vidas--;                           //Diminui Vidas
            delete balls[0];
            balls[0] = balls[nballs-1];
            nballs--;
           // i--;
        }

    }



    //}

    glutPostRedisplay();
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



   // Limpar todos os pixels
    glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

     glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
	glOrtho(0.0, width, 0.0, height, -mRadius, mRadius);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity ();


    //Ideia retirada do forum StackOverflow para exibir a pontuação
    //
    std::ostringstream ss;
    ss << pontos;
    std::string x = ss.str();
    glRasterPos3f(650, 650, mRadius);
    for(int i=0; i<x.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, x.at(i) );



    setMaterial();


    //Plano y=20;
    glPushMatrix();
    glTranslatef(width/2,20,0);
    glScalef(width, 1.0, 1.0);
    glutSolidCube(1);
    glPopMatrix();

    //Esfera Principal
    glPushMatrix();
    glTranslatef(mainX,mainY,0);
    glutSolidSphere(mRadius,100,100);
    glPopMatrix();


    //Modifica material para diferenciar as esferas
    setMaterial2();

    //Esferas Secundárias
    if(nballs > 0)
    {


        glPushMatrix();
        glTranslatef(balls[0]->x,balls[0]->y,0);

        glutSolidSphere(balls[0]->radius,100,100);
        glPopMatrix();
    }

    //Codigo para mostrar todas as esferas instantaneamente
   /* for(int i=0; i< nballs; i++)
    {
        glPushMatrix();
        glTranslatef(balls[i]->x,balls[i]->y,0);

        glutSolidSphere(balls[i]->radius,100,100);
        glPopMatrix();

    }*/


    //Display das vidas restantes
    setMaterial();
    for(int i=1; i<=vidas;i++)
    {

        glPushMatrix();
        glTranslatef(200+ 20*i,10,0);
        glutSolidSphere(10,100,100);
        glPopMatrix();

    }




    glutSwapBuffers ();
    glutPostRedisplay();

}

void reshape (int w, int h)
{
   width = w;
   height = h;
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        for(int i=0; i < nballs; i++)
            delete balls[i];
        delete balls;
        exit(0);
        break;
    }
}


void motion(int x, int y )
{

    //Controle da movimentação do mouse clicado

    y = 700 - y;
    if (pressed)
    {
        mainX += (double)x-lastx;
        mainY += (double)y-lasty;

        lastx=x;
        lasty=y;
    }


}



void mouse(int button, int state, int x, int y)
{

    //Verifica se houve um click dentro da esfera para iniciar arraste

    y = 700-y;
    if ( button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN )
        {
            if(( x<= mainX + mRadius && x >= mainX - mRadius) && ( y<= mainY + mRadius && y >= mainY - mRadius))
            {
                pressed = 1;
                lastx=x;
                lasty=y;
            }
        }

        else
            pressed = 0;


    }
}

int main(int argc, char** argv)
{
    srand (time(NULL));
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (width, height);
   glutInitWindowPosition (-100, -100);
   glutCreateWindow("Ball Game");
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutMotionFunc( motion );
   glutKeyboardFunc(keyboard);
   glutMouseFunc(mouse);
   glutIdleFunc(idle);



   //Criando as bolas
    balls = new Ball*[nballs];
    for(int i=0; i< nballs; i++)
    {
        balls[i] = new Ball(rand()%700 + 1, rand()% 100 + 600, rand()%10 + 10, ((float) (rand() % 80 + 20) ) / 50.0);
    }


   glutMainLoop();
   return 0;
}
