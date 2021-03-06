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
private:
    ChainonRDV* d_t;
    int Size;

public:
    LDCR(void);                                 // Constructeur
    LDCR(const LDCR& l);                        // Constructeur par recopie
    ~LDCR(void);                                // Destructeur

    // Surcharge d'opérateurs


    // Méthodes
    int size(void) const;                       // Calcul de la taille
    void inserer(RDV* rdv);                     // Insertion
    void supprimer(RDV* rdv);                   // Suppression
    void couper(RDV* rdv);                      // Couper
    bool chercher(RDV* rdv);                    // Chercher
    void afficher(ostream& ost = cout) const;   // Afficher

};

// Fonctions globales
ostream& operator<<(ostream& ost, const LDCR& ldcr);

#endif // LDCR_H
