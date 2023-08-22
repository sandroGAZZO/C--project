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

class edp //: public vecteur
{
    public:
        //edp (int N):vecteur(N){} // constructeur edp hérité de la classe vecteur
        edp() {"ici commence edp";}
        vecteur transport_upwind (const int&, const double&, const double&, const double&, vecteur&); //décentré amont
        vecteur transport_lax_friedrichs(const int&, const double&, const double&, const double&, vecteur&); // Lax-Friedrichs
        vecteur transport_lax_wendroff(const int&, const double&, const double&, const double&, vecteur&); // Lax-Wendroff
        vecteur u0_a(int&, double&);
        vecteur u0_b(int&, double&);
};

vecteur edp :: transport_upwind(const int& N, const double& CFL, const double& T, const double& L, vecteur& b)
{
    double dx=L/N;
    double dt= CFL*dx*2;
    double a=0.5;
    // dt=T/M : M=1/dt
    double M=int(T/dt)+1;
    vecteur v(N);
    v=b;
    for (int n=1; n<M; n++)
    {
        for (int j=N-1; j>0; j--)
        {
            v(j)=v(j)-a*CFL*(v(j)-v(j-1));
        }
        v(0)=0;
    }
    return v;
}

 

vecteur edp :: transport_lax_friedrichs(const int& N, const double& CFL, const double& T, const double& L, vecteur& b)
{
    double dx=L/N;
    double dt= CFL*dx;
    double a=0.5;
    // dt=T/M : M=1/dt
    double M=1/dt;
    vecteur v(N);
    v=b;
    for (int n=1; n<M; n++)
    {
        v(N-1)=(1./2)*(v(N-2)+v(N-2));
        for (int j=N-2; j>0; j--)
        {
            v(j)=(1./2)*(v(j+1)+v(j-1))-(a/2)*CFL*(v(j+1)-v(j-1));
        }
        v(0)=0;
    }
    return v;
}


vecteur edp :: transport_lax_wendroff(const int& N, const double& CFL, const double& T, const double& L, vecteur& b)
{
    double dx=L/N;
    double dt= CFL*dx;
    double a=0.5;
    // dt=T/M : M=1/dt
    double M=1/dt;
    vecteur v(N);
    v=b;
    for (int n=1; n<M; n++)
    {
        v(N-1)=v(N-1)+(1./2)*pow(CFL,2)*pow(a,2)*(2*v(N-2)-2*v(N-1));
        for (int j=N-2; j>0; j--)
        {
            v(j)=v(j)-(1./2)*a*CFL*(v(j+1)+v(j-1))+(1./2)*pow(a,2)*pow(CFL,2)*(v(j+1)-2*v(j)+v(j-1));
        }
        v(0)=0;
    }
    return v;
}

vecteur edp :: u0_a(int& N, double& L)
{
    vecteur x(N);
    x(0)=0;
    for (int i=1; i<N; i++)
    {
        x(i)=x(i-1)+L/N;
    }

    vecteur u0(N);
    for (int j=0; j<N; j++)
    {
        u0(j)=exp(-5*pow((5*x(j)-4),2));
    }

    return u0;
}

vecteur edp :: u0_b(int& N, double& L)
{
    vecteur x(N);
    x(0)=0;
    for (int i=1; i<N; i++)
    {
        x(i)=x(i-1)+L/N;
    }

    vecteur u(N);
    for (int j=0; j<N; j++)
    {
       if ((x(j)>=0.1) && (x(j)<=0.5))
       {
           u(j)=1;
       }
       else
       {
           u(j)=0;
       }
    }

    return u;
}

