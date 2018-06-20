/*
 * Autores: Diego Paiva e Lohan Ferreira
 * Data de criação: 07/04/2018
 * Descrição: Trabalho 1 - River Raid
 */

#include <GL/glut.h>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <time.h>
#include "Aviao.h"
#include "Inimigo.h"
#include "Combustivel.h"
#include <string>
#include <fstream>
#include "Object.h"
#include "glcTexture.h"
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <vector>


#define WINDOW_WIDTH  900
#define WINDOW_HEIGHT 600
#define QUANTIDADE_CHECKPOINTS 6

#define QUANTIDADE_INIMIGOS 68
#define QUANTIDADE_COMBUSTIVEL 43

#define ORTHO_MAXIMO 18000

Aviao *aviao = new Aviao();

class Quad
{
public:
    double x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4;
    double n1x,n1y,n1z,n2x,n2y,n2z;
    double maiorz, menorz;
    Quad *next;
    int tag;
    bool spec;
    Quad()
    {
        tag = 0;
        next = NULL;
        spec = 0;
    }

    void calculaNormal()
    {
        float u[3],v[3];
        u[0] = x2 - x1;
        u[1] = y2 - y1;
        u[2] = z2 - z1;

        v[0] = x4 - x1;
        v[1] = y4 - y1;
        v[2] = z4 - z1;


        n1x =  u[1]*v[2] - v[1] * u[2];
        n1y = - (u[0]*v[2]-v[0]*u[2]) ;
        n1z = u[0]*v[1] - v[0] * u[1];

        float modulo = sqrt((n1x * n1x)+(n1y * n1y)+(n1z * n1z));
        n1x /= modulo;
        n1y /= modulo;
        n1z /= modulo;
         if (n1z < 0) n1z *= -1;

        /*-------------------------------------------------*/
        u[0] = x3 - x2;
        u[1] = y3 - y2;
        u[2] = z3 - z2;

        v[0] = x4 - x2;
        v[1] = y4 - y2;
        v[2] = z4 - z2;


        n2x =  u[1]*v[2] - v[1] * u[2];
        n2y = - (u[0]*v[2]-v[0]*u[2]) ;
        n2z = u[0]*v[1] - v[0] * u[1];

        modulo = sqrt((n2x * n2x)+(n2y * n2y)+(n2z * n2z));
        n2x /= modulo;
        n2y /= modulo;
        n2z /= modulo;
        if (n2z < 0) n2z *= -1;



    }

};

class Projetil
{
    public:
    double x,y;
    Projetil()
    {
        x = aviao->getX3();
        y = aviao->getY3();
    }


};

Projetil *projetil[50] = {NULL};
int i_projetil=0;

class Reta
{

public:
    double x1, x2, y1,y2;                                   //Coordenadas
    double VO[2];                                           //Vetor Ortogonal
    double PI;                                              //Pré calculo para comparações rapidas (Produto Interno)
    int side;                                               //Verifica qual o lado da colisão ( 0 direita da reta , 1 esquerda da reta)
    bool verificaX;                                         //Flag caso verificação de eixo X seja necessária
    int dx;                                                 //Distancia no eixo X entre os pontos
    Reta(double px1, double py1, double px2, double py2, int s, bool vx)
    {
        x1 = px1;
        x2 = px2;
        y1 = py1;
        y2 = py2;
        side = s;
        dx = abs (x2 - x1);

        verificaX = vx;

        //Define vetor ortogonal rotacionando o vetor p1-p2 em 90º
        VO[0] = -(y2 - y1);
        VO[1] =  (x2 - x1);

        PI = x1 * VO[0] + y1 * VO[1];
    }

    int colisao()
    {

        if (aviao->getY1() >= y1 && aviao->getY2() <= y2 )
         {
                int PI2 = aviao->getX1() * VO[0] + aviao->getY1() * VO[1];

                if(side)
                {
                    if (PI2 <= PI)
                    {
                        if(verificaX)
                        {
                            if(abs(aviao->getX1() - x1) <= dx + 0.5 && abs(aviao->getX1() - x2) <= dx + 0.5)
                                return 1;
                        }
                        else return 1;
                    }
                }
                else
                {
                    if (PI2 >= PI)
                    {
                        if(verificaX)
                        {
                            if(abs(aviao->getX1() - x1) <= dx + 0.5 && abs(aviao->getX1() - x2) <= dx + 0.5)
                                return 1;
                        }
                        else return 1;
                    }
                }
        }
        if (aviao->getY2() >= y1 && aviao->getY2() <= y2)
        {

                int PI2 = aviao->getX2() * VO[0] + aviao->getY2() * VO[1];

                if(side)
                {
                    if (PI2 <= PI)
                    {
                        if(verificaX)
                        {
                            if(abs(aviao->getX2() - x1) <= dx + 0.5 && abs(aviao->getX2() - x2) <= dx + 0.5)
                                return 1;
                        }

                        else return 1;
                    }
                }
                else
                {
                    if (PI2 >= PI)
                    {
                        if(verificaX)
                        {
                            if(abs(aviao->getX2() - x1) <= dx + 0.5 && abs(aviao->getX2() - x2) <= dx + 0.5)
                                return 1;
                        }

                        else return 1;

                    }
                }

        }

        if (aviao->getY3() >= y1 && aviao->getY3() <= y2)
        {

                int PI2 = aviao->getX3() * VO[0] + aviao->getY3() * VO[1];

                if(side)
                {
                    if (PI2 <= PI)
                    {
                        if(verificaX)
                        {
                            if(abs(aviao->getX3() - x1) <= dx + 0.5 && abs(aviao->getX3() - x2) <= dx + 0.5)
                                return 1;
                        }
                        else return 1;
                    }
                }
                else
                {
                    if (PI2 >= PI)
                    {
                        if(verificaX)
                        {
                            if(abs(aviao->getX3() - x1) <= dx + 0.5 && abs(aviao->getX3() - x2) <= dx + 0.5)
                                return 1;
                        }
                        else return 1;
                    }
                }

        }
        return 0;
    }

    int colisaoP(Projetil *projetil)
    {
        if (projetil->y >= y1-6 && projetil->y <= y2+6 )
         {
                int PI2 = projetil->x * VO[0] + projetil->y * VO[1];

                if(side)
                {
                    if (PI2 <= PI)
                    {
                        if(verificaX)
                        {
                            if(abs(projetil->x-x1) <= dx+0.5 && abs(projetil->x-x2) <= dx+0.5)
                                return 1;
                        }
                        else return 1;
                    }
                }
                else
                {
                    if (PI2 >= PI)
                    {
                        if(verificaX )
                        {
                            if(abs(projetil->x-x1) <= dx+0.5 && abs(projetil->x-x2) <= dx+0.5)
                                return 1;
                        }
                        else return 1;
                    }
                }

        }
        return 0;
    }
};


glcTexture *textureManager;
int returny1 = aviao->getY1(),returny2 = aviao->getY2(), returny3 = aviao->getY3();
int placar[11];
Reta **retas;
Inimigo **inimigos;
Inimigo **checkpoints;
int nretas = 0;
double orthoFirstY = 0;
double orthoLastY = 500;
bool fullscreen = false;
bool orthoview = false;
int gameState = 0; // Estados do jogo 0 tela inicial, 1 jogando, 2 pausado, 3 fim de jogo, 4 placar
int vidas = 3;
int pontos = 0;
float porcentagemCombustivel = 100;
Combustivel *combustiveis[QUANTIDADE_COMBUSTIVEL];
std::fstream file;
int oldState;
int velocidade;
float translatey = 0.0;
float translatex= 0.0;
float move_x=0.0;
float rotation = 0.0;
float rotator = 0.0;
Object *enemy;






std::vector<Quad*> *quads;
void init();
void inicializarInimigo();
void inicializarCombustiveis();
void display();
void imprimirTexto(char const *texto, int x, int y);
void mouse(int button, int state, int x, int y);
void specialKeys(int key, int x, int y);
void keyboard(unsigned char key, int x, int y);
void idle();
void motion(int x, int y);
void reconfigurar();
void ordena(int v[], int tam);


