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

#define WINDOW_WIDTH  900
#define WINDOW_HEIGHT 600
#define QUANTIDADE_CHECKPOINTS 6

#define QUANTIDADE_INIMIGOS 68
#define QUANTIDADE_COMBUSTIVEL 43

#define ORTHO_MAXIMO 18000

Aviao *aviao = new Aviao();

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

Projetil *projetil;

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

    int colisaoP()
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



int returny1 = aviao->getY1(),returny2 = aviao->getY2(), returny3 = aviao->getY3();

Reta **retas;
Inimigo **inimigos;
Inimigo **checkpoints;
int nretas = 0;
double orthoFirstY = 0;
double orthoLastY = 500;
bool fullscreen = false;
int gameState = 0; // Estados do jogo 0 tela inicial, 1 jogando, 2 pausado, 3 fim de jogo
int vidas = 3;
int pontos = 0;
float porcentagemCombustivel = 100;
Combustivel *combustiveis[QUANTIDADE_COMBUSTIVEL];


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




int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("River Raid");
    init();
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
    retas[nretas] = new Reta(-30,3300,30,3301,1,true);
    nretas++;
    retas[nretas] = new Reta(-30,3000,30,3001,1,true);
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
    retas[nretas] = new Reta(0,15100,-130,15150,1,true);
    nretas++;
    retas[nretas] = new Reta(-130,15150,-130,15250,1,true);
    nretas++;
    retas[nretas] = new Reta(-130,15250,-110,15260,1,true);
    nretas++;
    retas[nretas] = new Reta(-110,15260,-110,15450,1,true);
    nretas++;
    retas[nretas] = new Reta(-110,15450,-130,15500,1,true);
    nretas++;
    retas[nretas] = new Reta(-130,15500,-130,15550,1,true);
    nretas++;
    retas[nretas] = new Reta(-130,15550,-100,15600,1,true);
    nretas++;
    retas[nretas] = new Reta(-100,15600,-100,15700,1,true);
    nretas++;
    retas[nretas] = new Reta(-100,15700,0,15750,1,true);
    nretas++;
    retas[nretas] = new Reta(100,15700,0,15750,0,true);
    nretas++;
    retas[nretas] = new Reta(100,15600,100,15700,0,true);
    nretas++;
    retas[nretas] = new Reta(130,15550,100,15600,0,true);
    nretas++;
    retas[nretas] = new Reta(130,15500,130,15550,0,true);
    nretas++;
    retas[nretas] = new Reta(110,15450,130,15500,0,true);
    nretas++;
    retas[nretas] = new Reta(110,15260,110,15450,0,true);
    nretas++;
    retas[nretas] = new Reta(130,15250,110,15260,0,true);
    nretas++;
    retas[nretas] = new Reta(130,15150,130,15250,0,true);
    nretas++;
    retas[nretas] = new Reta(0,15100,130,15150,0,true);
    nretas++;

    //Sexto Poligono
    retas[nretas] = new Reta(0,16500,-130,16550,1,true);
    nretas++;
    retas[nretas] = new Reta(-130,16550,-130,17050,1,true);
    nretas++;
    retas[nretas] = new Reta(-130,17050,0,17100,1,true);
    nretas++;
    retas[nretas] = new Reta(130,17050,0,17100,0,true);
    nretas++;
    retas[nretas] = new Reta(130,16550,130,17050,0,true);
    nretas++;
    retas[nretas] = new Reta(0,16500,130,16550,0,true);
    nretas++;


    glutMainLoop();

    return 0;

}

