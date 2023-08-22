// ==================================================
// ==           Par                                ==
// ==      Sandro Gazzo                            ==
// ==           Et                                 ==
// ==      Théo Dellouve                           ==
// ==================================================



#include <iostream>
#include <assert.h>
#include <math.h>
#include <string>
#include <fstream>
#include "matrice.h"
using namespace std;

class pendule 
{
    public:
    double pendule_non_amorti(double,double,double,const char*); // pe,dule non amorti
};

double pendule_non_amorti(double T, double delta_t, double v0,const char* LeFichier)
{
    double ite=int(T/delta_t)+1;
    double t=0;
    double v=0;
    ofstream file(LeFichier);
    for (int i=0; i<ite; i++)
    {
        v=v0*(cos(t)+sin(t));
        file <<t << " " << v << endl;
        t=t+delta_t;
    }
    file.close();
    cout << "T = " << T << " delta_t = " << delta_t << " nb d'iter = " << ite << endl ;
    return v;
}