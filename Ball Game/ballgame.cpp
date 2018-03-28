/*
  Name:        quad_color
  Copyright:   Version 0.1
  Author:      Rodrigo Luis de Souza da Silva
  Last Update: 03/09/2014
  Release:     28/10/2004
  Description: Colored quad.
*/

/*#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <iostream>
double mainX=350,mainY=400, mRadius=30;     //Coordenadas iniciais e tamanho da esfera principal
int nballs = 100;           //Numero de bolas a ser gerado pelo programa
int pontos = 0;
int vidas = 3;
int pressed = 0;             //Verifica se houve um click dentro da esfera
double lastx,lasty;         //coordenadas do ultimo clique para movimentação do mouse
double planx, plany, planz; //coordenadas do ponto central do plano





class Ball
{
public:

    Ball(double cx,double cy,double rad)
    {
        x=cx;
        y=cy;
        radius=rad;
    }
    double x,y,radius;
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


void display(void);
void init (void);
void keyboard(unsigned char key, int x, int y);
void idle();
void mouse(int button, int state, int x, int y);
void motion(int x, int y );


int main(int argc, char** argv)
{
    srand (time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH);
    glutInitWindowSize (700, 700);
    glutCreateWindow ("Game");
    init ();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    //Criando as bolas
    balls = new Ball*[nballs];
    for(int i=0; i< nballs; i++)
    {
        balls[i] = new Ball(rand()%700 + 1, rand()% 100 + 600,rand()%10 + 10);
    }


    glutMainLoop();

    return 0;
}

// É a rotina chamada automaticamente sempre que a
// janela ou parte dela precisa ser redesenhada


void idle()
{

    int state=0;
    for(int i=0; i < nballs; i++)
    {
        state = balls[i]->colisao();
        balls[i]->y -= 3;
        if(state == 1)
        {

            pontos++;
            delete balls[i];
            balls[i] = balls[nballs-1];
            nballs--;
            i--;
        }
        else if (state == 2)
        {
            vidas--;
            delete balls[i];
            balls[i] = balls[nballs-1];
            nballs--;
            i--;
        }



    }

    glutPostRedisplay();

}

void display(void)
{
    // Limpar todos os pixels
    glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);



    glColor3f(1,1,1);

    //Plano y=20;
    glPushMatrix();
    glTranslatef(350,20,0);
    glScalef(700.0, 1.0, 1.0);
    glutSolidCube(1);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(mainX,mainY,0);

    glutSolidSphere(mRadius,100,100);
    glPopMatrix();

    glColor3f(1.0,0,0);



    for(int i=0; i< nballs; i++)
    {
        glPushMatrix();
        glTranslatef(balls[i]->x,balls[i]->y,0);

        glutSolidSphere(balls[i]->radius,100,100);
        glPopMatrix();

    }




    glutSwapBuffers ();
    glutPostRedisplay();

}

void init (void)
{
    // selecionar cor de fundo (preto)
    glClearColor (0.0, 0.0, 0.0, 0.0);
                 // Habilita Z-buffer

    // inicializar sistema de viz.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 700, 0, 700, -30.0, 30.0);

    glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
    glLoadIdentity();           // Inicializa com matriz identidade

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
    // Inverte mouse para que origem fique no canto inferior esquerdo da janela
    // (por default, a origem é no canto superior esquerdo)


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
    // Inverte mouse para que origem fique no canto inferior esquerdo da janela
    // (por default, a origem é no canto superior esquerdo)
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
*/
