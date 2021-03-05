#ifndef LDCR_H
#define LDCR_H

#include "rdv.h"

class ChainonRDV
{
    friend class LDCR;
private:
    ChainonRDV(RDV* rdv) : rdv(rdv), d_prec(nullptr), d_suiv(nullptr) {};

    RDV* rdv;
    ChainonRDV* d_prec, * d_suiv;

};

class LDCR
{
public:
    LDCR(void);                     // Constructeur
    LDCR(const LDCR& l);            // Constructeur par recopie
    ~LDCR(void);                    // Destructeur
    int taille(void) const;         // Calcul de la taille
    void inserer(RDV*);             // Insertion
    void supprimer(RDV*);           // Suppression
    void couper(RDV*);              // Couper
    bool chercher(RDV*);            // Chercher
    void afficher(ostream&) const;  // Afficher
private:
    ChainonRDV* d_t;
    int size;
};

#endif // LDCR_H
