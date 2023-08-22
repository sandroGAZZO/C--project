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
#include <cmath>
#include "vecteur.h"
using namespace std;

class matrice 
{
    private:
        int size1;
        int size2;
        vecteur* matrix;
    public:
        matrice() {size1=size2=0;} // constructeur par defaut
        //  matrice (int n){size1=size2=n;} //bonus
        matrice(int n, int m); // constructeur matrice
        matrice(const matrice&); // constructeur par copie
        ~matrice(){delete[] matrix; size1=size2=0;}//destructeur
        vecteur& operator[] (const int&);// recupere la i-eme ligne
        double& operator() (const int&, const int&); //cout indice
        matrice& operator = (const matrice&); // affectation pour une matrice
        friend ostream& operator << (ostream&, const matrice&); //cout matrice
        friend istream& operator >> (istream&, matrice&);//cin matrice
        int& dim1(); //donne le nombre de lignes
        int& dim2(); //donne le nombre de colonnes
        matrice transpose();//la transposée de la matrice
        vecteur colonne(const int&); // recupere la j-eme colonne
        matrice operator + (const matrice&); // addition de matrice
        matrice operator - (const matrice&); //soustraction matrice
        matrice operator * (matrice&); //multiplication matrice
        matrice operator * (const double&); // multiplication matrice * scalaire
        friend matrice operator * (const double&, const matrice&); // multiplication scalaire * vecteur
        vecteur operator * ( vecteur&); // multiplication matrice*vecteur
        friend vecteur operator * ( vecteur&, matrice&); // multiplication vecteur*matrice
        void ecrire_mat(string); //ecrit la matrice
        friend matrice lire_mat(const string); //lit la matrice
        matrice lu(vecteur&);                                // factorisation lu 
        vecteur solvelu(vecteur&, vecteur&);                 // resolution lu
	    vecteur gc(vecteur&, vecteur&, double, int); //gradient conjugué
};


// ========== Créer la matrice =============

matrice :: matrice(int n, int m)
{
    size1=n;
    size2=m;
    matrix=new vecteur[n];
    vecteur v(m);
    for (int i=0; i<n; i++)
    {
        matrix[i]=v;
    }
}

matrice :: matrice (const matrice& A)
{
    int size1=A.size1;
    int size2=A.size2;
    matrix= new vecteur[size1];
    vecteur v(size2);
    for (int i=0; i<size1; i++)
    {
        matrix[i]=v;
    }
}

//=========== TRouver les lignes et les éléments =======

vecteur& matrice :: operator[] (const int& i)
{
    assert(this->size1 || this->size2);
    assert(0<=i && i<this->size1);
    return this->matrix[i];
}

double& matrice :: operator() (const int& i, const int& j)
{
    assert(this->size1 || this->size2);
    assert(0<=i && i<this->size1);
    assert(0<= j && j<this->size2);
    return this->matrix[i](j);
}


// =========== Affichage matrice ==============
matrice& matrice :: operator=(const matrice& A)
{
    assert(A.size1 || A.size2);
    assert(this->size1 || this->size2);
    if (&A != this)
    {
        assert((this->size1==A.size1) || (this->size1==0));
        assert((this->size2==A.size2) || (this->size2==0));
        if (!this->size2) matrix=new vecteur[this->size2=A.size2];
        for (int i=0; i<this->size1; i++) matrix[i]=A.matrix[i];
        return * this;
    }
}

ostream& operator << (ostream& sortie, const matrice& A)
{
    assert(A.size1 || A.size2);
   for (int i=0; i<A.size1; i++)
   {
       sortie << A.matrix[i];
   }
   sortie;
   return sortie;
}

istream& operator >> (istream&, matrice& A)
{
   assert(A.size1 || A.size2);
   for (int i=0; i<A.size1; i++)
   {
       cin >> A.matrix[i];
   }
}

// =========== Dimension matrice ============

int& matrice:: dim1()
{
 assert(this->size1);
 return this->size1;
}

int& matrice:: dim2()
{
 assert(this->size2);
 return this->size2;
}

// =========== Transposée et colonnes ==========

matrice matrice :: transpose ()
{
    assert(this->size1 || this->size2);
    matrice A (this->size2, this->size1);
    for (int j=0; j<this->size2; j++){
    for (int i=0; i<this->size1; i++)
   {
       A.matrix[j](i)=this->matrix[i](j);
   }
    }
    return A;
}

