// ==================================================
// ==           Par                                ==
// ==      Sandro Gazzo                            ==
// ==           Et                                 ==
// ==      Théo Dellouve                           ==
// ==================================================


#include <iostream>
#include "pendule.h"
#include <fstream>
#include <cmath>
#include <sstream>
#include <string>
#include <assert.h>
#include <time.h>
using namespace std;

int main(){
    double T=50;
    double delta_t=0.01;
    vecteur v0_vect(2);
    v0_vect(0)=0.5;
    v0_vect(1)=3;

    for (int i=0; i<2; i++)
    {
    double v0=v0_vect(i);

    double zero;
    
    zero=pendule_non_amorti(T,delta_t,v0,"solution");

    double xmin=0;
    double xmax=T;

    double ymin=-(v0+0.5);
    double ymax=v0+0.5;

    ofstream file2("film1.gnuplot");
    //file2 << "set terminal x11" << endl;
    file2 << "set xrange[" << xmin << ":" << xmax << "]" << endl; //fenetre sur l'abscisse
    file2 << "set yrange[" << ymin << ":" << ymax << "]" << endl; //fenetre sur l'ordonné
    file2 << "imax=" << T << endl; 
    file2 << "i=0" << endl;
    file2 << "load \"script1.gnu\" ";
    file2.close();

    ofstream file3("script1.gnu");
    file3 << "plot \"solution\" index i with linespoints pointtype 5001 pointsize 1" << endl;
    file3 << "pause -1 \"Appuyer sur une touche pour terminer \" " << endl;

    }

    return 0;
}