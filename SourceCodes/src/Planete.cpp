#include "Planete.h"
#include <windows.h>
#include <GL/glut.h>
#include <string>
#include <iostream>
#include <math.h>

using namespace std;

Planete::Planete(){
}

Planete::Planete(std:: string Name,Coordonnees Coor ,double SpeedRot,double SpeedRotS,double DistS,double Radius,double Red, double Green, double Blue){
    this->Name = Name;
	this->Coor = Coor;
	this->Red = Red;
	this->Green = Green;
	this->Blue = Blue;
	this->SpeedRot = SpeedRot;
	this->SpeedRotS = SpeedRotS;
	this->DistS = DistS;
	this->Radius = Radius;
	this->Pas = Coordonnees(0,0,0);
   // cout << "youpi .......  "<< DistS <<endl;
}

void Planete::setPas(Coordonnees coor){
    this->Pas = coor;
}

Planete::Planete(std:: string Name,Coordonnees CoorInit ,Coordonnees CoorFinal ,double SpeedRot, double Radius,double Red, double Green, double Blue){
    this->Name = Name;
	this->Coor = CoorInit;
	this->Red = Red;
	this->Green = Green;
	this->Blue = Blue;
	this->SpeedRot = SpeedRot;
	this->SpeedRotS = SpeedRotS;
	this->Radius = Radius;
	this->DistS = sqrt(pow(Coor.getPosX(),2)+pow(Coor.getPosY(),2)+pow(Coor.getPosZ(),2));
	this->Pas = Coordonnees((CoorInit.getPosX()-CoorFinal.getPosX())/100,(CoorInit.getPosY()-CoorFinal.getPosY())/100,(CoorInit.getPosZ()-CoorFinal.getPosZ())/100);

}


Planete::~Planete(){
    //dtor
}


void Planete::DrawPlanete(float angle, float angleS){
    /*** Planete ***/
    //angleAutourSoleil-=(float)360 / (float)2332800 * Const;
    glColor3d(Red, Green, Blue);
    glPushMatrix();
    glRotated(angleS,0,0,1);
        glPushMatrix();
        angle+=01;
       Coor.setPosX(Coor.getPosX()-Pas.getPosX());
       Coor.setPosY(Coor.getPosY()-Pas.getPosY());
       Coor.setPosZ(Coor.getPosZ()-Pas.getPosZ());
        glTranslated(Coor.getPosX(),Coor.getPosY(),Coor.getPosZ());

        glRotated(angle,0,0,1);
        glutSolidSphere(Radius,20,20);
        glPopMatrix();
    glPopMatrix();
}

double Planete::getRadius(){
    return Radius;
}