void RMD()
{
    Quad *quad;
//Inicia vector com quads base
    for(int i=0; i<nretas;i++)
        {
            quad = new Quad();
            if(retas[i]->x1>0 && !retas[i]->verificaX)
            {


            quad->x1 = retas[i]->x1;
            quad->y1 = retas[i]->y1;
            quad->z1 = 0;

            quad->x2 = 300;
            quad->y2 = retas[i]->y1;
            quad->z2 = 41;

            quad->x3 = 300;
            quad->y3 = retas[i]->y2;
            quad->z3 = 41;


            quad->x4 = retas[i]->x2;
            quad->y4 = retas[i]->y2;
            quad->z4 = 0;


            }
            else if(!retas[i]->verificaX)
            {

            quad->x1 = -300;
            quad->y1 = retas[i]->y1;
            quad->z1 = 41;

            quad->x2 = retas[i]->x1;
            quad->y2 = retas[i]->y1;
            quad->z2 = 0;

            quad->x3 = retas[i]->x2;
            quad->y3 = retas[i]->y2;
            quad->z3 = 0;


            quad->x4 = -300;
            quad->y4 = retas[i]->y2;
            quad->z4 = 41;

            }
            else if(retas[i]->side==1)
            {

            quad->spec = true;
            quad->x1 = retas[i]->x1;
            quad->y1 = retas[i]->y1;
            quad->z1 = 10;

            quad->x2 = -retas[i]->x1;
            quad->y2 = retas[i]->y1;
            quad->z2 = 10;

            quad->x3 = -retas[i]->x2;
            quad->y3 = retas[i]->y2;
            quad->z3 = 10;


            quad->x4 = retas[i]->x2;
            quad->y4 = retas[i]->y2;
            quad->z4 = 10;
            }

            quads->push_back(quad);
        }

    quad = quads->front();

    while(quad->tag<=2)
    {
        if(quad->spec && ((quad->x1 == quad->x2) || (quad->x3 == quad->x4)))
        {
            quads->push_back(quad);
            quads->erase(quads->begin());
            std::cout<<quad->spec;
            quad = quads->front();
            continue;

        }
            std::cout<<quad->tag;
        Quad *q1,*q2,*q3,*q4;
        double mx,my,mz;
        mx = (quad->x1 + quad->x3)/ 2;
        my = (quad->y1 + quad->y3)/ 2;
        if(quad->tag == 0)
            if(quad->x1 == 0) mz = 30;
            else
            mz = 70;
        else
        {
            mz = (quad->z1+quad->z2+quad->z3+quad->z4)/4.0;
            if(rand()%2 == 1)
            {
                mz = mz - (rand() % 16);
            }
            else
            {
                mz = mz + rand() % 16;
            }

        }



        q1 = new Quad();
        q1->tag = quad->tag + 1;
        q2 = new Quad();
        q2->tag = quad->tag + 1;
        q3 = new Quad();
        q3->tag = quad->tag + 1;
        q4 = new Quad();
        q4->tag = quad->tag + 1;

        q1->spec=q2->spec=q3->spec=q4->spec=quad->spec;

        q1->x1 = quad->x1;
        q1->y1 = quad->y1;
        q1->z1 = quad->z1;

        q1->x2 = mx;
        q1->y2 = q1->y1;
        q1->z2 = (quad->z1 + quad->z2)/2.0;

        q1->x3 = mx;
        q1->y3 = my;
        q1->z3 = mz;

        if(quad->x1 == 0) q1->x4 = (my-quad->y1)/((quad->y1 - quad->y4)/(quad->x1-quad->x4));
        else
        q1->x4 = (quad->x1+quad->x4)/2;
        q1->y4 = my;
        q1->z4 = (quad->z1+quad->z4)/2.0;



    /*----------------------*/
        q2->x1 = q1->x2;
        q2->y1 = q1->y2;
        q2->z1 = q1->z2;

        q2->x2 = quad->x2;
        q2->y2 = quad->y2;
        q2->z2 = quad->z2;

        if(quad->x2 == 0) q2->x3 = (my-quad->y2)/((quad->y3 - quad->y2)/(quad->x3-quad->x2));
        else
        q2->x3 = (quad->x2+quad->x3)/2;
        q2->y3 = my;
        q2->z3 = (quad->z2 + quad->z3)/2.0;

        q2->x4 = mx;
        q2->y4 = my;
        q2->z4 = mz;

    /*---------------------*/

        q3->x1 = mx;
        q3->y1 = my;
        q3->z1 = mz;

        q3->x2 = q2->x3;
        q3->y2 = q2->y3;
        q3->z2 = q2->z3;

        q3->x3 = quad->x3;
        q3->y3 = quad->y3;
        q3->z3 = quad->z3;

        q3->x4 = mx;
        q3->y4 = quad->y3;
        q3->z4 = (quad->z3+quad->z4)/2.0;

    /*-------------------*/

        q4->x1 = q1->x4;
        q4->y1 = q1->y4;
        q4->z1 = q1->z4;

        q4->x2 = mx;
        q4->y2 = my;
        q4->z2 = mz;

        q4->x3 = q3->x4;
        q4->y3 = q3->y4;
        q4->z3 = q3->z4;

        q4->x4 = quad->x4;
        q4->y4 = quad->y4;
        q4->z4 = quad->z4;


        quads->push_back(q1);
        quads->push_back(q2);
        quads->push_back(q3);
        quads->push_back(q4);
        quads->erase(quads->begin());
        quad = quads->front();

    }

    for(int i=0; i<quads->size(); i++)
        quads->at(i)->calculaNormal();

}

void specialKeysRelease(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT:
            move_x = 0;
            break;
        case GLUT_KEY_UP:
        case GLUT_KEY_DOWN:
            velocidade=0;
    }
}

void keyboardRelease(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'd' :
		case 'a' :
		    move_x=0.0;
		    rotation = 0.0;
		    rotator = 0.0;
        break;
        case 'w':
        case 's':
            velocidade = 0;
		break;
	}
}




void setMaterial(void)
{

   GLfloat objeto_ambient[]   = { .1745, .01175, .01175, 1.0 };
   GLfloat objeto_difusa[]    = { .61424, .04136, .04136, 1.0 };
   GLfloat objeto_especular[] = { .727811, .626959, .626959, 1.0 };
   GLfloat objeto_brilho[]    = { 90.0f };

   // Define os parametros da superficie a ser iluminada
   glMaterialfv(GL_FRONT, GL_AMBIENT, objeto_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, objeto_difusa);
   glMaterialfv(GL_FRONT, GL_SPECULAR, objeto_especular);
   glMaterialfv(GL_FRONT, GL_SHININESS, objeto_brilho);
}


void setMaterial2(void)
{

GLfloat mat_ambient[] ={ 0.05375f, 0.05f, 0.06625f, 0.82f };
GLfloat mat_diffuse[] ={ 0.18275f, 0.17f, 0.22525f, 0.82f};
GLfloat mat_specular[] ={0.332741f, 0.328634f, 0.346435f, 0.82f };
GLfloat shine[] = {38.4f};

   // Define os parametros da superficie a ser iluminada
   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, shine);
}

void setMaterial3(void)
{

GLfloat mat_ambient[] ={ 0.0215f, 0.1745f, 0.0215f, 0.55f };
GLfloat mat_diffuse[]= {0.07568f, 0.61424f, 0.07568f, 0.55f };
GLfloat mat_specular[] ={0.633f, 0.727811f, 0.633f, 0.55f };
GLfloat shine[] = {76.8f};

   // Define os parametros da superficie a ser iluminada
   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, shine);
}


void setMaterial4(void)
{

GLfloat mat_ambient[] ={ 0.24725f, 0.1995f, 0.0745f, 1.0f };
GLfloat mat_diffuse[]= {0.75164f, 0.60648f, 0.22648f, 1.0f };
GLfloat mat_specular[] ={0.628281f, 0.555802f, 0.366065f, 1.0f };
GLfloat shine[] = {51.2f};

   // Define os parametros da superficie a ser iluminada
   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, shine);
}

