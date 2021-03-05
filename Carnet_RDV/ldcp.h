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
    LDCP(void);                     // Constructeur
    LDCP(const LDCP& l);            // Constructeur par recopie
    ~LDCP(void);                    // Destructeur
    int taille(void) const;         // Calcul de la taille
    void inserer(Personne*);        // Insertion
    void supprimer(Personne*);      // Suppression
    void couper(Personne*);         // Couper
    bool chercher(Personne*);       // Chercher
    void afficher(ostream&) const;  // Afficher
private:
    ChainonPersonne* d_t;
    int size;
};

#endif // LDCP_H
