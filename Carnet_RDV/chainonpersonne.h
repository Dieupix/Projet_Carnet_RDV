#ifndef CHAINONPERSONNE_H
#define CHAINONPERSONNE_H

#include "personne.h"

class ChainonPersonne
{
    friend class LCS;
private:
    ChainonPersonne(Personne*);

    Personne* p;
    ChainonPersonne* d_prec, * d_suiv;

};

#endif // CHAINONPERSONNE_H