void setMaterial5(void)
{

GLfloat mat_ambient[] ={0.25f, 0.148f, 0.06475f, 1.0f  };
GLfloat mat_diffuse[]= {0.4f, 0.2368f, 0.1036f, 1.0f };
GLfloat mat_specular[] ={0.774597f, 0.458561f, 0.200621f, 1.0f };
GLfloat shine[] = {76.8f};

   // Define os parametros da superficie a ser iluminada
   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, shine);
}


void setMaterial6(void)
{

GLfloat mat_ambient[] ={ 0.1f, 0.18725f, 0.1745f, 0.8f };
GLfloat mat_diffuse[]={0.396f, 0.74151f, 0.69102f, 0.8f };
GLfloat mat_specular[] ={0.297254f, 0.30829f, 0.306678f, 0.8f };
GLfloat shine[] = {0.1f};

   // Define os parametros da superficie a ser iluminada
   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, shine);
}



int main(int argc, char** argv)
{

    quads = new std::vector<Quad*>();
    glutInit(&argc, argv);
    srand(time(NULL));
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(200, 100);

    glutCreateWindow("River Raid");
    init();

    glutIgnoreKeyRepeat(0);
    glutKeyboardUpFunc( keyboardRelease );
    glutSpecialUpFunc(specialKeysRelease);
    srand(time(NULL));
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutIdleFunc(idle);
    inimigos = new Inimigo* [QUANTIDADE_INIMIGOS];
    retas = new Reta* [400];
    checkpoints = new Inimigo* [QUANTIDADE_CHECKPOINTS];
    inicializarInimigo();
    inicializarCombustiveis();
    enemy = new Object("chopper.ply");


    file.open("pontos.txt" , std::ios::in | std::ios::out);
    for(int i=0; i<10; i++)
        file>>placar[i];
    file.clear();
    file.seekg(0, std::ios::beg);
    //Lado Direito
    retas[nretas] = new Reta(50,0,50,250,1,false);
    nretas++;
    retas[nretas] = new Reta(50,250,120,300,1,false);
    nretas++;
    retas[nretas] = new Reta(120,300,120,1800,1,false);
    nretas++;
    retas[nretas] = new Reta(120,1800,50,1850,1,false);
    nretas++;
    retas[nretas] = new Reta(50,1850,50,2100,1,false);
    nretas++;
    retas[nretas] = new Reta(50,2100,120,2150,1,false);
    nretas++;
    retas[nretas] = new Reta(120,2150,150,2200,1,false);
    nretas++;
    retas[nretas] = new Reta(150,2200,150,2250,1,false);
    nretas++;
    retas[nretas] = new Reta(150,2250,120,2300,1,false);
    nretas++;
    retas[nretas] = new Reta(120,2300,120,2500,1,false);
    nretas++;
    retas[nretas] = new Reta(120,2500,150,2550,1,false);
    nretas++;
    retas[nretas] = new Reta(150,2550,150,2650,1,false);
    nretas++;
    retas[nretas] = new Reta(150,2650,170,2700,1,false);
    nretas++;
    retas[nretas] = new Reta(170,2700,170,3400,1,false);
    nretas++;
    retas[nretas] = new Reta(170,3400,50,3450,1,false);
    nretas++;
    retas[nretas] = new Reta(50,3450,50,3750,1,false);
    nretas++;
    retas[nretas] = new Reta(50,3750,100,3800,1,false);
    nretas++;
    retas[nretas] = new Reta(100,3800,100,4000,1,false);
    nretas++;
    retas[nretas] = new Reta(100,4000,120,4050,1,false);
    nretas++;
    retas[nretas] = new Reta(120,4050,120,5000,1,false);
    nretas++;
    retas[nretas] = new Reta(120,5000,50,5050,1,false);
    nretas++;
    retas[nretas] = new Reta(50,5050,50,5300,1,false);
    nretas++;
    retas[nretas] = new Reta(50,5300,100,5301,1,false);
    nretas++;
    retas[nretas] = new Reta(100,5301,100,5350,1,false);
    nretas++;
    retas[nretas] = new Reta(100,5350,50,5400,1,false);
    nretas++;
    retas[nretas] = new Reta(50,5400,50,5550,1,false);
    nretas++;
    retas[nretas] = new Reta(50,5550,90,5600,1,false);
    nretas++;
    retas[nretas] = new Reta(90,5600,90,9000,1,false);
    nretas++;
    retas[nretas] = new Reta(90,9000,50,9050,1,false);
    nretas++;
    retas[nretas] = new Reta(50,9050,50,9400,1,false);
    nretas++;
    retas[nretas] = new Reta(50,9400,110,9450,1,false);
    nretas++;
    retas[nretas] = new Reta(110,9450,110,9500,1,false);
    nretas++;
    retas[nretas] = new Reta(110,9500,60,9550,1,false);
    nretas++;
    retas[nretas] = new Reta(60,9550,60,10000,1,false);
    nretas++;
    retas[nretas] = new Reta(60,10000,120,10050,1,false);
    nretas++;
    retas[nretas] = new Reta(120,10050,120,10200,1,false);
    nretas++;
    retas[nretas] = new Reta(120,10200,130,10201,1,false);
    nretas++;
    retas[nretas] = new Reta(130,10201,130,10400,1,false);
    nretas++;
    retas[nretas] = new Reta(130,10400,140,10401,1,false);
    nretas++;
    retas[nretas] = new Reta(140,10401,140,10600,1,false);
    nretas++;
    retas[nretas] = new Reta(140,10600,160,10650,1,false);
    nretas++;
    retas[nretas] = new Reta(160,10650,160,11400,1,false);
    nretas++;
    retas[nretas] = new Reta(160,11400,120,11450,1,false);
    nretas++;
    retas[nretas] = new Reta(120,11450,120,11650,1,false);
    nretas++;
    retas[nretas] = new Reta(120,11650,140,11700,1,false);
    nretas++;
    retas[nretas] = new Reta(140,11700,140,12550,1,false);
    nretas++;
    retas[nretas] = new Reta(140,12550,50,12600,1,false);
    nretas++;
    retas[nretas] = new Reta(50,12600,50,13000,1,false);
    nretas++;
    retas[nretas] = new Reta(50,13000,100,13050,1,false);
    nretas++;
    retas[nretas] = new Reta(100,13050,100,14500,1,false);
    nretas++;
    retas[nretas] = new Reta(100,14500,50,14550,1,false);
    nretas++;
    retas[nretas] = new Reta(50,14550,50,14750,1,false);
    nretas++;
    retas[nretas] = new Reta(50,14750,140,14800,1,false);
    nretas++;
    retas[nretas] = new Reta(140,14800,140,14900,1,false);
    nretas++;
    retas[nretas] = new Reta(140,14900,160,14950,1,false);
    nretas++;
    retas[nretas] = new Reta(160,14950,160,17500,1,false);
    nretas++;
    retas[nretas] = new Reta(160,17500,50,17550,1,false);
    nretas++;
    retas[nretas] = new Reta(50,17550,50,18000,1,false);
    nretas++;



    //Lado Esquerdo
    retas[nretas] = new Reta(-50,0,-50,250,0,false);
    nretas++;
    retas[nretas] = new Reta(-50,250,-120,300,0,false);
    nretas++;
    retas[nretas] = new Reta(-120,300,-120,1800,0,false);
    nretas++;
    retas[nretas] = new Reta(-120,1800,-50,1850,0,false);
    nretas++;
    retas[nretas] = new Reta(-50,1850,-50,2100,0,false);
    nretas++;
    retas[nretas] = new Reta(-50,2100,-120,2150,0,false);
    nretas++;
    retas[nretas] = new Reta(-120,2150,-150,2200,0,false);
    nretas++;
    retas[nretas] = new Reta(-150,2200,-150,2250,0,false);
    nretas++;
    retas[nretas] = new Reta(-150,2250,-120,2300,0,false);
    nretas++;
    retas[nretas] = new Reta(-120,2300,-120,2500,0,false);
    nretas++;
    retas[nretas] = new Reta(-120,2500,-150,2550,0,false);
    nretas++;
    retas[nretas] = new Reta(-150,2550,-150,2650,0,false);
    nretas++;
    retas[nretas] = new Reta(-150,2650,-170,2700,0,false);
    nretas++;
    retas[nretas] = new Reta(-170,2700,-170,3400,0,false);
    nretas++;
    retas[nretas] = new Reta(-170,3400,-50,3450,0,false);
    nretas++;
    retas[nretas] = new Reta(-50,3450,-50,3750,0,false);
    nretas++;
    retas[nretas] = new Reta(-50,3750,-100,3800,0,false);
    nretas++;
    retas[nretas] = new Reta(-100,3800,-100,4000,0,false);
    nretas++;
    retas[nretas] = new Reta(-100,4000,-120,4050,0,false);
    nretas++;
    retas[nretas] = new Reta(-120,4050,-120,5000,0,false);
    nretas++;
    retas[nretas] = new Reta(-120,5000,-50,5050,0,false);
    nretas++;
    retas[nretas] = new Reta(-50,5050,-50,5300,0,false);
    nretas++;
    retas[nretas] = new Reta(-50,5300,-100,5301,0,false);
    nretas++;
    retas[nretas] = new Reta(-100,5301,-100,5350,0,false);
    nretas++;
    retas[nretas] = new Reta(-100,5350,-50,5400,0,false);
    nretas++;
    retas[nretas] = new Reta(-50,5400,-50,5550,0,false);
    nretas++;
    retas[nretas] = new Reta(-50,5550,-90,5600,0,false);
    nretas++;
    retas[nretas] = new Reta(-90,5600,-90,9000,0,false);
    nretas++;
    retas[nretas] = new Reta(-90,9000,-50,9050,0,false);
    nretas++;
    retas[nretas] = new Reta(-50,9050,-50,9400,0,false);
    nretas++;
    retas[nretas] = new Reta(-50,9400,-110,9450,0,false);
    nretas++;
    retas[nretas] = new Reta(-110,9450,-110,9500,0,false);
    nretas++;
    retas[nretas] = new Reta(-110,9500,-60,9550,0,false);
    nretas++;
    retas[nretas] = new Reta(-60,9550,-60,10000,0,false);
    nretas++;
    retas[nretas] = new Reta(-60,10000,-120,10050,0,false);
    nretas++;
    retas[nretas] = new Reta(-120,10050,-120,10200,0,false);
    nretas++;
    retas[nretas] = new Reta(-120,10200,-130,10201,0,false);
    nretas++;
    retas[nretas] = new Reta(-130,10201,-130,10400,0,false);
    nretas++;
    retas[nretas] = new Reta(-130,10400,-140,10401,0,false);
    nretas++;
    retas[nretas] = new Reta(-140,10401,-140,10600,0,false);
    nretas++;
    retas[nretas] = new Reta(-140,10600,-160,10650,0,false);
    nretas++;
    retas[nretas] = new Reta(-160,10650,-160,11400,0,false);
    nretas++;
    retas[nretas] = new Reta(-160,11400,-120,11450,0,false);
    nretas++;
    retas[nretas] = new Reta(-120,11450,-120,11650,0,false);
    nretas++;
    retas[nretas] = new Reta(-120,11650,-140,11700,0,false);
    nretas++;
    retas[nretas] = new Reta(-140,11700,-140,12550,0,false);
    nretas++;
    retas[nretas] = new Reta(-140,12550,-50,12600,0,false);
    nretas++;
    retas[nretas] = new Reta(-50,12600,-50,13000,0,false);
    nretas++;
    retas[nretas] = new Reta(-50,13000,-100,13050,0,false);
    nretas++;
    retas[nretas] = new Reta(-100,13050,-100,14500,0,false);
    nretas++;
    retas[nretas] = new Reta(-100,14500,-50,14550,0,false);
    nretas++;
    retas[nretas] = new Reta(-50,14550,-50,14750,0,false);
    nretas++;
    retas[nretas] = new Reta(-50,14750,-140,14800,0,false);
    nretas++;
    retas[nretas] = new Reta(-140,14800,-140,14900,0,false);
    nretas++;
    retas[nretas] = new Reta(-140,14900,-160,14950,0,false);
    nretas++;
    retas[nretas] = new Reta(-160,14950,-160,17500,0,false);
    nretas++;
    retas[nretas] = new Reta(-160,17500,-50,17550,0,false);
    nretas++;
    retas[nretas] = new Reta(-50,17550,-50,18000,0,false);
    nretas++;


    //Primeiro Poligono
    retas[nretas] = new Reta(-30,3000,-30,3300,1,true);
    nretas++;
    retas[nretas] = new Reta(-30,3300,30,3301,0,true);
    nretas++;
    retas[nretas] = new Reta(-30,3000,30,3001,0,true);
    nretas++;
    retas[nretas] = new Reta(30,3000,30,3300,0,true);
    nretas++;


    //Segundo Poligono

    retas[nretas] = new Reta (0,4100,-60,4200,1,true);
    nretas++;
    retas[nretas] = new Reta (-60,4200,-60,4400,1,true);
    nretas++;
    retas[nretas] = new Reta (-60,4400,-25,4500,1,true);
    nretas++;
    retas[nretas] = new Reta (-25,4500,-25,4700,1,true);
    nretas++;
    retas[nretas] = new Reta (-25,4700,0,4800,1,true);
    nretas++;
    retas[nretas] = new Reta (25,4700,0,4800,0,true);
    nretas++;
    retas[nretas] = new Reta (25,4500,25,4700,0,true);
    nretas++;
    retas[nretas] = new Reta (60,4400,25,4500,0,true);
    nretas++;
    retas[nretas] = new Reta (60,4200,60,4400,0,true);
    nretas++;
    retas[nretas] = new Reta(0,4100,60,4200,0,true);
    nretas++;

    //Terceiro Poligono
    retas[nretas] = new Reta(0,10700,-60,10750,1,true);
    nretas++;
    retas[nretas] = new Reta(-60,10750,-60,10950,1,true);
    nretas++;
    retas[nretas] = new Reta(-60,10950,-25,11050,1,true);
    nretas++;
    retas[nretas] = new Reta(-25,11050,-25,11250,1,true);
    nretas++;
    retas[nretas] = new Reta(-25,11250,0,11260,0,true);
    nretas++;
    retas[nretas] = new Reta(25,11250,0,11260,0,true);
    nretas++;
    retas[nretas] = new Reta(25,11050,25,11250,0,true);
    nretas++;
    retas[nretas] = new Reta(60,10950,25,11050,0,true);
    nretas++;
    retas[nretas] = new Reta(60,10750,60,10950,0,true);
    nretas++;
    retas[nretas] = new Reta(0,10700,60,10750,0,true);
    nretas++;

    //Quarto poligono
    retas[nretas] = new Reta(0,11800,-70,11850,1,true);
    nretas++;
    retas[nretas] = new Reta(-70,11850,-70,12150,1,true);
    nretas++;
    retas[nretas] = new Reta(-70,12150,-80,12151,1,true);
    nretas++;
    retas[nretas] = new Reta(-80,12151,-80,12300,1,true);
    nretas++;
    retas[nretas] = new Reta(-80,12300,0,12350,1,true);
    nretas++;
    retas[nretas] = new Reta(80,12300,0,12350,0,true);
    nretas++;
    retas[nretas] = new Reta(80,12150,80,12300,0,true);
    nretas++;
    retas[nretas] = new Reta(70,12150,80,12151,0,true);
    nretas++;
    retas[nretas] = new Reta(70,11850,70,12150,0,true);
    nretas++;
    retas[nretas] = new Reta(0,11800,70,11850,0,true);
    nretas++;

    //Quinto Poligono
    retas[nretas] = new Reta(0,15100,-100,15150,1,true);
    nretas++;
    retas[nretas] = new Reta(-100,15150,-100,15250,1,true);
    nretas++;
    retas[nretas] = new Reta(-100,15250,-80,15260,1,true);
    nretas++;
    retas[nretas] = new Reta(-80,15260,-80,15450,1,true);
    nretas++;
    retas[nretas] = new Reta(-80,15450,-100,15500,1,true);
    nretas++;
    retas[nretas] = new Reta(-100,15500,-100,15550,1,true);
    nretas++;
    retas[nretas] = new Reta(-100,15550,-70,15600,1,true);
    nretas++;
    retas[nretas] = new Reta(-70,15600,-70,15700,1,true);
    nretas++;
    retas[nretas] = new Reta(-70,15700,0,15750,1,true);
    nretas++;
    retas[nretas] = new Reta(70,15700,0,15750,0,true);
    nretas++;
    retas[nretas] = new Reta(70,15600,70,15700,0,true);
    nretas++;
    retas[nretas] = new Reta(100,15550,70,15600,0,true);
    nretas++;
    retas[nretas] = new Reta(100,15500,100,15550,0,true);
    nretas++;
    retas[nretas] = new Reta(70,15450,100,15500,0,true);
    nretas++;
    retas[nretas] = new Reta(80,15260,80,15450,0,true);
    nretas++;
    retas[nretas] = new Reta(100,15250,80,15260,0,true);
    nretas++;
    retas[nretas] = new Reta(100,15150,100,15250,0,true);
    nretas++;
    retas[nretas] = new Reta(0,15100,100,15150,0,true);
    nretas++;

    //Sexto Poligono
    retas[nretas] = new Reta(0,16500,-90,16550,1,true);
    nretas++;
    retas[nretas] = new Reta(-90,16550,-90,17050,1,true);
    nretas++;
    retas[nretas] = new Reta(-90,17050,0,17100,1,true);
    nretas++;
    retas[nretas] = new Reta(90,17050,0,17100,0,true);
    nretas++;
    retas[nretas] = new Reta(90,16550,90,17050,0,true);
    nretas++;
    retas[nretas] = new Reta(0,16500,90,16550,0,true);
    nretas++;


    RMD();


    glutMainLoop();

    return 0;

}

