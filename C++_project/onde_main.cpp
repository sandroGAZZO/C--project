// ==================================================
// ==           Par                                ==
// ==      Sandro Gazzo                            ==
// ==           Et                                 ==
// ==      Théo Dellouve                           ==
// ==================================================


#include <iostream>
#include "onde.h"
#include <fstream>
#include <cmath>
#include <sstream>
#include <string>
#include <assert.h>
#include <time.h>
using namespace std;

int main()
{
// --------------------- DONNEES ---------------------------------------


// choix=1 : pincement d'une corde de guitare
// choix=2 : frottement d'une corde de violon
// choix=3 : corde d'un piano frappée

int choix;

vecteur vec_CFL(5); // condition CFL

vec_CFL(0)=1.2;
vec_CFL(1)=1.0;
vec_CFL(2)=0.9;
vec_CFL(3)=0.5;
vec_CFL(4)=0.1;

int T=5; // temps final

int N=50; // Nombre de maille

// string s="numero uno";
// s+= "doue";
// cout << s << endl;


// -----------------------------------------------------------------------
for (int i=0; i<5; i++)
{
double CFL=vec_CFL(i);
for (int choix=1; choix<4; choix++)
{
cout << "Les données suivantes ont été sélectionnées :" << endl;
cout << "    choix du cas à traiter :" << choix << endl;
cout << "        1 : pincement d'une corde de guitare" << endl;
cout << "        2 : frottement d'une corde de violon" << endl;
cout << "        3 : corde d'un piano frappée" << endl;
cout << "    nombres de maille :" << N << endl;
cout << "    temps final :" << T << endl;
cout << "    condition CFL :" << CFL << endl;
cout << "    le delta x :"<< 1.0/N << endl;
cout << endl;

// -------------------------- Stockages -----------------------------------
double delta_x=1.0/N;
double delta_t=CFL*pow(delta_x,2)/2;
// -------------------------- Applications --------------------------------

onde O; // classe onde

//----------------- BUG A PARTIR DE ICI ------------------------------------
int tps =25;
vecteur S;

S=ondes_euler_explicite(T,CFL,N,tps,choix, "Euler Explicite","EE Erreur L2","EE Erreur L_inf"); // erreur ici

vecteur Imp;
Imp=ondes_euler_implicite(T,CFL,N,tps,choix, "Euler Implicite", "EI Erreur L2","EI Erreur L_inf");

vecteur CN;
CN=ondes_crank_nicolson(T,CFL,N,tps,choix, "Crank-Nicolson", "CN Erreur L2", "CN Erreur L_inf");
// -------------------------- Graphique -----------------------------------

    //parametre pour gnuplot
    double xi,yi;
    double temps;

    //fenetre sur l'ordonné
    double ymin=-1.5;
    double ymax=1.5;

    //fenetre sur l'abscisse
    double xmin=0.0;
    double xmax=1.0;


    // On trace l'évolution en temps:

    ofstream file2("film1.gnuplot");
    //file2 << "set terminal x11" << endl;
    file2 << "set xrange[" << xmin << ":" << xmax << "]" << endl; //fenetre sur l'abscisse
    file2 << "set yrange[" << ymin << ":" << ymax << "]" << endl; //fenetre sur l'ordonné
    file2 << "imax=" << T << endl; 
    file2 << "i=0" << endl;
    file2 << "load \"script1.gnu\" ";
    file2.close();

    ofstream file3("script1.gnu");
    file3 << "plot \"Euler Explicite\" index i with linespoints pointtype 7 pointsize 1" << endl;
    file3 << "pause" << " " << 0.5 <<  endl;
    file3 << "i=i+1"<< endl;
    file3 << "if (i<imax) reread" << endl;
    file3 << "pause -1 \"Appuyer sur une touche pour terminer \" " << endl;

    system("gnuplot film1.gnuplot");

    ofstream file4("film1.gnuplot");
    //file4 << "set terminal x11" << endl;
    file4 << "set xrange[" << xmin << ":" << xmax << "]" << endl; //fenetre sur l'abscisse
    file4 << "set yrange[" << ymin << ":" << ymax << "]" << endl; //fenetre sur l'ordonné
    file4 << "imax=" << T << endl; 
    file4 << "i=0" << endl;
    file4 << "load \"script1.gnu\" ";
    file4.close();


    ofstream file5("script1.gnu");
    file5 << "plot \"Euler Implicite\" index i with linespoints pointtype 7 pointsize 1" << endl;
    file5 << "pause" << " " << 0.5 <<  endl;
    file5 << "i=i+1"<< endl;
    file5 << "if (i<imax) reread" << endl;
    file5 << "pause -1 \"Appuyer sur une touche pour terminer \" " << endl;

    system("gnuplot film1.gnuplot");

    ofstream file6("film1.gnuplot");
    //file6 << "set terminal x11" << endl;
    file6 << "set xrange[" << xmin << ":" << xmax << "]" << endl; //fenetre sur l'abscisse
    file6 << "set yrange[" << ymin << ":" << ymax << "]" << endl; //fenetre sur l'ordonné
    file6 << "imax=" << T << endl; 
    file6 << "i=0" << endl;
    file6 << "load \"script1.gnu\" ";
    file6.close();


    ofstream file7("script1.gnu");
    file7 << "plot \"Crank-Nicolson\" index i with linespoints pointtype 7 pointsize 1" << endl;
    file7 << "pause" << " " << 0.5 <<  endl;
    file7 << "i=i+1"<< endl;
    file7 << "if (i<imax) reread" << endl;
    file7 << "pause -1 \"Appuyer sur une touche pour terminer \" " << endl;

    system("gnuplot film1.gnuplot");

    double zmax=5.0;
    // double zmax=floor(T/delta_t);
    double zmin=0;
    double wmax=1.0;
    double wmin=0;

    ofstream file8("film1.gnuplot");
    //file8 << "set terminal x11" << endl;
    file8 << "set xrange[" << zmin << ":" << zmax << "]" << endl; //fenetre sur l'abscisse
    file8 << "set yrange[" << wmin << ":" << wmax << "]" << endl; //fenetre sur l'ordonné
    file8 << "imax=" << T << endl; 
    file8 << "i=0" << endl;
    file8 << "load \"script1.gnu\" ";
    file8.close();


    ofstream file9("script1.gnu");
    file9 << "plot \"EE Erreur L2\" index i with linespoints pointtype 7 pointsize 1" << endl;
    file9 << "pause -1 \"Appuyer sur une touche pour terminer \" " << endl;

    system("gnuplot film1.gnuplot");

    ofstream file10("film1.gnuplot");
    //file10 << "set terminal x11" << endl;
    file10 << "set xrange[" << zmin << ":" << zmax << "]" << endl; //fenetre sur l'abscisse
    file10 << "set yrange[" << wmin << ":" << wmax << "]" << endl; //fenetre sur l'ordonné
    file10 << "imax=" << T << endl; 
    file10 << "i=0" << endl;
    file10 << "load \"script1.gnu\" ";
    file10.close();


    ofstream file11("script1.gnu");
    file11 << "plot \"EI Erreur L2\" index i with linespoints pointtype 7 pointsize 1" << endl;
    file11 << "pause -1 \"Appuyer sur une touche pour terminer \" " << endl;

    system("gnuplot film1.gnuplot");

    ofstream file12("film1.gnuplot");
    //file12 << "set terminal x11" << endl;
    file12 << "set xrange[" << zmin << ":" << zmax << "]" << endl; //fenetre sur l'abscisse
    file12 << "set yrange[" << wmin << ":" << wmax << "]" << endl; //fenetre sur l'ordonné
    file12 << "imax=" << T << endl; 
    file12 << "i=0" << endl;
    file12 << "load \"script1.gnu\" ";
    file12.close();


    ofstream file13("script1.gnu");
    file13 << "plot \"CN Erreur L2\" index i with linespoints pointtype 7 pointsize 1" << endl;
    file13 << "pause -1 \"Appuyer sur une touche pour terminer \" " << endl;

    system("gnuplot film1.gnuplot");

    ofstream file14("film1.gnuplot");
    //file14 << "set terminal x11" << endl;
    file14 << "set xrange[" << zmin << ":" << zmax << "]" << endl; //fenetre sur l'abscisse
    file14 << "set yrange[" << wmin << ":" << wmax << "]" << endl; //fenetre sur l'ordonné
    file14 << "imax=" << T << endl; 
    file14 << "i=0" << endl;
    file14 << "load \"script1.gnu\" ";
    file14.close();


    ofstream file15("script1.gnu");
    file15 << "plot \"EE Erreur L_inf\" index i with linespoints pointtype 7 pointsize 1" << endl;
    file15 << "pause -1 \"Appuyer sur une touche pour terminer \" " << endl;

    system("gnuplot film1.gnuplot");

    ofstream file16("film1.gnuplot");
    //file16 << "set terminal x11" << endl;
    file16 << "set xrange[" << zmin << ":" << zmax << "]" << endl; //fenetre sur l'abscisse
    file16 << "set yrange[" << wmin << ":" << wmax << "]" << endl; //fenetre sur l'ordonné
    file16 << "imax=" << T << endl; 
    file16 << "i=0" << endl;
    file16 << "load \"script1.gnu\" ";
    file16.close();


    ofstream file17("script1.gnu");
    file17 << "plot \"EI Erreur L_inf\" index i with linespoints pointtype 7 pointsize 1" << endl;
    file17 << "pause -1 \"Appuyer sur une touche pour terminer \" " << endl;

    system("gnuplot film1.gnuplot");

    ofstream file18("film1.gnuplot");
    //file18 << "set terminal x11" << endl;
    file18 << "set xrange[" << zmin << ":" << zmax << "]" << endl; //fenetre sur l'abscisse
    file18 << "set yrange[" << wmin << ":" << wmax << "]" << endl; //fenetre sur l'ordonné
    file18 << "imax=" << T << endl; 
    file18 << "i=0" << endl;
    file18 << "load \"script1.gnu\" ";
    file18.close();


    ofstream file19("script1.gnu");
    file19 << "plot \"CN Erreur L_inf\" index i with linespoints pointtype 7 pointsize 1" << endl;
    file19 << "pause -1 \"Appuyer sur une touche pour terminer \" " << endl;

    system("gnuplot film1.gnuplot");

}
}

return 0;
}