void init()
{
    glClearColor (0.0, 0.0, 1.0, 0.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity ();
}

void specialKeys(int key, int x, int y)
{
    switch(key) {
        case GLUT_KEY_LEFT:
            aviao->moverEsquerda();
        break;
        case GLUT_KEY_RIGHT:
            aviao->moverDireita();
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
    if(gameState == 0)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glOrtho(-200, 200, orthoFirstY, orthoLastY, -1.0, 1.0);

        glClearColor (0.0, 0.0, 0.0, 0.0);

        glColor3f(1.0, 1.0, 0);
        imprimirTexto("RIVER RAID", -20, (orthoLastY + orthoFirstY)/2);
        imprimirTexto("Aperte espaco para comecar", -50, (orthoLastY + orthoFirstY)/2 - 20);
    }

    if (gameState == 1)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glOrtho(-200, 200, orthoFirstY, orthoLastY, -1.0, 1.0);
        glClearColor (0.0, 0.0, 1.0, 0.0);
        glColor3f(0.1, 1.0, 0.4);

        glBegin(GL_TRIANGLE_STRIP);
            glVertex3f(50,  0.0,   0);
            glVertex3f(200, 0.0,   0);
            glVertex3f(50,  250,   0);
            glVertex3f(200, 250,   0);
            glVertex3f(120, 300,   0);
            glVertex3f(200, 300,   0);
            glVertex3f(120, 1800,  0);
            glVertex3f(200, 1800,  0);
            glVertex3f(50,  1850,  0);
            glVertex3f(200, 1850,  0);
            glVertex3f(50,  2100,  0);
            glVertex3f(200, 2100,  0);
            glVertex3f(120, 2150,  0);
            glVertex3f(200, 2150,  0);
            glVertex3f(150, 2200,  0);
            glVertex3f(200, 2200,  0);
            glVertex3f(150, 2250,  0);
            glVertex3f(200, 2250,  0);
            glVertex3f(120, 2300,  0);
            glVertex3f(200, 2300,  0);
            glVertex3f(120, 2500,  0);
            glVertex3f(200, 2500,  0);
            glVertex3f(150, 2550,  0);
            glVertex3f(200, 2550,  0);
            glVertex3f(150, 2650,  0);
            glVertex3f(200, 2650,  0);
            glVertex3f(170, 2700,  0);
            glVertex3f(200, 2700,  0);
            glVertex3f(170, 3400,  0);
            glVertex3f(200, 3400,  0);
            glVertex3f(50,  3450,  0);
            glVertex3f(200, 3450,  0);
            glVertex3f(50,  3750,  0);
            glVertex3f(200, 3750,  0);
            glVertex3f(100, 3800,  0);
            glVertex3f(200, 3800,  0);
            glVertex3f(100, 4000,  0);
            glVertex3f(200, 4000,  0);
            glVertex3f(120, 4050,  0);
            glVertex3f(200, 4050,  0);
            glVertex3f(120, 5000,  0);
            glVertex3f(200, 5000,  0);
            glVertex3f(50,  5050,  0);
            glVertex3f(200, 5050,  0);
            glVertex3f(50,  5300,  0);
            glVertex3f(200, 5300,  0);
            glVertex3f(100, 5300,  0);
            glVertex3f(200, 5300,  0);
            glVertex3f(100, 5350,  0);
            glVertex3f(200, 5350,  0);
            glVertex3f(50,  5400,  0);
            glVertex3f(200, 5400,  0);
            glVertex3f(50,  5550,  0);
            glVertex3f(200, 5550,  0);
            glVertex3f(90,  5600,  0);
            glVertex3f(200, 5600,  0);
            glVertex3f(90,  9000,  0);
            glVertex3f(200, 9000,  0);
            glVertex3f(50,  9050,  0);
            glVertex3f(200, 9050,  0);
            glVertex3f(50,  9400,  0);
            glVertex3f(200, 9400,  0);
            glVertex3f(110, 9450,  0);
            glVertex3f(200, 9450,  0);
            glVertex3f(110, 9500,  0);
            glVertex3f(200, 9500,  0);
            glVertex3f(60,  9550,  0);
            glVertex3f(200, 9550,  0);
            glVertex3f(60,  10000, 0);
            glVertex3f(200, 10000, 0);
            glVertex3f(120, 10050, 0);
            glVertex3f(200, 10050, 0);
            glVertex3f(120, 10200, 0);
            glVertex3f(200, 10200, 0);
            glVertex3f(130, 10200, 0);
            glVertex3f(200, 10200, 0);
            glVertex3f(130, 10400, 0);
            glVertex3f(200, 10400, 0);
            glVertex3f(140, 10400, 0);
            glVertex3f(200, 10400, 0);
            glVertex3f(140, 10600, 0);
            glVertex3f(200, 10600, 0);
            glVertex3f(160, 10650, 0);
            glVertex3f(200, 10650, 0);
            glVertex3f(160, 11400, 0);
            glVertex3f(200, 11400, 0);
            glVertex3f(120, 11450, 0);
            glVertex3f(200, 11450, 0);
            glVertex3f(120, 11650, 0);
            glVertex3f(200, 11650, 0);
            glVertex3f(140, 11700, 0);
            glVertex3f(200, 11700, 0);
            glVertex3f(140, 12550, 0);
            glVertex3f(200, 12550, 0);
            glVertex3f(50,  12600, 0);
            glVertex3f(200, 12600, 0);
            glVertex3f(50,  13000, 0);
            glVertex3f(200, 13000, 0);
            glVertex3f(100, 13050, 0);
            glVertex3f(200, 13050, 0);
            glVertex3f(100, 14500, 0);
            glVertex3f(200, 14500, 0);
            glVertex3f(50,  14550, 0);
            glVertex3f(200, 14550, 0);
            glVertex3f(50,  14750, 0);
            glVertex3f(200, 14750, 0);
            glVertex3f(140, 14800, 0);
            glVertex3f(200, 14800, 0);
            glVertex3f(140, 14900, 0);
            glVertex3f(200, 14900, 0);
            glVertex3f(160, 14950, 0);
            glVertex3f(200, 14950, 0);
            glVertex3f(160, 17500, 0);
            glVertex3f(200, 17500, 0);
            glVertex3f(50,  17550, 0);
            glVertex3f(200, 17550, 0);
            glVertex3f(50,  18000, 0);
            glVertex3f(200, 18000, 0);
        glEnd();

        glBegin(GL_TRIANGLE_STRIP);
            glVertex3f(-50,  0.0,   0);
            glVertex3f(-200, 0.0,   0);
            glVertex3f(-50,  250,   0);
            glVertex3f(-200, 250,   0);
            glVertex3f(-120, 300,   0);
            glVertex3f(-200, 300,   0);
            glVertex3f(-120, 1800,  0);
            glVertex3f(-200, 1800,  0);
            glVertex3f(-50,  1850,  0);
            glVertex3f(-200, 1850,  0);
            glVertex3f(-50,  2100,  0);
            glVertex3f(-200, 2100,  0);
            glVertex3f(-120, 2150,  0);
            glVertex3f(-200, 2150,  0);
            glVertex3f(-150, 2200,  0);
            glVertex3f(-200, 2200,  0);
            glVertex3f(-150, 2250,  0);
            glVertex3f(-200, 2250,  0);
            glVertex3f(-120, 2300,  0);
            glVertex3f(-200, 2300,  0);
            glVertex3f(-120, 2500,  0);
            glVertex3f(-200, 2500,  0);
            glVertex3f(-150, 2550,  0);
            glVertex3f(-200, 2550,  0);
            glVertex3f(-150, 2650,  0);
            glVertex3f(-200, 2650,  0);
            glVertex3f(-170, 2700,  0);
            glVertex3f(-200, 2700,  0);
            glVertex3f(-170, 3400,  0);
            glVertex3f(-200, 3400,  0);
            glVertex3f(-50,  3450,  0);
            glVertex3f(-200, 3450,  0);
            glVertex3f(-50,  3750,  0);
            glVertex3f(-200, 3750,  0);
            glVertex3f(-100, 3800,  0);
            glVertex3f(-200, 3800,  0);
            glVertex3f(-100, 4000,  0);
            glVertex3f(-200, 4000,  0);
            glVertex3f(-120, 4050,  0);
            glVertex3f(-200, 4050,  0);
            glVertex3f(-120, 5000,  0);
            glVertex3f(-200, 5000,  0);
            glVertex3f(-50,  5050,  0);
            glVertex3f(-200, 5050,  0);
            glVertex3f(-50,  5300,  0);
            glVertex3f(-200, 5300,  0);
            glVertex3f(-100, 5300,  0);
            glVertex3f(-200, 5300,  0);
            glVertex3f(-100, 5350,  0);
            glVertex3f(-200, 5350,  0);
            glVertex3f(-50,  5400,  0);
            glVertex3f(-200, 5400,  0);
            glVertex3f(-50,  5550,  0);
            glVertex3f(-200, 5550,  0);
            glVertex3f(-90,  5600,  0);
            glVertex3f(-200, 5600,  0);
            glVertex3f(-90,  9000,  0);
            glVertex3f(-200, 9000,  0);
            glVertex3f(-50,  9050,  0);
            glVertex3f(-200, 9050,  0);
            glVertex3f(-50,  9400,  0);
            glVertex3f(-200, 9400,  0);
            glVertex3f(-110, 9450,  0);
            glVertex3f(-200, 9450,  0);
            glVertex3f(-110, 9500,  0);
            glVertex3f(-200, 9500,  0);
            glVertex3f(-60,  9550,  0);
            glVertex3f(-200, 9550,  0);
            glVertex3f(-60,  10000, 0);
            glVertex3f(-200, 10000, 0);
            glVertex3f(-120, 10050, 0);
            glVertex3f(-200, 10050, 0);
            glVertex3f(-120, 10200, 0);
            glVertex3f(-200, 10200, 0);
            glVertex3f(-130, 10200, 0);
            glVertex3f(-200, 10200, 0);
            glVertex3f(-130, 10400, 0);
            glVertex3f(-200, 10400, 0);
            glVertex3f(-140, 10400, 0);
            glVertex3f(-200, 10400, 0);
            glVertex3f(-140, 10600, 0);
            glVertex3f(-200, 10600, 0);
            glVertex3f(-160, 10650, 0);
            glVertex3f(-200, 10650, 0);
            glVertex3f(-160, 11000, 0);
            glVertex3f(-200, 11000, 0);
            glVertex3f(-160, 11400, 0);
            glVertex3f(-200, 11400, 0);
            glVertex3f(-120, 11450, 0);
            glVertex3f(-200, 11450, 0);
            glVertex3f(-120, 11650, 0);
            glVertex3f(-200, 11650, 0);
            glVertex3f(-140, 11700, 0);
            glVertex3f(-200, 11700, 0);
            glVertex3f(-140, 12550, 0);
            glVertex3f(-200, 12550, 0);
            glVertex3f(-50,  12600, 0);
            glVertex3f(-200, 12600, 0);
            glVertex3f(-50,  13000, 0);
            glVertex3f(-200, 13000, 0);
            glVertex3f(-100, 13050, 0);
            glVertex3f(-200, 13050, 0);
            glVertex3f(-100, 14500, 0);
            glVertex3f(-200, 14500, 0);
            glVertex3f(-50,  14550, 0);
            glVertex3f(-200, 14550, 0);
            glVertex3f(-50,  14750, 0);
            glVertex3f(-200, 14750, 0);
            glVertex3f(-140, 14800, 0);
            glVertex3f(-200, 14800, 0);
            glVertex3f(-140, 14900, 0);
            glVertex3f(-200, 14900, 0);
            glVertex3f(-160, 14950, 0);
            glVertex3f(-200, 14950, 0);
            glVertex3f(-160, 17500, 0);
            glVertex3f(-200, 17500, 0);
            glVertex3f(-50,  17550, 0);
            glVertex3f(-200, 17550, 0);
            glVertex3f(-50,  18000, 0);
            glVertex3f(-200, 18000, 0);
        glEnd();

        // Primeiro obstaculo que fica dentro da parte azul
        glBegin(GL_POLYGON);
            glVertex3f(-30, 3000, 0);
            glVertex3f(-30, 3300, 0);
            glVertex3f(30, 3300,  0);
            glVertex3f(30, 3000,  0);
        glEnd();

        // Segundo obstaculo que fica dentro da parte azul
        glBegin(GL_POLYGON);
            glVertex3f(0,4100, 0);
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

        // Terceiro obstaculo que fica dentro da parte azul
        glBegin(GL_POLYGON);
            glVertex3f(0.0, 36000, 0);
            glVertex3f(-60, 35500, 0);
            glVertex3f(-60, 34500, 0);
            glVertex3f(-90, 34000, 0);
            glVertex3f(-90, 33500, 0);
            glVertex3f(-60, 33000, 0);
            glVertex3f(-60, 32500, 0);
            glVertex3f(-90, 32000, 0);
            glVertex3f(-90, 30000, 0);
            glVertex3f(90, 30000, 0);
            glVertex3f(90, 32000, 0);
            glVertex3f(60, 32500, 0);
            glVertex3f(60, 33000, 0);
            glVertex3f(90, 33500, 0);
            glVertex3f(90, 34000, 0);
            glVertex3f(60, 34500, 0);
            glVertex3f(60, 35500, 0);
        glEnd();

        // Quarto obstaculo que fica dentro da parte azul
        glBegin(GL_POLYGON);
            glVertex3f(0, 10700, 0);
            glVertex3f(-60, 10750, 0);
            glVertex3f(-60, 10950, 0);
            glVertex3f(-25, 11050, 0);
            glVertex3f(-25, 11250, 0);
            glVertex3f(0, 11260, 0);
            glVertex3f(25, 11250, 0);
            glVertex3f(25, 11050, 0);
            glVertex3f(60, 10950, 0);
            glVertex3f(60, 10750, 0);
        glEnd();

        // Quinto obstaculo que fica dentro da parte azul
        glBegin(GL_POLYGON);
            glVertex3f(0, 11800, 0);
            glVertex3f(-70, 11850, 0);
            glVertex3f(-70, 12150, 0);
            glVertex3f(-80, 12150, 0);
            glVertex3f(-80, 12300, 0);
            glVertex3f(0, 12350, 0);
            glVertex3f(80, 12300, 0);
            glVertex3f(80, 12150, 0);
            glVertex3f(70, 12150, 0);
            glVertex3f(70, 11850, 0);
        glEnd();

        // Sexto obstaculo que fica dentro da parte azul
        glBegin(GL_POLYGON);
            glVertex3f(0, 15100, 0);
            glVertex3f(-130, 15150, 0);
            glVertex3f(-130, 15250, 0);
            glVertex3f(-110, 15260, 0);
            glVertex3f(-110, 15450, 0);
            glVertex3f(-130, 15500, 0);
            glVertex3f(-130, 15550, 0);
            glVertex3f(-100, 15600, 0);
            glVertex3f(-100, 15700, 0);
            glVertex3f(0.0, 15750, 0);
            glVertex3f(100, 15700, 0);
            glVertex3f(100, 15600, 0);
            glVertex3f(130, 15550, 0);
            glVertex3f(130, 15500, 0);
            glVertex3f(110, 15450, 0);
            glVertex3f(110, 15260, 0);
            glVertex3f(130, 15250, 0);
            glVertex3f(130, 15150, 0);
        glEnd();

        // Setimo obstaculo que fica dentro da parte azul
        glBegin(GL_POLYGON);
            glVertex3f(0, 16500, 0);
            glVertex3f(-130, 16550, 0);
            glVertex3f(-130, 17050, 0);
            glVertex3f(0, 17100, 0);
            glVertex3f(130, 17050, 0);
            glVertex3f(130, 16550, 0);
        glEnd();


        aviao->desenhar();


        //Projetil
        if(projetil != NULL)
        {
            glPushMatrix();
                glTranslatef(projetil->x,projetil->y,3);
                glScalef(0.6,1,1);
                glutSolidSphere(3,50,50);
            glPopMatrix();
        }

        for(int i = 0; i < QUANTIDADE_INIMIGOS; i++) {
            if(inimigos[i]!=NULL)
                inimigos[i]->desenhar();
        }

        for(int i = 0; i < QUANTIDADE_CHECKPOINTS; i++) {
            if(checkpoints[i]!=NULL)
                checkpoints[i]->desenhar();
        }

        for(int i = 0; i < QUANTIDADE_COMBUSTIVEL; i++) {
            combustiveis[i]->desenhar();
             if(aviao->colideComCombustivel(combustiveis[i])) {
               porcentagemCombustivel += 1;
             }
        }

        glColor3f(0.0,0.0,0.0);
        imprimirTexto(std::to_string(pontos).c_str(), 150, orthoLastY - 30);
        imprimirTexto(std::to_string(porcentagemCombustivel).c_str(), -180, orthoLastY - 30);
        imprimirTexto(std::to_string(vidas).c_str(), 0, orthoLastY - 30);
    }

    if (gameState == 2)
    {
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0,0,0,0);
        glColor3f(1.0,0.0,0.0);
        imprimirTexto("JOGO PAUSADO", -20, (orthoLastY+orthoFirstY)/2);
    }

    if (gameState == 3)
    {
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0, 0, 0, 0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glOrtho(-200, 200, orthoFirstY, orthoLastY, -1.0, 1.0);


        glColor3f(1.0, 0.0, 0.0);
        imprimirTexto("FIM DE JOGO", -20, (orthoFirstY + orthoLastY)/2);
    }

    glutSwapBuffers();
}