void init()
{
    glClearColor (1.0, 1.0, 1.0, 0.0);

   glShadeModel (GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);               // Habilita Z-buffer
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);                   // habilita luz 0
   glEnable(GL_NORMALIZE);



    glEnable(GL_ALPHA_TEST); // O alpha test descarta fragmentos dependendo de uma comparação (abaixo)
   glAlphaFunc(GL_GREATER, 0.5); // Info: https://www.opengl.org/sdk/docs/man2/xhtml/glAlphaFunc.xml

   glEnable(GL_BLEND);
   //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // https://www.opengl.org/sdk/docs/man/html/glBlendFunc.xhtml

   // Cor da fonte de luz (RGBA)
   GLfloat cor_luz[]     = { 1.0, 1.0, 1.0, 1.0};
   // Posicao da fonte de luz. Ultimo parametro define se a luz sera direcional (0.0) ou tera uma posicional (1.0)
   GLfloat posicao_luz[] = { 0.0, aviao->getY3() , 50.0, 1.0};

   // Define parametros da luz
   glLightfv(GL_LIGHT0, GL_AMBIENT, cor_luz);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, cor_luz);
   glLightfv(GL_LIGHT0, GL_SPECULAR, cor_luz);
   glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz);


   textureManager = new glcTexture();            // Criação do arquivo que irá gerenciar as texturas
   textureManager->SetNumberOfTextures(7);       // Estabelece o número de texturas que será utilizado
   textureManager->SetWrappingMode(GL_REPEAT);

   textureManager->CreateTexture("../data/ground.png", 0); // Para testar magnificação, usar a imagem marble128
   textureManager->CreateTexture("../data/ground5.png", 1); // Textura transparente, não sendo múltipla de zero
   textureManager->CreateTexture("../data/water.png", 2); // Textura transparente, não sendo múltipla de zero
   textureManager->CreateTexture("../data/capa.png", 3);
   textureManager->CreateTexture("../data/arcade.png", 4);
   textureManager->CreateTexture("../data/gas.png", 5);
   textureManager->CreateTexture("../data/gameover.png", 6);

   //textureManager->SetColorMode(GL_REPLACE);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity ();
}

