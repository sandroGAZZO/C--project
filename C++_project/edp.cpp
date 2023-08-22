// ==================================================
// ==           Par                                ==
// ==      Sandro Gazzo                            ==
// ==           Et                                 ==
// ==      Théo Dellouve                           ==
// ==================================================


#include <iostream>
#include "edp.h"
#include <fstream>
#include <cmath>
#include <sstream>
#include <string>
#include <assert.h>
#include <time.h>
using namespace std;

int main()
{
    double T=2.;
    double L=2.;
    double CFL=1./2;
    int i=8;
    // for (int i=3; i<9;i++)
    // {
    int N=pow(2,i);
    vecteur u(N), w(N);
    edp A;
    edp B;
    u=B.u0_a(N,L);
    w=A.transport_upwind(N,CFL,L,T,u);

    cout << "pour N= " << N <<endl;

    cout << "Amont:" << endl;
    cout << w <<endl;


    w.ecrire("fichier_am.txt");


    //---------------------------------------
    int nx=pow(2,i);
    int nt=10;
    double ymin=1e10;
    double ymax=-1e10;
    double xi,yi;
    double Tfinal=2.0;
    double temps;
    double xmin=0.0;
    double xmax=3.2;

    vecteur x(nx);
    vecteur v(nx);
    ofstream file1("test1.txt");
    for (int i=0; i<nx;i++)
    {x(i)=(i+1)*2./nx;}
    u=B.u0_a(N,L);
    cout<<"u0="<<u<<endl;

    for (int n=0; n<nt; n++)
        {
        u=A.transport_upwind(N,CFL,L,T,u);
        //  u=A.transport_lax_friedrichs(N,CFL,L,T,u);
        // u=A.transport_lax_wendroff(N,CFL,L,T,u);
        // file1 << 0 << " " << 0 << endl;
        temps=(n+1)*Tfinal/nt;
        cout<< u << endl;
        for (int i=0; i<nx; i++)
            {
            xi=x(i);
            yi=u(i);
            if (yi<ymin)
            {ymin=yi;}
            if (yi>ymax)
            {ymax=yi;}
            file1 << xi << " " << yi << endl;
            }
            file1 << endl << endl;

        }
    file1.close();

    ofstream file2("film1.gnuplot");
    //file2 << "set terminal x11" << endl;
    file2 << "set xrange[" << xmin << ":" << xmax << "]" << endl;
    file2 << "set yrange[" << ymin << ":" << ymax << "]" << endl;
    file2 << "imax=" << nt << endl;
    file2 << "i=0" << endl;
    file2 << "load \"script1.gnu\" ";
    file2.close();

    ofstream file3("script1.gnu");
    file3 << "plot \"test1.txt\" index i with linespoints pointtype 7 pointsize 1" << endl;
    file3 << "pause" << " " << 0.5 <<  endl;
    file3 << "i=i+1"<< endl;
    file3 << "if (i<imax) reread" << endl;
    file3 << "pause -1 \"Appuyer sur une touche pour terminer \" " << endl;

    system("gnuplot film1.gnuplot");

    //-------------------------------------------
// 
//   ofstream file2("film1.gnuplot");
 //   file2 << "set terminal x11" << endl;
    // file2 << "set xrange[" << xmin << ":" << xmax << "]" << endl;
    // file2 << "set yrange[" << ymin << ":" << ymax << "]" << endl;
    // file2 << "imax=" << nt << endl;
    // file2 << "i=0" << endl;
    // file2 << "load \"script1.gnu\" ";
    // file2.close();
    // system("gnuplot film1.gnuplot");
// 
    // w=A.transport_lax_friedrichs(N,CFL,L,T,u);
    // cout << "Lax-Friedrichs:"<< endl;
    // cout << w <<endl;
    // 
// 
    // w.ecrire("fichier_lf.txt");
    //  ofstream file3("film2.gnuplot");
 //   file3 << "set terminal x11" << endl;
    // file3 << "set xrange[" << xmin << ":" << xmax << "]" << endl;
    // file3 << "set yrange[" << ymin << ":" << ymax << "]" << endl;
    // file3 << "imax=" << nt << endl;
    // file3 << "i=0" << endl;
    // file3 << "load \"script1.gnu\" ";
    // file3.close();
    // system("gnuplot film2.gnuplot");
// 
    // w=A.transport_lax_wendroff(N,CFL,L,T,u);
    // cout << "Lax-Wendroff"<< endl;
    // cout << w <<endl;
    // 
// 
    // w.ecrire("fichier_lw.txt");
    //  ofstream file4("film3.gnuplot");
 //   file4 << "set terminal x11" << endl;
    // file4 << "set xrange[" << xmin << ":" << xmax << "]" << endl;
    // file4 << "set yrange[" << ymin << ":" << ymax << "]" << endl;
    // file4 << "imax=" << nt << endl;
    // file4 << "i=0" << endl;
    // file4 << "load \"script1.gnu\" ";
    // file4.close();
    // system("gnuplot film3.gnuplot");
  //  }
// 
    return 0;
    
}