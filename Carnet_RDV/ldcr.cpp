#include "ldcr.h"

LDCR::LDCR(void) {
    this->d_t = nullptr;
    this->Size = 0;
}

LDCR::LDCR(const LDCR& l) {
    if (l.d_t == nullptr) this->d_t = nullptr;
    else {
        auto lc = l.d_t;
        this->d_t = new ChainonRDV(lc->rdv);
        auto crt = this->d_t;
        while (lc->d_suiv != nullptr) {
            auto as = new ChainonRDV(lc->d_suiv->rdv);
            as->d_prec = crt;
            crt->d_suiv = as;
            crt = as;
            lc = lc->d_suiv;
        }
        this->Size = l.Size;
    }
}

LDCR::~LDCR(void) {
    auto crt = this->d_t;
    while (crt != nullptr) {
        auto as = crt;
        crt = crt->d_suiv;
        delete as;
    }
}

// ---------- Surcharge d'opérateurs ----------


// ---------- Méthodes ----------
int LDCR::size(void) const {
    return this->Size;
}

void LDCR::inserer(RDV* val) {
    auto n = new ChainonRDV(val);
    if (this->d_t == nullptr){
        this->d_t = n;
        ++this->Size;
    }
    else {
        auto crt = this->d_t;
        while (crt->d_suiv != nullptr and *crt->rdv < *val)
            crt = crt->d_suiv;
        if (*crt->rdv < *val) {
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

void LDCR::supprimer(RDV* val) {
    if (this->d_t != nullptr) {
        auto crt = this->d_t;
        if (*crt->rdv == *val) {
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
            while (*crt->rdv < *val and crt->d_suiv != nullptr)
                crt = crt->d_suiv;
            if (*crt->rdv == *val) {
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

void LDCR::couper(RDV* val) {
    auto crt = this->d_t;
    while (crt != nullptr and *crt->rdv < *val) crt = crt->d_suiv;
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

bool LDCR::chercher(RDV* val) {
    bool found = false;
    auto crt = this->d_t;
    while (crt != nullptr and !found) {
        found = *crt->rdv == *val;
        crt = crt->d_suiv;
    }
    return found;
}

void LDCR::afficher(ostream& ost) const {
    auto crt = this->d_t;
    if (crt == nullptr) ost << "Liste vide";
    else {
        int i = 0;
        while (crt->d_suiv != nullptr) {
            ost << *crt->rdv << " -> ";
            crt = crt->d_suiv;
            i++;
            if (i == 10) {
                i = 0;
                ost << endl;
            }
        }
        ost << *crt->rdv;
    }
}

// ---------- Fonctions globales ----------
ostream& operator<<(ostream& ost, const LDCR& l) {
    l.afficher(ost);
    return ost;
}