void specialKeys(int key, int x, int y)
{
    switch(key) {

        case GLUT_KEY_F10:
            orthoview = !orthoview;
            break;
        case GLUT_KEY_LEFT:
            move_x = -2;
        break;
        case GLUT_KEY_RIGHT:
            move_x = 2;
        break;

        case GLUT_KEY_UP:
            velocidade = 2;
        break;

        case GLUT_KEY_DOWN:
            velocidade = -1.5;
        break;


    }
}

void inicializarInimigo()
{
    inimigos[0] = new Inimigo(0, 300);
    inimigos[1] = new Inimigo(-50, 500);
    inimigos[2] = new Inimigo(-70, 900);
    inimigos[3] = new Inimigo(-30, 1000);
    inimigos[4] = new Inimigo(70, 1200);
    inimigos[5] = new Inimigo(50, 1300);
    inimigos[6] = new Inimigo(30, 1350);
    inimigos[7] = new Inimigo(80, 1500);
    inimigos[8] = new Inimigo(-80, 1700);
    inimigos[9] = new Inimigo(0, 2100);
    inimigos[10] = new Inimigo(110, 2220);
    inimigos[11] = new Inimigo(100, 2350);
    inimigos[12] = new Inimigo(90, 2450);
    inimigos[13] = new Inimigo(-90, 2600);
    inimigos[14] = new Inimigo(-140, 2900);
    inimigos[15] = new Inimigo(-120, 3150);
    inimigos[16] = new Inimigo(120, 3200);
    inimigos[17] = new Inimigo(-130, 3350);
    inimigos[18] = new Inimigo(-20, 3500);
    inimigos[19] = new Inimigo(20, 3700);
    inimigos[20] = new Inimigo(-90, 4200);
    inimigos[21] = new Inimigo(90, 4750);
    inimigos[22] = new Inimigo(-30, 4800);
    inimigos[23] = new Inimigo(-30, 5450);
    inimigos[24] = new Inimigo(50, 5850);
    inimigos[25] = new Inimigo(50, 6000);
    inimigos[26] = new Inimigo(50, 6100);
    inimigos[27] = new Inimigo(0, 6500);
    inimigos[28] = new Inimigo(-20, 6700);
    inimigos[29] = new Inimigo(-10, 6800);
    inimigos[30] = new Inimigo(80, 6900);
    inimigos[31] = new Inimigo(-10, 7000);
    inimigos[32] = new Inimigo(80, 7500);
    inimigos[33] = new Inimigo(80, 7600);
    inimigos[34] = new Inimigo(-10, 8000);
    inimigos[35] = new Inimigo(-10, 8500);
    inimigos[35] = new Inimigo(-10, 8700);
    inimigos[36] = new Inimigo(0, 8900);
    inimigos[37] = new Inimigo(-10, 9900);
    inimigos[38] = new Inimigo(60, 10100);
    inimigos[39] = new Inimigo(-70, 10300);
    inimigos[40] = new Inimigo(-100, 10680);
    inimigos[41] = new Inimigo(100, 10680);
    inimigos[42] = new Inimigo(-100, 11300);
    inimigos[43] = new Inimigo(100, 12200);
    inimigos[44] = new Inimigo(0, 12650);
    inimigos[45] = new Inimigo(-20, 12900);
    inimigos[46] = new Inimigo(0, 13150);
    inimigos[47] = new Inimigo(50, 13200);
    inimigos[48] = new Inimigo(40, 13300);
    inimigos[49] = new Inimigo(-40, 13400);
    inimigos[50] = new Inimigo(0, 13600);
    inimigos[51] = new Inimigo(20, 13700);
    inimigos[52] = new Inimigo(60, 14200);
    inimigos[53] = new Inimigo(60, 14300);
    inimigos[54] = new Inimigo(-60, 14350);
    inimigos[55] = new Inimigo(0, 14600);
    inimigos[56] = new Inimigo(-120, 14820);
    inimigos[57] = new Inimigo(-120, 14870);
    inimigos[58] = new Inimigo(-130, 15000);
    inimigos[59] = new Inimigo(-130, 15300);
    inimigos[60] = new Inimigo(130, 15650);
    inimigos[61] = new Inimigo(-80, 16000);
    inimigos[62] = new Inimigo(80, 16100);
    inimigos[63] = new Inimigo(100, 16200);
    inimigos[64] = new Inimigo(-50, 16450);
    inimigos[65] = new Inimigo(50, 16400);
    inimigos[66] = new Inimigo(-145, 16900);
    inimigos[67] = new Inimigo(130, 17400);


    checkpoints[0] = new Inimigo (0,1900);
    checkpoints[0]->isCheckPoint = true;
    checkpoints[1] = new Inimigo (0,5150);
    checkpoints[1]->isCheckPoint = true;
    checkpoints[2] = new Inimigo (0,9150);
    checkpoints[2]->isCheckPoint = true;
    checkpoints[3] = new Inimigo (0,12900);
    checkpoints[3]->isCheckPoint = true;
    checkpoints[4] = new Inimigo (0,14600);
    checkpoints[4]->isCheckPoint = true;
    checkpoints[5] = new Inimigo (0,17800);
    checkpoints[5]->isCheckPoint = true;
}

