#ifndef PONTO_H
#define PONTO_H


class Ponto
{
    public:
        Ponto(float x, float y, float z);
        virtual ~Ponto();
        float getX();
        float getY();
        float getZ();
    private:
        float x;
        float y;
        float z;
};

#endif // PONTO_H
