#include <iostream>
#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include "Planete.h"
#include "Coordonnees.h"

#define _USE_MATH_DEFINES /** Pour le PI **/
#include <cmath>          /** Pour le PI **/

#include <vector>

#include <GL/freeglut.h>

/********* Debut Methodes ***********/
    void MainProject();
    void displayProject();
    static void reshapeProject(int width,int height);
    static void idle(void);
    void keyboardProject (unsigned char key, int xmouse, int ymouse);
    void keyboardSpecialProject (int key, int xmouse, int ymouse);
    void MouseFunc (int button, int state, int x, int y);
    void MouseMotion (int mouseX, int mouseY);
    void MouseWheel(int wheel, int direction, int x, int y);

    void timer(int);
    void CreatePlanetes();
    void DrawPlanete(float angleS, float angle, float distS, float Radius);
    void DrawOrbite(float r);
    void CreateComete();
    bool detecteCollision(Planete *Planetes, Planete Comete);
    double CalcDist (Coordonnees A, Coordonnees B);

/*********  Fin  Methodes ***********/


/******** Debut Variables Globales  **********/
    const int Const = 5000;
    bool Motion = false;
    /** Planetes **/
    Planete *Planetes = new Planete[9];
    std::vector< Planete > PlaneteCom;

                              /**   Soleil  , Mercure, Venus   , Terre   , Mars    , Jupiter  , Saturne  , Uranus    , Neptune    **/
    const float DistSoleil[9]    = {0       , 2      , 3       , 4       , 5.5     , 7        , 10       , 13        , 17         };
    const float Rotation[9]      = {0       , 5097600, 20995200, 86400   , 88596   , 35388    , 36828    , 25320     , 65520      };
    const float RotationS[9]     = {2332800 , 7603200, 19353600, 31536000, 59356800, 374328000, 929597472, 2651218560, 5206982400 };
    const float Radius[9]        = {1.5     , 0.15   , 0.18    , 0.2     , 0.15    , 0.5      , 0.15     , 0.35      , 0.35       };
          float AngleSoitMeme[9] = {0       , 0      , 0       , 0       , 0       , 0        , 0        , 0         , 0          };
          float AngleSurSoleil[9]= {0       , 0      , 0       , 0       , 0       , 0        , 0        , 0         , 0          };
    /** Variables de GlLookAt (Camera)  **/
    float p_camx = -40.0, p_camy = -20.0, p_camz = 50.0, cible_camx = 0.0, cible_camy = 0.0, cible_camz = 0.0, v1 = 0.0, v2 = 1.0, v3 = 0.0;
    float rotateX = 0,rotateY = 0,rotateZ = 0;
    float speed = 1;
    int PlaneteChoisi = -1;
    int oldMouseX = -1, oldMouseY = -1;
    int newMouseX = -1, newMouseY = -1;

    float rotateMouseX = 0,rotateMouseY = 0,rotateMouseZ = 0;
/********  Fin  Variables Globales  **********/


using namespace std;

int main(){
    MainProject();
    return 0;
}

/****** Project ******/
void MainProject(){
    CreatePlanetes();
    glutInitDisplayMode(GLUT_DEPTH);
    glutInitWindowSize(800,800);
    glutInitWindowPosition(400,0);
    glutCreateWindow("OpenGL Project");
    glutReshapeFunc(reshapeProject);            /** ReShape **/
    glutDisplayFunc(displayProject);            /** Display **/
    glutKeyboardFunc(keyboardProject);          /** KeyBoard **/
    glutSpecialFunc(keyboardSpecialProject);    /** KeyBoard Special **/
    glutMouseFunc(MouseFunc);                   /** Camera Mouse **/
    glutMotionFunc(MouseMotion);                /** Camera Mouse **/
  //  glutMouseWheelFunc(MouseWheel);
    glEnable(GL_DEPTH_TEST);
    glEnable( GL_TEXTURE_2D );
//    LoadGLTextures();
    glutMainLoop();
}

