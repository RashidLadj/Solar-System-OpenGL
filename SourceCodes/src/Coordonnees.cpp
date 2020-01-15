#include "Coordonnees.h"
#include <math.h>
Coordonnees::Coordonnees(){
    //ctor
}

Coordonnees::Coordonnees(double PosX ,double PosY ,double PosZ){
    this->PosX = PosX;
	this->PosY = PosY;
	this->PosZ = PosZ;
	//ctor
}

Coordonnees::~Coordonnees(){
    //dtor
}

void Coordonnees::Translate(double DX ,double DY ,double DZ){
    this->PosX += DX;
	this->PosY += DY;
	this->PosZ += DZ;
}

double Coordonnees::getPosX(){
    return PosX;
}

double Coordonnees::getPosY(){
    return PosY;
}

double Coordonnees::getPosZ(){
    return PosZ;
}

void Coordonnees::setPosX(double PosX){
    this->PosX = PosX;
}

void Coordonnees::setPosY(double PosY){
    this->PosY = PosY;
}

void Coordonnees::setPosZ(double PosZ){
    this->PosZ = PosZ;
}

