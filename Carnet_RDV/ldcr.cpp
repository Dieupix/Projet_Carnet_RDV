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



// ---------- Surcharge des opérateurs ----------
bool LDCR::operator==(const LDCR& l) {
    bool equals = true;
    auto crt = d_t, as = l.d_t;
    while (crt != nullptr and as != nullptr and equals) {
        equals = crt->rdv == as->rdv;
        crt = crt->d_suiv;
        as = as->d_suiv;
    }

    if ((crt == nullptr and as != nullptr) or (crt != nullptr and as == nullptr)) equals = false;

    return equals;
}
bool LDCR::operator!=(const LDCR& l) {
    return !this->operator==(l);
}

LDCR& LDCR::operator=(const LDCR& l) {
    if (l.d_t == nullptr) {
        auto crt = d_t;
        while (crt != nullptr) {
            auto as = crt;
            crt = crt->d_suiv;
            delete as;
        }
        d_t = nullptr;
    }
    else {
        auto as = l.d_t;
        auto crt = d_t;
        if (crt == nullptr) {
            d_t = new ChainonRDV(as->rdv);
            crt = d_t;
            as = as->d_suiv;
            while (as != nullptr) {
                auto n = new ChainonRDV(as->rdv);
                crt->d_suiv = n;
                n->d_prec = crt;
                crt = crt->d_suiv;
                as = as->d_suiv;
            }
        }
        else {
            while (crt->d_suiv != nullptr and as->d_suiv != nullptr) {
                crt->rdv = as->rdv;
                as = as->d_suiv;
                crt = crt->d_suiv;
            }
            crt->rdv = as->rdv;
            if (crt->d_suiv == nullptr and as->d_suiv != nullptr) {
                as = as->d_suiv;
                while (as != nullptr) {
                    auto n = new ChainonRDV(as->rdv);
                    crt->d_suiv = n;
                    n->d_prec = crt;
                    crt = crt->d_suiv;
                    as = as->d_suiv;
                }
                while (crt != nullptr) {
                    auto t = crt;
                    crt = crt->d_suiv;
                    t->d_prec->d_suiv = nullptr;
                    delete t;
                }
            }
            else {
                crt = crt->d_suiv;
                while (crt != nullptr) {
                    auto t = crt;
                    crt = crt->d_suiv;
                    t->d_prec->d_suiv = nullptr;
                    delete t;
                }
            }
        }
    }
    return *this;
}

RDV& LDCR::operator[](int i) const{
}



// ---------- Méthodes ----------
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

bool LDCR::chercher(RDV* val) const{
    bool found = false;
    auto crt = this->d_t;
    while (crt != nullptr and !found) {
        found = *crt->rdv == *val;
        crt = crt->d_suiv;
    }
    return found;
}

bool LDCR::inserer(RDV* val) {
    bool hasBeenInserted = true;
    auto n = new ChainonRDV(val);
    if (this->d_t == nullptr){
        this->d_t = n;
        ++this->Size;
    }else if(this->d_t->d_suiv == nullptr){
        if(*this->d_t->rdv == *val){
            delete n;
            hasBeenInserted = false;
        }
        else{
            if(*this->d_t->rdv < *val){
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
        while (crt->d_suiv != nullptr and *crt->rdv < *val)
            crt = crt->d_suiv;

        if(*crt->rdv == *val){
            delete n;
            return false;
        }

        if (*crt->rdv < *val) {
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

int LDCR::rechD(RDV* val) const
{
    int indCrt{0};
    auto crt = d_t;
    bool b{false};
    int indD = 0;
    int indF = Size;
    int m{0};
    while(!b && indD <= indF)
    {
        m = (indD+indF)/2;
        if(indCrt < m)
        {
            for(int i=indCrt;i<m;++i)
            {crt=crt->d_suiv;}
        }
        else
        {
            for(int i=indCrt;i>m;--i)
            {crt=crt->d_prec;}
        }
        if(*crt->rdv == *val){b=true;}
        else if(*crt->rdv < *val){indD=m+1;}
        else indF=m-1;
    }
    return b?indCrt:-1;
}

int LDCR::size(void) const {
    return this->Size;
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



// ---------- Fonctions globales ----------
ostream& operator<<(ostream& ost, const LDCR& l) {
    l.afficher(ost);
    return ost;
}
