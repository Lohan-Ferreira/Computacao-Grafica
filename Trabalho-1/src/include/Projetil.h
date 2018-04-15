#ifndef PROJETIL_H
#define PROJETIL_H

class Projetil
{
    public:
        Projetil(double x, double y);
        ~Projetil();
        double getX();
        double getY();
        void setX(double x);
        void setY(double y);
    private:
        double x;
        double y;
};

#endif // PROJETIL_H
