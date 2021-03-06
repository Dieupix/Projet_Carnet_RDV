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

    // Surcharge des opérateurs
    bool operator==(const LDCR&);               // Test d'égalité
    bool operator!=(const LDCR&);               // Test de différence

    LDCR& operator=(const LDCR&);               // Affectation

    RDV* operator[](int);

    // Méthodes
    void afficher(ostream& ost = cout) const;   // Afficher
    bool chercher(RDV* rdv) const;              // Chercher
    bool inserer(RDV* rdv);                     // Insertion
    int rechD(RDV* rdv) const;                  // Rech dichotomique
    int size(void) const;                       // Calcul de la taille
    void supprimer(RDV* rdv);                   // Suppression

};

// Fonctions globales
ostream& operator<<(ostream& ost, const LDCR& ldcr);

#endif // LDCR_H
