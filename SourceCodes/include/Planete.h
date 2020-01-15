#ifndef PLANETE_H
#define PLANETE_H

#include <string>
#include "Coordonnees.h"
class Planete
{
    public:
        Coordonnees Coor;
        Planete();
        Planete(std:: string  Name,Coordonnees Coor ,double SpeedRot,double SpeedRotS,double DistS,double Radius,double Red, double Green, double Blue);
        Planete(std:: string Name,Coordonnees CoorInit ,Coordonnees CoorFinal, double SpeedRot, double Radius,double Red, double Green, double Blue);
        virtual ~Planete();
        void DrawPlanete(float angleS, float angle);
        double getRadius();
        void setPas(Coordonnees coor);
    protected:

    private:
        std::string Name;

        double SpeedRot;  // vitesse de rotation Sur lui meme
        double SpeedRotS;  // vitesse de rotation Sur le soleil
        double DistS; //distance du soleil
        double Radius;
        double Red;
        double Green;
        double Blue;
        Coordonnees Pas;
};

#endif // PLANETE_H
