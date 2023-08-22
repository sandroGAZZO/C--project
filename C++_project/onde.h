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

class onde
{
    public:
        vecteur u0(int, double, int); // donne u0 selon le choix : u0(N, a, choix)
        vecteur ut(int, double, int, double); // donne ut selon le choix : ut(N, a, b, choix)
        vecteur ondes_euler_explicite(double, double, int, int&, int&, const char*, const char*, const char*); // schéma euler explicite
        vecteur ondes_euler_implicite(double, double, int, int&, int&, const char*, const char*, const char*); // schéma euler implicite
        vecteur ondes_crank_nicolson(double, double, int, int&, int&, const char*, const char*, const char*); // schéma Crank-Nicolson
};


vecteur onde :: u0(int N,double a, int choix)
{
    // choix 1 : pincement d'une corde de guitare
    // choix 2 : frottement d'une corde de violon
    // choix 3 : corde d'un piano frappée
    // choix de a nécessaire pour choix 1 et choix 3
    assert(a<1 && a>0);
    vecteur x(N+1);
    for (int j=0; j<N+1; j++) // mauvais N ??
    {
        x(j)= double(j)/(N+1);
    }
    vecteur u0(N+1);

    //-------------------------
    if (choix==1)
    {
    for (int j=0; j<N+1;j++)
    {
        if (x(j)<=a)
        {
            u0(j)=x(j)/a;
        }
        else
        {
            u0(j)=(1-x(j))/(1-a);
        }
    }
    }
    //-------------------------
    if (choix==2)
    {
        for (int j=0; j<N+1;j++)
        {
            u0(j)=4*x(j)*(1-x(j));
        }
    }
    //-------------------------
    if (choix==3)
    {
        for (int j=0; j<N+1;j++)
        {
        u0(j)=0;
        }
    }
    //-------------------------
return u0;
}

vecteur onde :: ut(int N,double a, int choix, double delta_t)
{
    // choix 1 : pincement d'une corde de guitare
    // choix 2 : frottement d'une corde de violon
    // choix 3 : corde d'un piano frappée
    // choix de a nécessaire pour choix 1 et choix 3
    assert(a<0.9 && a>0);
    vecteur x(N+1);
    double b=0.1;
    double c0=2;
    for (int j=0; j<N+1; j++) // mauvais N ??
    {
        x(j)= double(j)/(N+1);
    }
    vecteur ut(N+1);
    //-------------------------
    if (choix==1)
    {
        for (int j=0; j<N+1;j++)
        {
        ut(j)=0;
        }
    }
    //-------------------------
    if (choix==2)
    {
       for (int j=0; j<N+1;j++)
        {
        ut(j)=0;
        }
    }
    //-------------------------
    if (choix==3)
    {
        for(int j=0; j<N+1; j++)
        {
        if ((x(j)>a)&&(x(j)<=a+b))
        {
            ut(j)=delta_t*pow(10,7);
        }
        else
        {
        ut(j)=0;
        }
        }
    }
    //-------------------------
    
return ut;
}

vecteur ondes_euler_explicite(double T,double CFL, int N, int& tps, int& choix, const char* LeFichier, const char* Erreur1, const char* Erreur2)
{
    onde O; // classe onde

    //Vecteurs de stockage
    vecteur u0(N+1);
    vecteur ut(N+1);
    vecteur u1(N+1);
    vecteur u(N+1);
    vecteur mu(N+1);
    vecteur lam(N+1);

    //Données
    double delta_x=1.0/N;
    double delta_t=CFL*pow(delta_x,2)/2;
    double a=delta_t/pow(delta_x,2);
    tps=floor(T/delta_t);

    //Solutions initiales
    u0=O.u0(N,a,choix);
    ut=O.ut(N,a,choix, delta_t); // necessaire au calcul de u1
    u1=delta_t*ut+u0; // on calcul u1 avec a formule ut(x,0)=(u(x,dt)-u(x,0))/dt

    ofstream file(LeFichier);
    ofstream file1(Erreur1);
    ofstream file2(Erreur2);

    lam=u0;
    mu=u1;
    double new_delta_t =delta_t;
    
    for (int i=1; i<=tps; i++) // k...
    {

        for (int j=1; j<N; j++)
        {
            u(j)=mu(j)+(mu(j+1)-2*mu(j)+mu(j-1))*a-lam(j);
            file <<j*delta_x << " " << u(j) << endl;
            // V=CFL*A*u1+2*u1-u0;
            // M[i](j)=V(j);
        }
        new_delta_t=new_delta_t+delta_t;
        file1 << new_delta_t << " " << u.norm_2()<< endl;
        file2 << new_delta_t << " " << u.norm_infini()<< endl;

        lam=mu;
        mu=u;
        file << endl << endl;
        // for (int j=0; j<N+2; j++)
        // {
        // u0(j)=u1(j);
        // u1(j)=M[i](j)+1;
        // }
    }    
    file.close();
    file1.close();
    file2.close();
    cout << "N = " << N << " delta_t = " << delta_t << " iter en temps = " << tps << endl ;
    return u;
}