void inicializarCombustiveis()
{
    combustiveis[0] = new Combustivel(50, 500);
    combustiveis[1] = new Combustivel(30, 600);
    combustiveis[2] = new Combustivel(80, 700);
    combustiveis[3] = new Combustivel(35, 900);
    combustiveis[4] = new Combustivel(-20, 1000);
    combustiveis[5] = new Combustivel(30, 1200);
    combustiveis[6] = new Combustivel(0, 1700);
    combustiveis[7] = new Combustivel(60, 2500);
    combustiveis[8] = new Combustivel(100, 3000);
    combustiveis[9] = new Combustivel(-50, 3200);
    combustiveis[10] = new Combustivel(-50, 3400);
    combustiveis[11] = new Combustivel(60, 3900);
    combustiveis[12] = new Combustivel(-60, 4100);
    combustiveis[13] = new Combustivel(90, 4500);
    combustiveis[14] = new Combustivel(80, 4800);
    combustiveis[15] = new Combustivel(40, 6000);
    combustiveis[16] = new Combustivel(-40, 6300);
    combustiveis[17] = new Combustivel(-10, 6600);
    combustiveis[18] = new Combustivel(30, 6900);
    combustiveis[19] = new Combustivel(0, 7200);
    combustiveis[20] = new Combustivel(-50, 7500);
    combustiveis[21] = new Combustivel(-10, 7800);
    combustiveis[22] = new Combustivel(40, 8100);
    combustiveis[23] = new Combustivel(0, 8400);
    combustiveis[24] = new Combustivel(-20, 8800);
    combustiveis[25] = new Combustivel(80, 9480);
    combustiveis[26] = new Combustivel(40, 9650);
    combustiveis[27] = new Combustivel(-80, 10500);
    combustiveis[28] = new Combustivel(80, 10700);
    combustiveis[29] = new Combustivel(-70, 11000);
    combustiveis[30] = new Combustivel(120, 11200);
    combustiveis[31] = new Combustivel(-80, 11500);
    combustiveis[32] = new Combustivel(-70, 11600);
    combustiveis[33] = new Combustivel(100, 12250);
    combustiveis[34] = new Combustivel(0, 13200);
    combustiveis[35] = new Combustivel(40, 13600);
    combustiveis[36] = new Combustivel(20, 14000);
    combustiveis[37] = new Combustivel(-30, 14400);
    combustiveis[38] = new Combustivel(120, 15000);
    combustiveis[39] = new Combustivel(-120, 15050);
    combustiveis[40] = new Combustivel(-80, 16000);
    combustiveis[41] = new Combustivel(-145, 16550);
    combustiveis[42] = new Combustivel(-145, 16600);
    combustiveis[43] = new Combustivel(-145, 16650);
}

void display()
{

        textureManager->SetColorMode(GL_REPLACE);
        textureManager->Update();

        float aspectRatio = textureManager->GetAspectRatio(1);

   // Calculo abaixo funciona apenas se textura estiver centralizada na origem
        float h = 1.0f;
        float w = 1.0f;

        if( aspectRatio > 1.0f) h  = h/aspectRatio;
        else                    w  = w*aspectRatio;

    if(gameState == 0)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glOrtho(-200, 200, orthoFirstY, orthoLastY, -100.0, 100.0);

        glClearColor (0.0, 0.0, 0.0, 0.0);
        textureManager->Bind(3);


        glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(-200,orthoFirstY,0);
        glTexCoord2f(1,0);
        glVertex3f(200,orthoFirstY,0);
        glTexCoord2f(1,1);
        glVertex3f(200,orthoLastY,0);
        glTexCoord2f(0,1);
        glVertex3f(-200,orthoLastY,0);
        glEnd();

        textureManager->Bind(5);
        glColor3f(1.0, 1.0, 0);
        imprimirTexto("RIVER RAID", -20, (orthoLastY + orthoFirstY)/2);
        imprimirTexto("Aperte espaco para comecar", -50, (orthoLastY + orthoFirstY)/2 - 20);
    }

    if (gameState == 1)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glMatrixMode (GL_PROJECTION);
        glLoadIdentity ();
        if(!orthoview)
            gluPerspective(45.0, (GLfloat)WINDOW_WIDTH/(GLfloat) WINDOW_HEIGHT, 1.0, 1000.0);
        else
            glOrtho(-200, 200, -100, 300, 1.0, 1000.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity ();
        if(!orthoview)
            gluLookAt (0.0, aviao->getY3()-170, 180.0, 0.0, aviao->getY3(), 50.0, 0.0, 1.0, 0.0);
        else
            gluLookAt (0.0, aviao->getY3(), 180.0, 0.0, aviao->getY3(), 0.0, 0.0, 1.0, 0.0);



        glClearColor (0.0, 0.0, 1.0, 0.0);
        //setMaterial6();
        //glColor3f(0.1, 1.0, 0.4);

        imprimirTexto(std::to_string(pontos).c_str(), 150, orthoLastY - 30);
        imprimirTexto(std::to_string(porcentagemCombustivel).c_str(), -180, orthoLastY - 30);
        imprimirTexto(std::to_string(vidas).c_str(), 0, orthoLastY - 30);

        //setMaterial3();
        glNormal3f(0,0,1);
        textureManager->Bind(1);


        //textureManager->SetColorMode(GL_MODULATE);
       // textureManager->Bind(0);


       /* for(int i=0; i<nretas;i++)
        {
            if(retas[i]->x1 < 0) glNormal3f(1,0,0);
            else glNormal3f(-1,0,0);
            glBegin(GL_QUADS);
            glTexCoord2f(0.0,0.0);
            glVertex3f(retas[i]->x1, retas[i]->y1, 0);
            glTexCoord2f(5.0,0.0);
            glVertex3f(retas[i]->x2, retas[i]->y2, 0);
            glTexCoord2f(5.0,1.0);
            glVertex3f(retas[i]->x2, retas[i]->y2, 41);
            glTexCoord2f(0.0,1.0);
            glVertex3f(retas[i]->x1, retas[i]->y1, 41);
            glEnd();
        }
        */

        setMaterial6();
       textureManager->SetColorMode(GL_MODULATE);
       textureManager->Update();

        Quad *quad;
        for(int i = 0; i < quads->size(); i++)
        {
            quad = quads->at(i);

            if(quad->y1 > orthoLastY+100 || quad->y1 < orthoFirstY-500) continue;

            if(quad->x1 >0 )
            w = abs(300 - abs(quad->x1)) / 250.0;
            else
            w = abs(300 - abs(quad->x2)) / 250.0;

            h = abs(quad->y1 - quad->y3) / 250.0;

                glNormal3f(quad->n1x,quad->n1y,quad->n1z);
                glBegin(GL_TRIANGLES);

                glTexCoord2f(0,0);
                glVertex3f(quad->x1,quad->y1,quad->z1);
                glTexCoord2f(w,0);
                glVertex3f(quad->x2,quad->y2,quad->z2);
                glTexCoord2f(0,h);
                glVertex3f(quad->x4,quad->y4,quad->z4);
                glEnd();

                glNormal3f(quad->n2x,quad->n2y,quad->n2z);
                glBegin(GL_TRIANGLES);


                glTexCoord2f(w,0);
                glVertex3f(quad->x2,quad->y2,quad->z2);
                glTexCoord2f(w,h);
                glVertex3f(quad->x3,quad->y3,quad->z3);
                glTexCoord2f(0,h);
                glVertex3f(quad->x4,quad->y4,quad->z4);
                glEnd();


        }

       textureManager->SetColorMode(GL_REPLACE);
       textureManager->Update();

        textureManager->Bind(2);

        aspectRatio = textureManager->GetAspectRatio(2);

   // Calculo abaixo funciona apenas se textura estiver centralizada na origem
         h = 7.0f;
         w = 7.0f;

        if( aspectRatio > 1.0f) h  = h/aspectRatio;
        else                    w  = w*aspectRatio;


        glBegin(GL_QUADS);

                glTexCoord2f(0.0,0.0);
                glVertex3f(-400, 0, -10);
                glTexCoord2f(h,0.0);
                glVertex3f(400, 0, -10);
                glTexCoord2f(h,w);
                glVertex3f(400, 20000, -10);
                glTexCoord2f(0.0,w);
                glVertex3f(-400, 20000, -10);
        glEnd();





        textureManager->Disable();
        translatex+=move_x;
        aviao->x1+=move_x;
        aviao->x2+=move_x;
        aviao->x3+=move_x;

        if(rotator>=-0.4 && rotator <=0.4)
            rotator+=rotation;

        setMaterial();
        glPushMatrix();
            glTranslatef(translatex,translatey,0.0);
            glScalef(13,13,13);
            glRotatef(180,rotator,0,1);
            aviao->desenhar();
        glPopMatrix();


        //Projetil
        for(int i=0; i<50; i++)
        if(projetil[i] != NULL)
        {
            glPushMatrix();
                glTranslatef(projetil[i]->x,projetil[i]->y,3);
                glScalef(0.6,1,1);
                glutSolidSphere(3,50,50);
            glPopMatrix();
        }

        setMaterial2();
        for(int i = 0; i < QUANTIDADE_INIMIGOS; i++) {
            if(inimigos[i]!=NULL)
                inimigos[i]->desenhar(enemy, orthoFirstY,orthoLastY+300);
        }

        setMaterial5();
        for(int i = 0; i < QUANTIDADE_CHECKPOINTS; i++) {
            if(checkpoints[i]!=NULL)
                checkpoints[i]->desenhar(enemy,orthoFirstY,orthoLastY+300);
        }

        textureManager->Bind(5);
        setMaterial4();
        for(int i = 0; i < QUANTIDADE_COMBUSTIVEL; i++) {
            if(combustiveis[i]!=NULL)
            {
                 combustiveis[i]->desenhar();
                 if(aviao->colideComCombustivel(combustiveis[i]) && porcentagemCombustivel<100) {
                   porcentagemCombustivel += 1;
             }
            }
        }

        glColor3f(0.0,0.0,0.0);


    }

    if (gameState == 2)
    {
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0,0,0,0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glOrtho(-200, 200, orthoFirstY, orthoLastY, -100.0, 100.0);

        textureManager->Bind(3);


        glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(-200,orthoFirstY,0);
        glTexCoord2f(1,0);
        glVertex3f(200,orthoFirstY,0);
        glTexCoord2f(1,1);
        glVertex3f(200,orthoLastY,0);
        glTexCoord2f(0,1);
        glVertex3f(-200,orthoLastY,0);
        glEnd();




        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        textureManager->Bind(5);
        imprimirTexto("JOGO PAUSADO", -20, (orthoLastY+orthoFirstY)/2);

    }

    if (gameState == 3)
    {

        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0,0,0,0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glOrtho(-200, 200, orthoFirstY, orthoLastY, -100.0, 100.0);

        textureManager->Bind(6);


        glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(-200,orthoFirstY,0);
        glTexCoord2f(1,0);
        glVertex3f(200,orthoFirstY,0);
        glTexCoord2f(1,1);
        glVertex3f(200,orthoLastY,0);
        glTexCoord2f(0,1);
        glVertex3f(-200,orthoLastY,0);
        glEnd();




        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

    }

    if (gameState == 4)
    {
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0, 0, 0, 0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glOrtho(-200, 200, orthoFirstY, orthoLastY, -100.0, 100.0);

        glClearColor (0.0, 0.0, 0.0, 0.0);
        textureManager->Bind(4);


        glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(-200,orthoFirstY,0);
        glTexCoord2f(1,0);
        glVertex3f(200,orthoFirstY,0);
        glTexCoord2f(1,1);
        glVertex3f(200,orthoLastY,0);
        glTexCoord2f(0,1);
        glVertex3f(-200,orthoLastY,0);
        glEnd();


        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        textureManager->Bind(5);
        glColor3f(1.0, 1.0, 1.0);
        imprimirTexto("PLACAR", -20, orthoLastY-20);
        for(int i=0; i<10; i++)
            imprimirTexto(std::to_string(placar[i]).c_str(), 0, orthoLastY - 20*(i+2));

    }

    glutSwapBuffers();
}

