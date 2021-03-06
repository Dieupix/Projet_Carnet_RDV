#ifndef LDCP_H
#define LDCP_H

#include "personne.h"

class ChainonPersonne
{
    friend class LDCP;
private:
    ChainonPersonne(Personne* p) : p(p), d_prec(nullptr), d_suiv(nullptr) {};

    Personne* p;
    ChainonPersonne* d_prec, * d_suiv;

};

class LDCP
{
public:
    LDCP(void);                                 // Constructeur
    LDCP(const LDCP& l);                        // Constructeur par recopie
    ~LDCP(void);                                // Destructeur
    int size(void) const;                       // Calcul de la taille
    void inserer(Personne* p);                  // Insertion
    void supprimer(Personne* p);                // Suppression
    void couper(Personne* p);                   // Couper
    bool chercher(Personne* p);                 // Chercher
    void afficher(ostream& ost = cout) const;   // Afficher

private:
    ChainonPersonne* d_t;
    int Size;
};

#endif // LDCP_H
