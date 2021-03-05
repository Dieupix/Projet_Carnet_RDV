#include "chainonpersonne.h"

ChainonPersonne::ChainonPersonne(Personne* p)
{
    this->p = p;
    this->d_prec = nullptr;
    this->d_suiv = nullptr;
}
