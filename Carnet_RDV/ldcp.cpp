#include "ldcp.h"

LDCP::LDCP(void) {
    this->d_t = nullptr;
    this->size = 0;
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
        this->size = l.size;
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

int LDCP::taille(void) const {
    return this->size;
}

void LDCP::inserer(Personne* val) {
    auto n = new ChainonPersonne(val);
    if (this->d_t == nullptr){
        this->d_t = n;
        ++this->size;
    }
    else if (*this->d_t->p > *val) {
        n->d_suiv = this->d_t;
        this->d_t->d_prec = n;
        n->d_prec = nullptr;
        this->d_t = n;
        ++this->size;
    }
    else {
        auto crt = this->d_t;
        while (crt->d_suiv != nullptr and *crt->p < *val)
            crt = crt->d_suiv;
        if (*crt->p < *val) {
            n->d_prec = crt;
            crt->d_suiv = n;
            n->d_suiv = nullptr;
        }
        else {
            crt->d_prec->d_suiv = n;
            n->d_prec = crt->d_prec;
            n->d_suiv = crt;
            crt->d_prec = n;
        }
    }
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
            --this->size;
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
                --this->size;
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

void LDCP::afficher(ostream& ost = cout) const {
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

ostream& operator<<(ostream& ost, const LDCP& l) {
    l.afficher(ost);
    return ost;
}
