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



// ---------- Surcharge des opérateurs ----------
bool LDCP::operator==(const LDCP& l) {
    bool equals = true;
    auto crt = d_t, as = l.d_t;
    while (crt != nullptr and as != nullptr and equals) {
        equals = crt->p == as->p;
        crt = crt->d_suiv;
        as = as->d_suiv;
    }

    if ((crt == nullptr and as != nullptr) or (crt != nullptr and as == nullptr)) equals = false;

    return equals;
}
bool LDCP::operator!=(const LDCP& l) {
    return !this->operator==(l);
}

LDCP& LDCP::operator=(const LDCP& l) {
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
            d_t = new ChainonPersonne(as->p);
            crt = d_t;
            as = as->d_suiv;
            while (as != nullptr) {
                auto n = new ChainonPersonne(as->p);
                crt->d_suiv = n;
                n->d_prec = crt;
                crt = crt->d_suiv;
                as = as->d_suiv;
            }
        }
        else {
            while (crt->d_suiv != nullptr and as->d_suiv != nullptr) {
                crt->p = as->p;
                as = as->d_suiv;
                crt = crt->d_suiv;
            }
            crt->p = as->p;
            if (crt->d_suiv == nullptr and as->d_suiv != nullptr) {
                as = as->d_suiv;
                while (as != nullptr) {
                    auto n = new ChainonPersonne(as->p);
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

Personne* LDCP::operator[](int) const{
}


// ---------- Méthodes ----------
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

bool LDCP::chercher(Personne* val) const{
    bool found = false;
    auto crt = this->d_t;
    while (crt != nullptr and !found) {
        found = *crt->p == *val;
        crt = crt->d_suiv;
    }
    return found;
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

int LDCP::rechD(Personne* val) const
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
        if(*crt->p == *val){b=true;}
        else if(*crt->p < *val){indD=m+1;}
        else indF=m-1;
    }
    return b?indCrt:-1;
}

int LDCP::size(void) const {
    return this->Size;
}

bool LDCP::supprimer(Personne* val) {
    bool hasBeenRemoved = true;
    if (this->d_t != nullptr) {
        auto crt = this->d_t;
        if (*crt->p == *val) {
            if(crt->p->getRDVList().size() != 0) hasBeenRemoved = false;
            else {
                if (crt->d_suiv == nullptr)
                    this->d_t = nullptr;
                else {
                    crt->d_suiv->d_prec = nullptr;
                    this->d_t = crt->d_suiv;
                }
                delete crt;
                --this->Size;
            }
        }
        else {
            while (*crt->p < *val and crt->d_suiv != nullptr)
                crt = crt->d_suiv;
            if (*crt->p == *val) {
                if(crt->p->getRDVList().size() != 0) hasBeenRemoved = false;
                else {
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
    return hasBeenRemoved;
}



// ---------- Fonctions globales ----------
ostream& operator<<(ostream& ost, const LDCP& l) {
    l.afficher(ost);
    return ost;
}
