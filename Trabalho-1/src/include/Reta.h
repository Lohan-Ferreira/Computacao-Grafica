#ifndef RETA_H
#define RETA_H


class Reta
{
    public:
        Reta(double px1, double py1, double px2, double py2, int s, bool vx);
        ~Reta();
        int colisao();
    private:
        double x1, x2, y1,y2;               // Coordenadas
        double VO[2];                       // Vetor Ortogonal
        double PI;                          // Pré calculo para comparações rapidas (Produto Interno)
        int side;                           // Verifica qual o lado da colisão ( 0 direita da reta , 1 esquerda da reta)
        bool verificaX;                     // Flag caso verificação de eixo X seja necessária
        int dx;                             // Distancia no eixo X entre os pontos
};

#endif // RETA_H