/** Creation des planetes **/
void CreatePlanetes(){
   // Planetes = new Planete[9];
    Planete Soleil ("Soleil" , Coordonnees(-DistSoleil[0],0,0), Rotation[0], RotationS[0], DistSoleil[0], Radius[0], 1.0, 0.6, 0.0);    Planetes[0] = Soleil;
	Planete Mercure("Mercure", Coordonnees(-DistSoleil[1],0,0), Rotation[1], RotationS[1], DistSoleil[1], Radius[1], 0.5, 0.4, 0.4);    Planetes[1] = Mercure;
	Planete Venus  ("Venus"  , Coordonnees(-DistSoleil[2],0,0), Rotation[2], RotationS[2], DistSoleil[2], Radius[2], 0.6, 0.6, 0.2);    Planetes[2] = Venus;
	Planete Terre  ("Terre"  , Coordonnees(-DistSoleil[3],0,0), Rotation[3], RotationS[3], DistSoleil[3], Radius[3], 0.0, 0.0, 0.7);    Planetes[3] = Terre;
	Planete Mars   ("Mars"   , Coordonnees(-DistSoleil[4],0,0), Rotation[4], RotationS[4], DistSoleil[4], Radius[4], 1.0, 0.2, 0.0);    Planetes[4] = Mars;
	Planete Jupiter("Jupiter", Coordonnees(-DistSoleil[5],0,0), Rotation[5], RotationS[5], DistSoleil[5], Radius[5], 0.8, 0.6, 0.3);    Planetes[5] = Jupiter;
	Planete Saturne("Saturne", Coordonnees(-DistSoleil[6],0,0), Rotation[6], RotationS[6], DistSoleil[6], Radius[6], 0.9, 0.8, 0.3);    Planetes[6] = Saturne;
	Planete Uranus ("Uranus" , Coordonnees(-DistSoleil[7],0,0), Rotation[7], RotationS[7], DistSoleil[7], Radius[7], 0.4, 0.4, 1.0);    Planetes[7] = Uranus;
	Planete Neptune("Neptune", Coordonnees(-DistSoleil[8],0,0), Rotation[8], RotationS[8], DistSoleil[8], Radius[8], 0.0, 0.0, 0.5);    Planetes[8] = Neptune;
}

static void reshapeProject(int width,int height){
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,(double)320/320,0.1,1040);
    gluLookAt( p_camx, p_camy, p_camz, cible_camx, cible_camy, cible_camz, v1, v2, v3);
    glutTimerFunc(1000.0/2.0, timer, 0);
}

