/*
 * Autores: Diego Paiva e Lohan Ferreira
 * Data de criação: 07/04/2018
 * Descrição: Trabalho 1 - River Raid
 *
 */

#include <GL/glut.h>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include "Inimigo.h"

#define WINDOW_WIDTH  900
#define WINDOW_HEIGHT 600

#define QUANTIDADE_INIMIGOS 68

#define ORTHO_MAXIMO 18000

#define WINDOW_HEIGHT 600

double navex1 = -8, navey1 = 20, navex2 = 8, navey2 = 20, navex3 = 0, navey3 = 40;

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

        if (navey1 >= y1 && navey1 <= y2 )
         {

                int PI2 = navex1 * VO[0] + navey1 * VO[1];

                if(side)
                {

                    if (PI2 <= PI)
                    {
                        if(verificaX )
                        {
                            if(abs(navex1-x1) <= dx+0.5 && abs(navex1-x2) <= dx+0.5)
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
                            if(abs(navex1-x1) <= dx+0.5 && abs(navex1-x2) <= dx+0.5)
                                return 1;
                        }

                        else return 1;

                    }
                }



        }


         if (navey2 >= y1 && navey2 <= y2)
        {

                int PI2 = navex2 * VO[0] + navey2 * VO[1];

                if(side)
                {
                    if (PI2 <= PI)
                    {
                        if(verificaX )
                        {
                            if(abs(navex2-x1) <= dx+0.5 && abs(navex2-x2) <= dx+0.5)
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
                            if(abs(navex2-x1) <= dx+0.5 && abs(navex2-x2) <= dx+0.5)
                                return 1;
                        }

                        else return 1;

                    }
                }

        }


         if (navey3 >= y1 && navey3 <= y2)
        {

                int PI2 = navex3 * VO[0] + navey3 * VO[1];

                if(side)
                {
                    if (PI2 <= PI)
                    {
                        if(verificaX )
                        {
                            if(abs(navex3-x1) <= dx+0.5 && abs(navex3-x2) <= dx+0.5)
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
                            if(abs(navex3-x1) <= dx+0.5 && abs(navex3-x2) <= dx+0.5)
                                return 1;
                        }

                        else return 1;

                    }
                }

        }

        return 0;
    }

};

Reta** retas;
Inimigo *inimigos[QUANTIDADE_INIMIGOS];
int nretas = 0;
void init();
void inicializarInimigo();
void display();
void imprimirTexto(char const *texto, int x, int y);
void mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);
void idle();
void motion(int x, int y);
double orthoFirstY = 0;
double orthoLastY = 500;

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("River Raid");
    init();
    srand(time(NULL));
    inicializarInimigo();
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    retas = new Reta* [400];

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



    glutMainLoop();

    return 0;

}

void init()
{
    glClearColor (0.0, 0.0, 1.0, 0.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity ();
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
    inimigos[9] = new Inimigo(0, 1900);
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
    inimigos[22] = new Inimigo(-30, 5100);
    inimigos[23] = new Inimigo(-30, 5200);
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
    inimigos[36] = new Inimigo(0, 9100);
    inimigos[37] = new Inimigo(-10, 9800);
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
}

void display()
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();

    glOrtho(-200, 200, orthoFirstY, orthoLastY, -1.0, 1.0);

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

    // Aeronave
    glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_TRIANGLES) ;
        glVertex3f(navex1, navey1, 0);
        glVertex3f(navex2, navey2, 0);
        glVertex3f(navex3, navey3, 0);
    glEnd();

    for(int i = 0; i < QUANTIDADE_INIMIGOS; i++) {
        inimigos[i]->desenhar();
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
    float t, dt;
    static float tLast = 0.0;

    /* Get elapsed time and convert to s */
    t = glutGet(GLUT_ELAPSED_TIME);

    t /= 1000.0;

    /* Calculate delta t */
    dt = t - tLast;
    for(int i = 0; i<nretas; i++)
    {


        if(retas[i]->colisao()== 1)
            {

                navex1 = -80; navex2 = -64; navex3 = -72;
            }

    }

    /* Update velocity and position */

    if(orthoLastY < ORTHO_MAXIMO)
    {
        orthoLastY += 1;
        orthoFirstY += 1;
        navey1 += 1;
        navey2 += 1;
        navey3 += 1;
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
            navex1 -= 5;
            navex2 -= 5;
            navex3 -= 5;
        break;
        case 'd':
            navex1 += 5;
            navex2 += 5;
            navex3 += 5;
        break;

        case 'w':
            navey1 += 5;
            navey2 += 5;
            navey3 += 5;
        break;
    }
}