void imprimirTexto(char const *texto, int x, int y)
{
    int length = (int) strlen(texto);

    // Posição do texto na tela
    glRasterPos3f(x, y-250,70.0);

    for(int i = 0; i < length; i++)
    {
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
    float t,desiredFrameTime, frameTime;
    static float tLast = 0.0;

    // Get elapsed time and convert to s
    t = glutGet(GLUT_ELAPSED_TIME);

    // Convert to seconds
    t /= 1000.0;

    frameTime = t - tLast;

    desiredFrameTime = 1.0/60.0;

     if(frameTime <= desiredFrameTime)
        return;






    if(gameState == 1)
    {

        porcentagemCombustivel -= 0.05;

         if(porcentagemCombustivel <= 0) {

            reconfigurar();
        }

        // Verifica colisao AVIÃO-INIMIGOS
        for(int i = 0; i < QUANTIDADE_INIMIGOS ; i++)
        {
            if(inimigos[i]!=NULL)
            {

                if(inimigos[i]->colisaoN(aviao))
                {
                    reconfigurar();
                }
            }
        }


        // Verifica colisao AVIÃO-CHECKPOINTS
        for(int i = 0; i < QUANTIDADE_CHECKPOINTS ; i++)
        {
            if(checkpoints[i]!=NULL)
            {


                if(checkpoints[i]->colisaoN(aviao))
                {
                    reconfigurar();
                }
            }
        }






            //COLISAO PROJETIL-COMBUSTIVEL
            for(int i = 0; i <QUANTIDADE_COMBUSTIVEL; i++)
            {
                if(combustiveis[i]!=NULL)
                {
                  for(int j=0; j<50; j++)
                  {
                    if(projetil[j]!=NULL)
                    if(combustiveis[i]->colisaoP(projetil[j]->x,projetil[j]->y))
                    {
                        pontos++;
                        delete combustiveis[i];
                        combustiveis[i]=NULL;
                        delete projetil[j];
                        projetil[j] = NULL;
                        break;
                    }
                  }
                }
            }

            //Colisão PROJETIL - INIMIGOS
            for(int i = 0; i <QUANTIDADE_INIMIGOS ; i++)
            {
                if(inimigos[i]!=NULL)
                {
                  for(int j=0; j<50; j++)
                  {
                    if(projetil[j]!=NULL)
                    if(inimigos[i]->colisaoP(projetil[j]->x,projetil[j]->y))
                    {
                        pontos++;
                        delete inimigos[i];
                        inimigos[i]=NULL;
                        delete projetil[j];
                        projetil[j] = NULL;
                        break;
                    }
                  }
                }
            }

        //Colisão Projetil - Mapa
        if(projetil != NULL)
            for(int i = 0; i < nretas; i++)
            {
                for(int j=0; j<50; j++)
                {

                if(projetil[j]!=NULL)
                if(retas[i]->colisaoP(projetil[j]) == 1)
                {
                    delete projetil[j];
                    projetil[j] = NULL;
                    break;
                }

                }
            }

        //Colisão Projetil - Checkpoints
        if(projetil != NULL)
            for(int i= 0; i < QUANTIDADE_CHECKPOINTS; i++)
                {
                    if(checkpoints[i]!=NULL)
                    for(int j=0; j<50;j++)
                    {

                    if(projetil[j]!=NULL)
                    if (checkpoints[i]->colisaoP(projetil[j]->x,projetil[j]->y))
                    {
                        returny1 = returny2 = checkpoints[i]->getY();
                        returny3 = returny1 + 20;

                        delete checkpoints[i];
                        checkpoints[i] = NULL;
                        delete projetil[j];
                        projetil[j] = NULL;
                        break;


                    }
                    }
                }

        //Verifica colisão AVIÃO - MAPA
        for(int i = 0; i < nretas; i++)
        {
            if(retas[i]->colisao() == 1)
            {

                reconfigurar();
            }
        }


        /* Update velocity and position */

        if(orthoLastY < ORTHO_MAXIMO)
        {
            orthoLastY += 2 + velocidade;
            orthoFirstY += 2 + velocidade;
            translatey += 2 + velocidade;
            aviao->setComponente("y1", aviao->getY1() + 2 + velocidade);
            aviao->setComponente("y2", aviao->getY2() + 2 + velocidade);
            aviao->setComponente("y3", aviao->getY3() + 2 + velocidade);
        }

        else
        {
            vidas=0;
            reconfigurar();
        }

    for(int i=0; i<50; i++)
        if(projetil[i] != NULL)
        {
            projetil[i]->y += 10;
            if(projetil[i]->y > orthoLastY+200)
            {
                delete projetil[i];
                projetil[i] = NULL;
            }
        }

        for(int i = 1; i <= 8; i++) {
            if(inimigos[i] != NULL) {
                inimigos[i]->oscilar(-120, 120);
            }
        }

        if(inimigos[10] != NULL)
            inimigos[10]->oscilar(-150, 150);

        if(inimigos[11] != NULL)
            inimigos[11]->oscilar(-120, 120);

        if(inimigos[12] != NULL)
            inimigos[12]->oscilar(-120, 120);

        if(inimigos[13] != NULL)
            inimigos[13]->oscilar(-150, 150);

        if(inimigos[14] != NULL)
            inimigos[14]->oscilar(-170, 170);

        if(inimigos[15] != NULL)
            inimigos[15]->oscilar(-170, -30);

        if(inimigos[16] != NULL)
            inimigos[16]->oscilar(30, 170);

        if(inimigos[19] != NULL)
            inimigos[19]->oscilar(-50, 50);

        if(inimigos[22] != NULL)
            inimigos[22]->oscilar(-50, 50);

        if(inimigos[23] != NULL)
            inimigos[23]->oscilar(-50, 50);

        for(int i = 24; i <= 35; i++) {
            if(inimigos[i] != NULL) {
                inimigos[i]->oscilar(-90, 90);
            }
        }

        if(inimigos[36] != NULL)
            inimigos[36]->oscilar(-50, 50);

        if(inimigos[37] != NULL)
            inimigos[37]->oscilar(-60, 60);

        if(inimigos[43] != NULL)
            inimigos[43]->oscilar(80, 140);

        if(inimigos[44] != NULL)
            inimigos[44]->oscilar(-50, 50);

        if(inimigos[45] != NULL)
            inimigos[45]->oscilar(-50, 50);

        for(int i = 46; i <= 54; i++) {
            if(inimigos[i] != NULL) {
                inimigos[i]->oscilar(-100, 100);
            }
        }

        if(inimigos[56] != NULL)
            inimigos[56]->oscilar(-140, 140);

        if(inimigos[57] != NULL)
            inimigos[57]->oscilar(-140, 140);

        if(inimigos[59] != NULL)
            inimigos[59]->oscilar(-160, -110);

        if(inimigos[60] != NULL)
            inimigos[60]->oscilar(100, 160);

        for(int i = 61; i <= 67; i++) {
            if(inimigos[i] != NULL) {
                inimigos[i]->oscilar(-160, 160);
            }
        }
    }
    /* Update tLast for next time, using static local variable */
    tLast = t;

    /* Ask glut to schedule call to display function */
    glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'a':
            move_x= -2;
            rotation = -0.01;
       //     aviao->moverEsquerda();
        break;
        case 'd':
            move_x= 2;
            rotation = +0.01;
        //    aviao->moverDireita();
        break;

        case 'w':
            velocidade = 2;
        break;
        case 's':
            velocidade = -1.5;
        break;
		case 'm':
            if(!fullscreen)
            {
                fullscreen = true;
                glutFullScreen();
            }
            else
            {
                fullscreen = false;
                glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
            }
        break;
        case ' ':
            if(gameState == 1)
                if(i_projetil >= 50) i_projetil = 0;
                if(projetil[i_projetil]!= NULL) delete projetil[i_projetil];
                projetil[i_projetil] = new Projetil();
                i_projetil++;
            if(gameState == 0 || gameState == 3 || gameState == 4)
            {
                gameState = 1;
                vidas = 3;
                pontos = 0;
                orthoFirstY = 0;
                orthoLastY = 500;
                porcentagemCombustivel = 100;
            }
        break;
        case 'p':
            if(gameState == 1)
            {
                gameState = 2;
            }

            else if(gameState == 2)
            {
                gameState = 1;
            }
        break;
        case 'r':
            for(int i = 0; i < QUANTIDADE_INIMIGOS; i++)
            {
                if(inimigos[i]!=NULL)
                    delete inimigos[i];
            }
            inicializarInimigo();
            inicializarCombustiveis();
            for(int i=0; i<50;i++)
                        {
                            if(projetil[i]!=NULL) delete projetil[i];
                            projetil[i] = NULL;
                        }
            aviao->setComponente("x1", -8);
            aviao->setComponente("y1", 20);
            aviao->setComponente("x2", 8);
            aviao->setComponente("y2", 20);
            aviao->setComponente("x3", 0);
            aviao->setComponente("y3", 40);
            returny1 = aviao->getY1();
            returny2 = aviao->getY2();
            returny3 = aviao->getY3();
            gameState = 1;
            vidas = 3;
            pontos = 0;
            orthoFirstY = 0;
            orthoLastY = 500;
            porcentagemCombustivel = 100;
            translatex = 0.0;
            translatey = aviao->getY3();
        break;

        case '2':
             oldState = gameState;
            if(gameState==0 || gameState==3)
            {
                gameState=4;
            }
           else if(gameState==4)
            {

                gameState=oldState;

            }
        break;

		case 27:
		    for(int i = 0; i < QUANTIDADE_INIMIGOS; i++)
                delete inimigos[i];
            delete [] inimigos;
            file.close();
            exit(0);
        break;
    }
}