void displayProject(){
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glRotatef(rotateMouseX,1,0,0);
    glRotatef(rotateMouseY,0,1,0);
    glRotatef(rotateMouseZ,0,0,1);
    /*glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();                       // On initialise la matrice de vue avec la matrice identité.
    gluPerspective(45,(double)320/320,0.1,1040);
    gluLookAt( p_camx, p_camy, p_camz, cible_camx, cible_camy, cible_camz, v1, v2, v3);*/
    /*** Soleil ***/
        AngleSoitMeme[0] -=(float)360 / (float)2332800 * Const;
        Planetes[0].DrawPlanete(AngleSoitMeme[0],0);

    /*** Mercure ***/
        AngleSoitMeme[1] += (float)360 / (float)5097600 * Const;
        AngleSurSoleil[1] += (float)360 / (float)7603200 * Const;
        Planetes[1].DrawPlanete(AngleSoitMeme[1], AngleSurSoleil[1]);
        DrawOrbite(DistSoleil[1]);

    /*** Venus ***/
        AngleSoitMeme[2] += (float)360 / (float)20995200 * Const;
        AngleSurSoleil[2] += (float)360 / (float)19353600 * Const;
        DrawOrbite(DistSoleil[2]);
        Planetes[2].DrawPlanete(AngleSoitMeme[2], AngleSurSoleil[2]);

    /*** Terre ***/
        AngleSoitMeme[3] += (float)360 / (float)86400 * Const;
         AngleSurSoleil[3] += (float)360 / (float)31536000 * Const;
        DrawOrbite(DistSoleil[3]);
        Planetes[3].DrawPlanete(AngleSoitMeme[3], AngleSurSoleil[3]);

    /*** Mars ***/
        AngleSoitMeme[4] += (float)360 / (float)88596 * Const;
        AngleSurSoleil[4] += (float)360 / (float)59356800 * Const;
        DrawOrbite(DistSoleil[4]);
        Planetes[4].DrawPlanete(AngleSoitMeme[4], AngleSurSoleil[4]);

    /*** Jupiter ***/
        AngleSoitMeme[5] += (float)360 / (float)35388 * Const;
         AngleSurSoleil[5] += (float)360 / (float)374328000 * Const;
        DrawOrbite(DistSoleil[5]);
        Planetes[5].DrawPlanete(AngleSoitMeme[5], AngleSurSoleil[5]);

    /*** Saturne ***/
        AngleSoitMeme[6] += (float)360 / (float)36828 * Const;
        AngleSurSoleil[6] += (float)360 / (float)929597472 * Const;
        DrawOrbite(DistSoleil[6]);
        Planetes[6].DrawPlanete(AngleSoitMeme[6], AngleSurSoleil[6]);

    /*** Uranus ***/
        AngleSoitMeme[7] += (float)360 / (float)25320 * Const;
        AngleSurSoleil[7] += (float)360 / (float)2651218560 * Const;
        DrawOrbite(DistSoleil[7]);
        Planetes[7].DrawPlanete(AngleSoitMeme[7], AngleSurSoleil[7]);

    /*** Neptune ***/
        AngleSoitMeme[8] += (float)360 / (float)65520 * Const;
        AngleSurSoleil[8] += (float)360 / (float)5206982400 * Const;
        DrawOrbite(DistSoleil[8]);
        Planetes[8].DrawPlanete(AngleSoitMeme[8], AngleSurSoleil[8]);

        for (int i = 0 ; i< PlaneteCom.size(); i++){
            PlaneteCom.at(i).DrawPlanete(1.2,0);
            if (detecteCollision(Planetes,PlaneteCom.at(i))){
                PlaneteCom.erase(PlaneteCom.begin() + i);
                i--;
            }
        }
    glFlush();
}

void timer(int){
    /* update animation */
    glPopMatrix();      /** Restore Etat Sauvgardé des transformations **/
    glPushMatrix();     /** Re-Sauvgarder l'état Etat Sauvgardé des transformations **/
	if (PlaneteChoisi != -1){
        p_camx = -DistSoleil[PlaneteChoisi]*cos(AngleSurSoleil[PlaneteChoisi] * M_PI / 180.0);
        p_camy = -DistSoleil[PlaneteChoisi]*sin(AngleSurSoleil[PlaneteChoisi] * M_PI / 180.0);
        cible_camx = p_camx;
        cible_camy = p_camy;
	}
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,(double)320/320,0.1,1040);
    gluLookAt( p_camx, p_camy, p_camz, cible_camx, cible_camy, cible_camz, v1, v2, v3);
    glRotatef( rotateX, 1.0f, 0, 0 );
    glRotatef( rotateY, 0, 1.0f, 0 );
    glRotatef( rotateZ, 0, 0, 1.0f );
    glutPostRedisplay();
    glutTimerFunc(1000.0/60.0, timer, 0);
}

void DrawOrbite(float r){
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    int num_segments = 500;
    glBegin(GL_LINE_LOOP);
    for(int ii = 0; ii < num_segments; ii++){
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component
        glVertex2f(x,y);//output vertex
    }
    glEnd();
}

