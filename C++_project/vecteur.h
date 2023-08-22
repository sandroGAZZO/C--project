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
using namespace std;

class vecteur
{
private :
    int size;
    double* p;
public :
    vecteur() {size=0;} // constructeur par défaut
    vecteur(int a); //constructeur affectant l'entier a la taille du vecteur
    vecteur(const vecteur&);//constructeur par recopie
    ~vecteur(){delete [] p; size=0;} // destructeur
    double& operator () (const int&); // surdefinition operateur ()
    friend ostream& operator << (ostream&, const vecteur&); // cout pour vecteur
    friend istream& operator >> (istream&, vecteur&); // cin pour vecteur
    vecteur& operator = (const vecteur&); // affectation pour vecteur
    int& dim(); // donne la dimension d'un vecteur
    bool operator == (const vecteur&); // compare 2 vecteurs
    friend vecteur operator * (const double&,const vecteur&); // produit d'un scalaire par un vecteur
    vecteur operator * (const double&); // produit d'un vecteur par un scalaire
    friend double operator* (const vecteur&, const vecteur&); // produit scalaire entre deux vecteurs
    friend vecteur operator / (const vecteur&, const double&); // division d'un vecteur par un scalaire
    friend vecteur operator + (const vecteur&, const vecteur&); // addition de deux vecteurs
    friend vecteur operator - (const vecteur&, const vecteur&); //soustraction de deux vecteurs
    double norm_infini (); // norme infini d'un vecteur
    double norm_1 (); // norme un d'un vecteur
    double norm_euclid (); // norme euclidienne d'un vecteur
    double norm_2 (); // norme deux d'un vecteur
    void ecrire(string);
    void lire(string);
};


// ========== Créer le vecteur ============
vecteur:: vecteur(int a)
{
    size=a;
    p=new double[a];
    for (int i=0; i<a; i++)
     {
     p[i]=0;
     }
}

 vecteur:: vecteur ( const vecteur& q)
 {
     int size =q.size;
     p=new double[size];
     for (int i=0; i<size; i++)
     {
     p[i]=q.p[i];
     }
}


// ========== Recherche et affichage de vecteurs et de ses éléments =======
double& vecteur:: operator()(const int& i)
{
     assert(this->size);
     assert(0<=i && i<this->size);
    return this -> p[i];
}

ostream& operator << (ostream& sortie, const vecteur& q)
{
     assert(q.size);
     for (int i=0; i<q.size; i++)
     {
        sortie << q.p[i]<< " ";
     }
     sortie << endl;
     return sortie;
}

istream& operator >> (istream&, vecteur& q)
{
     assert(q.size);
     for (int i=0; i<q.size; i++)
     {
     cin >> q.p[i];
     }
}


// ===== Opérateur sur les vecteurs + dimension =========
vecteur& vecteur :: operator = (const vecteur& v)
{
    assert(v.size);
    if (&v != this)
    {
    assert((this->size==v.size) || (this->size==0));
    if(!this->size) p=new double[this->size=v.size];
    for (int i=0; i<this->size; i++) p[i]=v.p[i];
    return * this;
    }

}

int& vecteur:: dim()
{
 assert(this->size);
 return this->size;

}

bool vecteur :: operator == (const vecteur& v)
{
    assert(v.size);
    assert((this->size==v.size) || (this->size==0));
    for (int i=0; i<v.size; i++)
    {
        if (this->p[i]!=v.p[i]) return false;
    }
    return true;
}

vecteur vecteur :: operator * (const double& k) // Cette méthode appartient à la classe
 {
   assert(this->size);
   vecteur w(this->size);
   for (int i=0; i<this->size; i++)
   {
       w.p[i]=k*p[i];
   }
   return w;
}

  vecteur operator * (const double& k, const vecteur& v) // Cette méthode est amie de la classe
  {
    assert(v.size);
    vecteur w(v.size);
    for (int i=0; i<v.size; i++)
    {
        w.p[i]=k*v.p[i];
    }
    return w;
 }

double  operator* (const vecteur& v, const vecteur& w)
{
    assert(v.size);
    assert(w.size);
    assert(w.size==v.size);
    // vecteur q(v.size);
    double q;
    for (int i=0; i<v.size; i++)
    {
        q+=w.p[i]*v.p[i];
    }
    return q;
}


  vecteur operator / (const vecteur& v,const double& k) // Cette méthode est amie de la classe
  {
    assert(v.size);
    assert(k!=0);
    vecteur w(v.size);
    for (int i=0; i<v.size; i++)
    {
        w.p[i]=v.p[i]/k;
    }
    return w;
 }

vecteur operator + (const vecteur& v, const vecteur& w)
{
    assert(v.size);
    assert(w.size);
    assert(w.size==v.size);
    vecteur q(v.size);
    for (int i=0; i<v.size; i++)
    {
        q.p[i]=w.p[i]+v.p[i];
    }
    return q;
}

vecteur operator - (const vecteur& v, const vecteur& w)
{
    assert(v.size);
    assert(w.size);
    assert(w.size==v.size);
    vecteur q(v.size);
    for (int i=0; i<v.size; i++)
    {
        q.p[i]=w.p[i]-v.p[i];
    }
    return q;
}

// ========= normes d'un vecteur =============

double vecteur :: norm_infini()
{   
    assert(this->size);
  double a=0.;
  int j=0;
  for (int i=0; i<this->size; i++)
  {
      if(abs(this->p[i])>a)
      {
          j=i;
          a=abs(this->p[i]);
      }
  }
  return abs(this->p[j]);
}


double vecteur :: norm_1()
{   
  assert(this->size);
  vecteur w(1);
  for (int i=0; i<this->size; i++)
  {
      w.p[0]+=abs(this->p[i]);
  }
  return w.p[0];
}

double vecteur :: norm_euclid()
{   
    assert(this->size);
  vecteur w(1);
  for (int i=0; i<this->size; i++)
  {
      w.p[0]+=pow(this->p[i],2);
  }
  return sqrt(w.p[0]);
}


double vecteur :: norm_2()
{   
    assert(this->size);
  vecteur w(1);
  for (int i=0; i<this->size; i++)
  {
      w.p[0]+=pow(this->p[i],2);
  }
  return sqrt(w.p[0]/this->size);
}


// ========== Le vecteur dans un fichier ==========

void vecteur :: ecrire(string nom_fichier)
{
    ofstream monFlux(nom_fichier,ios::out);
    monFlux << this->size << endl;
    if (monFlux)
    {
        for (int i=0; i<this->size; i++){
        monFlux << this->p[i] << endl;
        }
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }
    monFlux.close();
}

void vecteur :: lire(string nom_fichier)
{
ifstream fichier (nom_fichier,ios::in);
fichier >> this->size;
this->p=new double [this->size];
    for (int i=0; i<this->size;i++){
    fichier >> this->p[i];
}
fichier.close();
}