vecteur matrice:: colonne(const int& y)
{
    assert(this->size1 || this->size2);
    assert(0<=y && y<this->size2);
    vecteur v (this->size1);
    for (int i=0; i<this->size1; i++)
    {
        v(i)=this->matrix[i](y);
    }
    return v;
}

// ========= Opérateur matrice ==============


matrice matrice :: operator + (const matrice& U)
{
    assert(U.size1 || U.size2);
    assert(this->size1==U.size1 || this->size2==U.size2);
    matrice T (U.size1, U.size2);
    for (int i=0; i<U.size1; i++)
    {
        for(int j=0; j<U.size2; j++)
        {
            T.matrix[i](j)=U.matrix[i](j)+this->matrix[i](j);
        }
    }
    return T;
}

matrice matrice :: operator - (const matrice& U)
{
    assert(U.size1 || U.size2);
    assert(this->size1==U.size1 || this->size2==U.size2);
    matrice T (U.size1, U.size2);
    for (int i=0; i<U.size1; i++)
    {
        for(int j=0; j<U.size2; j++)
        {
            T.matrix[i](j)=U.matrix[i](j)-this->matrix[i](j);
        }
    }
    return T;
}

matrice matrice :: operator * (matrice& U)
{
    assert(U.size1 || U.size2);
    assert(this->size1 || this->size2);
    assert(this->size2==U.size1);
    matrice T (this->size1, U.size2);
    vecteur v (U.size1);
     for (int i=0; i<this->size1; i++)
    {
        for(int j=0; j<U.size2; j++)
        {
            T.matrix[i](j)=this->matrix[i]*U.colonne(j);
        }
    }
    return T;
}

matrice matrice :: operator * (const double& k)
{
    assert(this->size1 || this->size2);
    matrice T(this->size1, this->size2);
    for (int i=0; i<this->size1; i++)
    {
        T.matrix[i]=k*this->matrix[i];
    }
    return T;
}

matrice operator * (const double& k, const matrice& U)
{
    assert(U.size1 || U.size2);
    matrice T (U.size1, U.size2);
    for (int i=0; i<U.size1; i++)
    {
        T.matrix[i]=k*U.matrix[i];
    }
    return T;
}

vecteur matrice :: operator * (vecteur& v)
{
 assert(v.dim());
 assert(this->size2==v.dim());
 vecteur u(v.dim());
 for (int i=0; i<v.dim(); i++)
 {
     u(i)=this->matrix[i]*v;
 }
 return u; 
}

vecteur operator * ( vecteur& v, matrice& A)
{
 assert(v.dim());
 assert(A.size1==v.dim());
 vecteur u(A.size1);
 for (int i=0; i<A.size1; i++)
 {
     u(i)=v*A.colonne(i);
 }
 return u; 
}

// =========== Fichier matrice =========

void matrice :: ecrire_mat(string nom_fichier)
{
    ofstream monFlux(nom_fichier,ios::out);
    monFlux << this->size1 << " "<< this->size2 << endl;

    if (monFlux)
    {
        for (int i=0; i<this->size1; i++){
        monFlux << this->matrix[i];
        }
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }
    monFlux.close();
}


matrice lire_mat(const string nom_fichier)
{
    ifstream fichier(nom_fichier,ios::in);
    int n;
    int m;
    fichier >> n;
    fichier >> m;
    matrice M(n,m);
    for(int i=0; i<n; i++)
    {
        for (int j=0; j<m; j++){
        fichier >> M.matrix[i](j);
        }
    }
    return M;
}

// ======= Système linéaire matrice =============