void keyboardProject (unsigned char key, int xmouse, int ymouse){
    glPopMatrix();      /** Restore Etat Sauvgardé des transformations **/
    glPushMatrix();     /** Re-Sauvgarder l'état Etat Sauvgardé des transformations **/
	switch (key){
		case '+':   /** Zoom Camera (Z) **/
            p_camz--;
            break;

        case '-':   /** DeZoom Cemera (Z) **/
            p_camz++;
            break;

        case 'i':   /** Etat Initial Camera **/
            p_camx = 0.0, p_camy = 0.0, p_camz = 50.0, cible_camx = 0.0, cible_camy = 0.0, cible_camz = 0.0, v1 = 0.0, v2 = 1.0, v3 = 0.0;
            rotateX = 0 ; rotateY = 0 ; rotateZ = 0 ;
            rotateMouseX = 0 ; rotateMouseY = 0 ; rotateMouseZ = 0 ;
            break;

        case 'u':   /** RotateY Positif **/
	       rotateY+=speed;
	       cout << rotateY << endl;
           break;

		case 't':    /** RotateY Negatif **/
	       rotateY-=speed;
           break;

        case 'e':   /** RotateZ Positif **/
	       rotateZ+=speed;
	       cout << rotateY << endl;
           break;

		case 'a':    /** RotateZ Negatif **/
	       rotateZ-=speed;
           break;

        case 'c':   /** RotateX Positif **/
	       rotateX+=speed;
	       cout << rotateY << endl;
           break;

		case 'w':    /** RotateX Negatif **/
	      // glPushMatrix();
	       rotateX-=speed;
           break;

        case '0':   /** Soleil **/
           PlaneteChoisi = 0;
           break;

		case '1':   /** Mercure **/
           PlaneteChoisi = 1;
           break;

        case '2':   /** Venus **/
            PlaneteChoisi = 2;
           break;

		case '3':   /** Terre **/
		    PlaneteChoisi = 3;
            break;

        case '4':   /** Mars **/
		    PlaneteChoisi = 4;
            break;

        case '5':   /** Jupiter **/
		    PlaneteChoisi = 5;
            break;

        case '6':   /** Saturne **/
            PlaneteChoisi = 6;
            break;

		case '7':   /** Uranis **/
		    PlaneteChoisi = 7;
            break;

        case '8':   /** Neptune **/
            PlaneteChoisi = 8;
            break;

        case '9':   /** Comete **/
            CreateComete();
            //PlaneteChoisi = 8;
            break;

		default:
		    cout << "Hello world!" << endl;
            break;
	}


	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,(double)320/320,0.1,1040);
    gluLookAt( p_camx, p_camy, p_camz, cible_camx, cible_camy, cible_camz, v1, v2, v3);
    glRotatef( rotateX, 1.0f, 0, 0 );
    glRotatef( rotateY, 0, 1.0f, 0 );
    glRotatef( rotateZ, 0, 0, 1.0f );
    glutPostRedisplay();


}

void keyboardSpecialProject (int key, int xmouse, int ymouse){
    glPopMatrix();
	switch (key){
         case GLUT_KEY_RIGHT:
             glPushMatrix();
             p_camx++;
             cible_camx++;
             break;

         case GLUT_KEY_LEFT:
             glPushMatrix();
             p_camx--;
             cible_camx--;
             break;

         case GLUT_KEY_UP:
             glPushMatrix();
             p_camy++;
             cible_camy++;
             break;

         case GLUT_KEY_DOWN:
             glPushMatrix();
             p_camy--;
             cible_camy--;
             break;
	}
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,(double)320/320,0.1,1040);
    gluLookAt( p_camx, p_camy, p_camz, cible_camx, cible_camy, cible_camz, v1, v2, v3);
    glRotatef( rotateX, 1.0f, 0, 0 );
    glRotatef( rotateY, 0, 1.0f, 0 );
    glRotatef( rotateZ, 0, 0, 1.0f );
    glutPostRedisplay();
}

void MouseMotion (int mouseX, int mouseY){
    if(Motion){
        cout <<" MouseMotion   " << mouseX << "    " << mouseY << endl;
     // Mouse.
        int DX,DY;
        if (oldMouseX == -1){
             oldMouseX = mouseX;
             oldMouseY = mouseY;
        }
        else{
            newMouseX = mouseX;
            newMouseY = mouseY;
            DX = oldMouseX - newMouseX;
            DY = oldMouseY - newMouseY;
            /** Camera **/
             cout <<"   oldMouseX == " << oldMouseX <<"      oldMouseY == " << oldMouseY << endl;
             cout <<"   newMouseX == " << newMouseX <<"      newMouseY == " << newMouseY << endl;
             cout <<"   Dx == " << DX <<"      DY == " << DY << endl;
            if (DX>0){
                rotateMouseY-=DX;
            }
            if (DX<0){
                rotateMouseY-=DX;
            }
            if (DY>0){
                rotateMouseX-=DY;
            }
            if (DY<0){
                rotateMouseX-=DY;
            }
            oldMouseX = newMouseX;
            oldMouseY = newMouseY;
        }
    }
}