vecteur ondes_euler_implicite(double T,double CFL, int N, int& tps, int& choix, const char* LeFichier, const char* Erreur1, const char* Erreur2)
{
    onde O; // classe onde

    //Vecteurs de stockage
    vecteur u0(N+1);
    vecteur ut(N+1);
    vecteur u1(N+1);
    vecteur u(N+1);
    vecteur mu(N+1);
    vecteur lam(N+1);

    //Données
    double delta_x=1.0/N;
    double delta_t=CFL*pow(delta_x,2)/2;
    double a=delta_t/pow(delta_x,2);
    tps=floor(T/delta_t);

    //Solutions initiales
    u0=O.u0(N,a,choix);
    ut=O.ut(N,a,choix, delta_t); // necessaire au calcul de u1
    u1=delta_t*ut+u0; // on calcul u1 avec a formule ut(x,0)=(u(x,dt)-u(x,0))/dt

    //Matrice tridiagonale
    matrice A(N+1,N+1);
    A(0,1)=0;
    A(N,N-1)=0;
    A(0,0)=1.0+2*a;
    A(N,N)=1.0+2*a;
    for(int j=1;j<N;j++)
    {
        A(j,j)=1+2*a ;
        A(j,j-1)=-a ;
        A(j,j+1)=-a ;
    }

    // Factorisation LU de M
    vecteur pivot(N+1);
    matrice L(N+1,N+1);
    L=A.lu(pivot);

    ofstream file(LeFichier);
    ofstream file1(Erreur1);
    ofstream file2(Erreur2);

    lam=u0;
    mu=u1;
    double new_delta_t =delta_t;

    for(int i=1;i<=tps;i++)
    {
        u=L.solvelu(lam,pivot)-mu;
        //u=L.solvelu(lam,pivot)-0.5*mu; //bon??
        for(int j=1;j<N;j++)
        {
            file<<j*delta_x << " " << u(j) << endl;
        }
        new_delta_t=new_delta_t+delta_t;
        file1 << new_delta_t << " " << u.norm_2()<< endl;
        file2 << new_delta_t << " " << u.norm_infini()<< endl;

        lam=mu;
        mu=u;
        
        file << endl << endl;
    }
    file.close();


    cout << "N = " << N << " delta_t = " << delta_t << " iter en temps = " << tps << endl ;
    return u;
}

vecteur ondes_crank_nicolson(double T,double CFL, int N, int& tps, int& choix, const char* LeFichier, const char* Erreur1, const char* Erreur2)
{
    onde O; // classe onde

    //Vecteurs de stockage
    vecteur u0(N+1);
    vecteur ut(N+1);
    vecteur u1(N+1);
    vecteur u(N+1);
    vecteur mu(N+1);
    vecteur lam(N+1);
    vecteur gam(N+1);

    //Données
    double delta_x=1.0/N;
    double delta_t=CFL*pow(delta_x,2)/2;
    double a=delta_t/pow(delta_x,2);
    tps=floor(T/delta_t);

    //Solutions initiales
    u0=O.u0(N,a,choix);
    ut=O.ut(N,a,choix,delta_t); // necessaire au calcul de u1
    u1=delta_t*ut+u0; // on calcul u1 avec a formule ut(x,0)=(u(x,dt)-u(x,0))/dt

    //Matrice tridiagonale
    matrice A_droite(N+1,N+1);
    A_droite(0,1)=0;
    A_droite(N,N-1)=0;
    A_droite(0,0)=1.0-2*a;
    A_droite(N,N)=1.0-2*a;
    matrice A_gauche(N+1,N+1);
    A_gauche(0,0)=1.0+2*a;
    A_gauche(N,N)=1.0+2*a;
    A_gauche(0,1)=0;
    A_gauche(N,N-1)=0;
    for(int j=1;j<N;j++)
    {
        A_droite(j,j)=1-2*a;
        A_droite(j,j-1)=a;
        A_droite(j,j+1)=a;
        A_gauche(j,j)=1+2*a;
        A_gauche(j,j-1)=-a;
        A_gauche(j,j+1)=-a;
    }

    // Factorisation LU de M
    vecteur pivot(N+1);
    matrice L(N+1,N+1);
    L=A_gauche.lu(pivot);

// Boucle en temps et generation du fichier de donnees
    ofstream file(LeFichier);
    ofstream file1(Erreur1);
    ofstream file2(Erreur2);
    
    double new_delta_t =delta_t;
    lam=u0;
    mu=u1;
    for(int i=1;i<=tps;i++)
    {
        gam=A_droite*lam;
        u=L.solvelu(gam,pivot)-(1.0/2)*mu;

        // gam=A_droite*0.5*lam;
        // u=L.solvelu(gam,pivot)-(1.0/2)*mu;
        for(int j=1;j<N;j++)
        {
            file<<j*delta_x << " " <<u(j) << endl;
        }
        new_delta_t=new_delta_t+delta_t;
        file1 << new_delta_t << " " << u.norm_2()<< endl;
        file2 << new_delta_t << " " << u.norm_infini()<< endl;
        lam=mu;
        mu=u ;
        
        file << endl << endl;
        }
    file.close();
    file1.close();
    file2.close();
    
    cout << "N = " << N << " delta_t = " << delta_t << " iter en temps = " << tps << endl ;
    return u;
}