matrice matrice::lu(vecteur& Piv)
{
    matrice C(size1,size2);
    if (size1!=size2)
    {cout << " Matrice non carree, factorisation LU impossible \n"; return C;}
    for (int i=0; i<size1;i++)
    {
        Piv(i)=i;
        C.matrix[i]=matrix[i];
    };
    
    for (int k=0; k<size2-1;k++)
    {
        
        double max = abs(C(int(Piv(k)),k));				  // Factorisation LU	
        int lmax = k;
        
        for (int l=k+1; l<size1;l++)
        {
            if (max<abs(C(int(Piv(l)),k)))
            {
                max = abs(C(int(Piv(l)),k));
                lmax = l;
            }     
        };
        
        int aux = Piv(k);
        Piv(k) = Piv(lmax);
        Piv(lmax) = aux;
        
        for (int p=k+1; p<size1;p++)
        {
            C(int(Piv(p)),k)=C(int(Piv(p)),k) / C(int(Piv(k)),k);
            
            for (int i=k+1; i<size1; i++)
                C(int(Piv(p)),i)=C(int(Piv(p)),i) - C(int(Piv(p)),k) * C(int(Piv(k)),i);
            
        };
    };
    return C;
}               

//------------------------------------------------------
// resolution systemes lineaires triangulaire inf et sup 
// N.B. ici Piv est un vecteur de double, converti ensuite en entier. Sinon utiliser le template vecteur

vecteur matrice::solvelu(vecteur& b, vecteur& Piv)
{
    vecteur sol(size2);
    int p;
    for (int i=0; i<size1; i++)
        sol(i) = b(int(Piv(i)));
    
    for (int k=0; k<size1; k++)
    {
        for (int j=0; j<k; j++)
        {p = int(Piv(k)); 
            sol(k) = sol(k) - matrix[p](j) * sol(j);}     		  // Résolution LU
    };
    
    for (int h=size1-1; h>=0;h--)
    {
        p = int(Piv(h));
        for(int j=h+1;j<size2;j++)
            sol(h) = sol(h) - matrix[p](j) * sol(j);
        sol(h) = sol(h) / matrix[p](h);   
    };
    return sol;
} 


//  matrice matrice :: lu ()
//  {
    // assert(this->size1 || this->size2);
    // assert(this->size1==this->size2);
    // int i;
    // int j;
    // int k;
    // matrice LU(this->size1,this->size1);
    //  for(int k=0; k<this->size1 -1;k++){
        // for(int i=k+1; i<this->size1 ;i++){
            // assert(this->matrix[k](k)>1e-8);
            // this->matrix[i](k) = this->matrix[i](k)/this->matrix[k](k);
            // for(int j=k+1; j<this->size1;j++)
                // this->matrix[i](j) =this->matrix[i](j)- this->matrix[i](k)*this->matrix[k](j);
            // }
        // }
    // LU=*this;
    // return LU;
//  }

//  vecteur matrice :: solvelu(vecteur& b)
//  {
    //  double sum;
    //  for(int i=0; i<this->size1 -1; i++)
    //  {
        //  sum=0;
        //  for (int k=0; k<i-1; k++)
        //  {
            //  sum=this->matrix[i](k)*b(k);
        //  }
        //  b(i)=b(i)-sum;
    //  }
    //  for (int i=this->size1-2;i>=0;i--  )
    //  {
        //  sum=0;
        //  for (int k=i; k<this->size1; k++)
        //  {
            //  sum=this->matrix[i](k)*b(k);
        //  }
        //  b(i)=b(i)-sum/this->matrix[i](i);
    //  }
    // vecteur x(b.dim());
    //  x=b;

    //  vecteur x(b.dim());
    //  for (int i = 0; i < this->size1; i++) {
        // x(i) = b(i);
// 
        // for (int k = 0; k < i; k++)
            // x(i) -= this->matrix[i](k) * x(k);
    // }
// 
    // for (int i = this->size1 - 1; i >=0; i--) {
        // for (int k = i ; k < this->size1; k++)
            // x(i) -= this->matrix[i](k) * x(k);
// 
        // x(i) = x(i) / this->matrix[i](i);
    // }
    // return x;
//  }

vecteur matrice :: gc (vecteur& b, vecteur& x0, double eps, int maxit)
{
    int k=0;
    vecteur g(b.dim());
    vecteur h(g.dim());
    vecteur t(g.dim());
    double rho;
    double gamma;
    g=(*this)*x0-b;
    h=-1*g;
    t=g;
    gamma=0;
    while((g*g >= eps) && (k<maxit))
    {
        rho=-(g*h)/(h*(*this*h));
        x0=x0+rho*h;
        t=g;
        g=g+rho*(*this)*h;
        gamma=(g*g)/(t*t);
        h=-1*g+gamma*h;
    }
    vecteur solu(x0.dim());
    solu=x0;
    return solu;
}