void MouseFunc (int button, int state, int x, int y){
   if ( state == GLUT_UP){
        oldMouseX = -1;
        oldMouseY = -1;
        Motion = false;
        if (button == GLUT_MIDDLE_BUTTON ){
            p_camz--;
        }
   }
   else{
        if (button == GLUT_LEFT_BUTTON ){
            Motion = true;
        }
        else{
            Motion = false;
            if ((button == GLUT_MIDDLE_BUTTON ) && (state ==    GLUT_DOWN)){
                p_camz++;
            }
        }
   }
}

void MouseWheel(int wheel, int direction, int x, int y)
{
    wheel=0;
    if (direction==-1)
    {
        p_camz -= 0.5;

    }
    else if (direction==+1)
    {
        p_camz += 0.5;
    }

// glutPostRedisplay();

}

void CreateComete(){
     Coordonnees PositionInitiale =  Coordonnees((double)(rand()%(35-30)+30),(double)(rand()%(25-(-20))+(-20)),(double)(rand()%(20-(-20))+(-20)));
     Coordonnees PositionFinale =  Coordonnees(-(double)(rand()%(35-30)+30),-(double)(rand()%(25-(-20))+(-20)),-(double)(rand()%(20-(-20))+(-20)));
     Planete Comete ("Comete" , PositionInitiale ,PositionFinale,Rotation[0], 0.6, 1.0, 1.0, 1.0);    //Planetes[0] = Soleil;
     PlaneteCom.push_back(Comete);


      cout << "...........  " << Comete.Coor.getPosX() << endl;
}

bool detecteCollision(Planete *Planetes, Planete Comete){
    Coordonnees coo;
    double x,y,z;
    for (int Plane = 0 ; Plane<9; Plane++){
               x = -Planetes[Plane].Coor.getPosX()*cos(AngleSurSoleil[Plane] * M_PI / 180.0);
               y = -Planetes[Plane].Coor.getPosX()*sin(AngleSurSoleil[Plane] * M_PI / 180.0);
               z = 0;
               coo = Coordonnees(x,y,z);
               if (CalcDist(coo,Comete.Coor) <= Comete.getRadius() + Planetes[Plane].getRadius() ){
                    cout << " Collision 1 " << endl;
                    return true;
               }

    }
    return false;
}

double CalcDist (Coordonnees A, Coordonnees B){
    return sqrt(pow(A.getPosX()-B.getPosX(),2)+pow(A.getPosY()-B.getPosY(),2)+pow(A.getPosZ()-B.getPosZ(),2));
}
/*************************** Manuel ******************************/
/****   I			        --> Etat Initial
/****   E			        --> Rotate Z +
/****   A			        --> Rotate Z -
/****   U			        --> Rotate Y +
/****   T			        --> Rotate Y -
/****   C			        --> Rotate X +
/****   W			        --> Rotate X -
/****   +			        --> Zoom Z +
/****   - 			        --> Zoom Z -
/****   GLUT_KEY_RIGHT 	    --> Translate X +
/****   GLUT_KEY_LEFT 	    --> Translate X -
/****   GLUT_KEY_UP		    --> Translate Y +
/****   GLUT_KEY_DOWN	    --> Translate Y -

/****   0			        --> Suivre Soleil
/****   1 			        --> Suivre Mercure
/****   2 			        --> Suivre Venus
/****   3 			        --> Suivre Terre
/****   4 			        --> Suivre Mars
/****   5 			        --> Suivre Jupiter
/****   6 			        --> Suivre Saturne
/****   7 			        --> Suivre Uranus
/****   8 			        --> Suivre Neptune

/****   0 			        --> Creation Comete Aléatoire                   ..................... PAS Encore


/****   Mouse .................................................................................... Pas encore
/****   ********************************    ****/