void imprimirTexto(char const *texto, int x, int y)
{
    int length = (int) strlen(texto);

    // Posição do texto na tela
    glRasterPos3f(x, y, 0.0);

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






        //Colisão PROJETIL - INIMIGOS
        if(projetil != NULL)
            for(int i = 0; i <QUANTIDADE_INIMIGOS ; i++)
            {
                if(inimigos[i]!=NULL)
                {


                    if(inimigos[i]->colisaoP(projetil->x,projetil->y))
                    {
                        pontos++;
                        delete inimigos[i];
                        inimigos[i]=NULL;
                        delete projetil;
                        projetil = NULL;
                        break;
                    }
                }
            }

        //Colisão Projetil - Mapa
        if(projetil != NULL)
            for(int i = 0; i < nretas; i++)
            {
                if(retas[i]->colisaoP() == 1)
                {
                    delete projetil;
                    projetil = NULL;
                    break;
                }
            }

        //Colisão Projetil - Checkpoints
        if(projetil != NULL)
            for(int i= 0; i < QUANTIDADE_CHECKPOINTS; i++)
                {
                    if(checkpoints[i]!=NULL)
                    if (checkpoints[i]->colisaoP(projetil->x,projetil->y))
                    {
                        returny1 = returny2 = checkpoints[i]->getY();
                        returny3 = returny1 + 20;

                        delete checkpoints[i];
                        checkpoints[i] = NULL;
                        delete projetil;
                        projetil = NULL;
                        break;


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
            orthoLastY += 2;
            orthoFirstY += 2;
            aviao->setComponente("y1", aviao->getY1() + 2);
            aviao->setComponente("y2", aviao->getY2() + 2);
            aviao->setComponente("y3", aviao->getY3() + 2);
        }

        else
        {
            gameState=3;
            reconfigurar();
        }


        if(projetil != NULL)
        {
            projetil->y += 10;
            if(projetil->y > orthoLastY)
            {
                delete projetil;
                projetil = NULL;
            }
        }

        inimigos[1]->oscilar(-120, 120);
        inimigos[2]->oscilar(-120, 120);
        inimigos[3]->oscilar(-120, 120);
        inimigos[4]->oscilar(-120, 120);
        inimigos[5]->oscilar(-120, 120);
        inimigos[6]->oscilar(-120, 120);
        inimigos[7]->oscilar(-120, 120);
        inimigos[8]->oscilar(-120, 120);
        inimigos[10]->oscilar(-150, 150);
        inimigos[11]->oscilar(-120, 120);
        inimigos[12]->oscilar(-120, 120);
        inimigos[13]->oscilar(-150, 150);
        inimigos[14]->oscilar(-170, 170);
        inimigos[15]->oscilar(-170, -30);
        inimigos[16]->oscilar(30, 170);
        inimigos[19]->oscilar(-50, 50);
        inimigos[22]->oscilar(-50, 50);
        inimigos[23]->oscilar(-50, 50);
        inimigos[24]->oscilar(-90, 90);
        inimigos[25]->oscilar(-90, 90);
        inimigos[26]->oscilar(-90, 90);
        inimigos[27]->oscilar(-90, 90);
        inimigos[28]->oscilar(-90, 90);
        inimigos[29]->oscilar(-90, 90);
        inimigos[30]->oscilar(-90, 90);
        inimigos[31]->oscilar(-90, 90);
        inimigos[32]->oscilar(-90, 90);
        inimigos[33]->oscilar(-90, 90);
        inimigos[34]->oscilar(-90, 90);
        inimigos[35]->oscilar(-90, 90);
        inimigos[36]->oscilar(-50, 50);
        inimigos[37]->oscilar(-60, 60);
        inimigos[43]->oscilar(80, 140);
        inimigos[44]->oscilar(-50, 50);
        inimigos[45]->oscilar(-50, 50);
        inimigos[46]->oscilar(-100, 100);
        inimigos[47]->oscilar(-100, 100);
        inimigos[48]->oscilar(-100, 100);
        inimigos[49]->oscilar(-100, 100);
        inimigos[50]->oscilar(-100, 100);
        inimigos[51]->oscilar(-100, 100);
        inimigos[52]->oscilar(-100, 100);
        inimigos[53]->oscilar(-100, 100);
        inimigos[54]->oscilar(-100, 100);
        inimigos[56]->oscilar(-140, 140);
        inimigos[57]->oscilar(-140, 140);
        inimigos[59]->oscilar(-160, -110);
        inimigos[60]->oscilar(100, 160);
        inimigos[61]->oscilar(-160, 160);
        inimigos[62]->oscilar(-160, 160);
        inimigos[63]->oscilar(-160, 160);
        inimigos[64]->oscilar(-160, 160);
        inimigos[65]->oscilar(-160, 160);
        inimigos[67]->oscilar(-160, 160);
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
            aviao->moverEsquerda();
        break;
        case 'd':
            aviao->moverDireita();
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
            if(projetil == NULL && gameState == 1)
                projetil = new Projetil();
            if(gameState == 0 || gameState == 3)
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
            projetil = NULL;
            aviao->setComponente("x1", -8);
            aviao->setComponente("y1", 20);
            aviao->setComponente("x2", 8);
            aviao->setComponente("y2", 20);
            aviao->setComponente("x3", 0);
            aviao->setComponente("y3", 40);
            returny1 = aviao->getY1();
            returny2 = aviao->getY2();
            returny3 = aviao->getY3();
            gameState = 0;
            vidas = 3;
            pontos = 0;
            orthoFirstY = 0;
            orthoLastY = 500;
            porcentagemCombustivel = 100;
        break;
		case 27:
		    for(int i = 0; i < QUANTIDADE_INIMIGOS; i++)
                delete inimigos[i];
            delete [] inimigos;
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
                        projetil = NULL;
                        aviao->setComponente("x1", -8);
                        aviao->setComponente("y1", 20);
                        aviao->setComponente("x2", 8);
                        aviao->setComponente("y2", 20);
                        aviao->setComponente("x3", 0);
                        aviao->setComponente("y3", 40);
                        returny1 = aviao->getY1();
                        returny2 = aviao->getY2();
                        returny3 = aviao->getY3();
                    }
}
