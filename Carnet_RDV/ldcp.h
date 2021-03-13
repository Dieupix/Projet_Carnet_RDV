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
private:
    ChainonPersonne* d_t;
    int Size;

public:
    LDCP(void);                                 // Constructeur
    LDCP(const LDCP& l);                        // Constructeur par recopie
    ~LDCP(void);                                // Destructeur

    // Surcharges des opérateurs
    bool operator==(const LDCP&);               // Test d'égalité
    bool operator!=(const LDCP&);               // Test de différence

    LDCP& operator=(const LDCP&);               // Affectation

    Personne* operator[](int) const;

    // Méthodes
    void afficher(ostream& ost = cout) const;   // Afficher
    bool chercher(Personne* p) const;           // Chercher
    bool inserer(Personne* p);                  // Insertion
    int rechD(Personne* p) const;               // Recherche dichotomique
    int size(void) const;                       // Calcul de la taille
    bool supprimer(Personne* p);                // Suppression

};

// Fonctions globales
ostream& operator<<(ostream& ost, const LDCP& ldcp);

#endif // LDCP_H
