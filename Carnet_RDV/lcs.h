#ifndef LCS_H
#define LCS_H

#include "chainonpersonne.h"

class LCS
{
public:
    LCS(void);                       // Constructeur
    LCS(const LCS& l);           // Constructeur par recopie
    ~LCS(void);                      // Destructeur
    int taille(void) const;          // Calcul de la taille
    void inserer(Personne*);    // Insertion
    void supprimer(Personne*);  // Suppression
    void couper(Personne*);     // Couper
    bool chercher(Personne*);   // Chercher
    void fusion(const LCS&);  // Fusion
    void afficher(ostream&) const;
private:
    ChainonPersonne* d_t;
    int size;
};

#endif // LCS_H