void reconfigurar()
{
                    vidas--;
                    aviao->setComponente("x1", -8);
                    aviao->setComponente("y1", returny1);
                    aviao->setComponente("x2", 8);
                    aviao->setComponente("y2", returny2);
                    aviao->setComponente("x3", 0);
                    aviao->setComponente("y3", returny3);
                    orthoFirstY = returny1 - 20;
                    orthoLastY  = returny1 + 480;
                    porcentagemCombustivel = 100;
                    translatex = 0.0;
                    translatey = aviao->getY3();

                    if(vidas <= 0)
                    {
                        gameState = 3;
                        porcentagemCombustivel = 100;
                        for(int i = 0; i < QUANTIDADE_INIMIGOS; i++)
                        {
                            if(inimigos[i]!=NULL)
                                delete inimigos[i];
                        }
                        inicializarInimigo();
                        inicializarCombustiveis();

                        for(int i=0; i<50;i++)
                        {
                            if(projetil[i]!=NULL) delete projetil[i];
                            projetil[i] = NULL;
                        }
                        aviao->setComponente("x1", -8);
                        aviao->setComponente("y1", 20);
                        aviao->setComponente("x2", 8);
                        aviao->setComponente("y2", 20);
                        aviao->setComponente("x3", 0);
                        aviao->setComponente("y3", 40);
                        returny1 = aviao->getY1();
                        returny2 = aviao->getY2();
                        returny3 = aviao->getY3();
                        translatex = 0.0;
                        translatey = aviao->getY3();

                        placar[10] = pontos;
                        ordena(placar,11);
                        for(int i=0; i<10; i++)
                        {
                            file<<placar[i]<<'\n';
                        }

                        file.clear();
                        file.seekg(0, std::ios::beg);
                    }
}


void ordena (int v[], int tam)
{
    int aux;
    for(int i=0; i<tam; i++)
        for(int j=0; j<tam; j++)
            if(v[j] < v[i])
                {
                    aux = v[j];
                    v[j] = v[i];
                    v[i] = aux;
                }


}
