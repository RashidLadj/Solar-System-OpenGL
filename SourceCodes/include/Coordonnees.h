#ifndef COORDONNEES_H
#define COORDONNEES_H


class Coordonnees
{
    public:
        Coordonnees();
        Coordonnees(double PosX ,double PosY ,double PosZ);
        virtual ~Coordonnees();
        void Translate(double DX ,double DY ,double DZ);
        double getPosX();
        double getPosY();
        double getPosZ();
        void setPosX(double PosX);
        void setPosY(double PosY);
        void setPosZ(double PosZ);

    protected:

    private:
        double PosX;
        double PosY;
        double PosZ;
};

#endif // COORDONNEES_H
