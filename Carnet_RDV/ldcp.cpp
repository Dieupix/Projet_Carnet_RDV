#include "ldcp.h"

LDCP::LDCP(void) {
    this->d_t = nullptr;
    this->Size = 0;
}

LDCP::LDCP(const LDCP& l) {
    if (l.d_t == nullptr) this->d_t = nullptr;
    else {
        auto lc = l.d_t;
        this->d_t = new ChainonPersonne(lc->p);
        auto crt = this->d_t;
        while (lc->d_suiv != nullptr) {
            auto as = new ChainonPersonne(lc->d_suiv->p);
            as->d_prec = crt;
            crt->d_suiv = as;
            crt = as;
            lc = lc->d_suiv;
        }
        this->Size = l.Size;
    }
}

LDCP::~LDCP(void) {
    auto crt = this->d_t;
    while (crt != nullptr) {
        auto as = crt;
        crt = crt->d_suiv;
        delete as;
    }
}

// ---------- Surcharge d'opérateurs ----------


// ---------- Méthodes ----------
int LDCP::size(void) const {
    return this->Size;
}

bool LDCP::inserer(Personne* val) {
    bool hasBeenInserted = true;
    auto n = new ChainonPersonne(val);
    if (this->d_t == nullptr){
        this->d_t = n;
        ++this->Size;
    }else if(this->d_t->d_suiv == nullptr){
        if(*this->d_t->p == *val){
            delete n;
            hasBeenInserted = false;
        }
        else{
            if(*this->d_t->p < *val){
                this->d_t->d_suiv = n;
                n->d_prec = this->d_t;
            }else{
                auto as = this->d_t;
                this->d_t = n;
                as->d_prec = n;
                n->d_suiv = as;
            }
            ++this->Size;
        }
    }
    else {
        auto crt = this->d_t;
        while (crt->d_suiv != nullptr and *crt->p < *val){
            if(*crt->p == *val){
                delete n;
                return false;
            }
            crt = crt->d_suiv;
        }
        if (*crt->p < *val) {
            n->d_prec = crt;
            crt->d_suiv = n;
        }
        else {
            crt->d_prec->d_suiv = n;
            n->d_prec = crt->d_prec;
            n->d_suiv = crt;
            crt->d_prec = n;
        }
        ++this->Size;
    }
    return hasBeenInserted;
}

void LDCP::supprimer(Personne* val) {
    if (this->d_t != nullptr) {
        auto crt = this->d_t;
        if (*crt->p == *val) {
            if (crt->d_suiv == nullptr)
                this->d_t = nullptr;
            else {
                crt->d_suiv->d_prec = nullptr;
                this->d_t = crt->d_suiv;
            }
            delete crt;
            --this->Size;
        }
        else {
            while (*crt->p < *val and crt->d_suiv != nullptr)
                crt = crt->d_suiv;
            if (*crt->p == *val) {
                if (crt->d_suiv == nullptr)
                    crt->d_prec->d_suiv = nullptr;
                else {
                    crt->d_prec->d_suiv = crt->d_suiv;
                    crt->d_suiv->d_prec = crt->d_prec;
                }
                delete crt;
                --this->Size;
            }
        }
    }
}

void LDCP::couper(Personne* val) {
    auto crt = this->d_t;
    while (crt != nullptr and *crt->p < *val) crt = crt->d_suiv;
    if (crt != nullptr) {
        if (crt == this->d_t) {
            auto as = crt;
            crt = crt->d_suiv;
            this->d_t = nullptr;
            delete as;
        }
        else {
            auto as = crt;
            crt = crt->d_suiv;
            as->d_prec->d_suiv = nullptr;
            delete as;
        }
        while (crt != nullptr) {
            auto as = crt;
            crt = crt->d_suiv;
            delete as;
        }
    }
}

bool LDCP::chercher(Personne* val) {
    bool found = false;
    auto crt = this->d_t;
    while (crt != nullptr and !found) {
        found = *crt->p == *val;
        crt = crt->d_suiv;
    }
    return found;
}

void LDCP::afficher(ostream& ost) const {
    auto crt = this->d_t;
    if (crt == nullptr) ost << "Liste vide";
    else {
        int i = 0;
        while (crt->d_suiv != nullptr) {
            ost << *crt->p << " -> ";
            crt = crt->d_suiv;
            i++;
            if (i == 10) {
                i = 0;
                ost << endl;
            }
        }
        ost << *crt->p;
    }
}

// ---------- Fonctions globales ----------
ostream& operator<<(ostream& ost, const LDCP& l) {
    l.afficher(ost);
    return ost;
}
