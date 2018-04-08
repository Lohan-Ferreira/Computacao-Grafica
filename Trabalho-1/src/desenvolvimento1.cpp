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


double navex1 = -8  ,navey1 = 20 ,navex2 = 8 ,navey2 = 20 ,navex3 = 0,navey3 = 40;


class Reta
{

public:
    double x1,x2,y1,y2;                                     //Coordenadas
    double VO[2];                                           //Vetor Ortogonal
    double PI;                                              //Pré calculo para comparações rapidas (Produto Interno)
    int side;                                               //Verifica qual o lado da colisão ( 0 direita da reta , 1 esquerda da reta)
    bool verificaX;                                          //Flag caso verificação de eixo X seja necessária
    int dx;                                                  //Distancia no eixo X entre os pontos
    Reta(double px1,double py1,double px2,double py2, int s, bool vx)
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
        VO[1] = (x2 - x1);

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
int nretas = 0;
void init();
void display();
void imprimirTexto(char const *texto, int x, int y);
void mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);
void idle();
void motion(int x, int y);
double orthoFirstY = 000;
double orthoLastY = 850;

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("River Raid");
    glutKeyboardFunc(keyboard);
    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);


       retas = new Reta* [400];

    retas[nretas] = new Reta(80,0,80,300,1,false);
    nretas++;

     retas[nretas] = new Reta(80,300,120,500,1,false);
    nretas++;

     retas[nretas] = new Reta(120,500,120,1000,1,false);
    nretas++;

     retas[nretas] = new Reta(120,1000,80,1200,1,false);
    nretas++;




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


     glColor3f(1,1,1);

    glBegin(GL_TRIANGLES);
    glVertex3f(navex1,  navey1,    0);
    glVertex3f(navex2, navey2,    0);
    glVertex3f(navex3,  navey3,  0);
    glEnd();

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

    // 15000 = ortho maximo y
    if(orthoLastY < 15000)
    {
        orthoLastY+=0.2;
        orthoFirstY+=0.2;
        navey1+=0.2;
        navey2+=0.2;
        navey3+=0.2d;

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
        navex1 -= 3;
        navex2 -= 3;
        navex3 -= 3;
        break;
    case 'd':
        navex1 += 3;
        navex2 += 3;
        navex3 += 3;
        break;

    case'w':
        navey1+=3;
        navey2+=3;
        navey3+=3;
        break;
    }
}




