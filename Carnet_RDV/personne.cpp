#include "personne.h"

Personne::Personne(const string& firstName, const string& lastName, const string& phone, const string& email, const vector<RDV*>& rdvList){
    this->firstName = firstName;
    this->lastName = lastName;
    for(unsigned i = 0; i < this->lastName.length(); ++i) this->lastName[i] = toupper(this->lastName[i]);
    this->phone = phone;
    this->email = email;
    this->rdvList = rdvList;
}



// ---------- Surcharge des opérateurs ----------
bool Personne::operator>(const Personne& p) const{
    return compareTo(p) < 0;
}
bool Personne::operator>=(const Personne& p) const{
    return compareTo(p) <= 0;
}
bool Personne::operator<(const Personne& p) const{
    return compareTo(p) > 0;
}
bool Personne::operator<=(const Personne& p) const{
    return compareTo(p) >= 0;
}
bool Personne::operator==(const Personne& p) const{
    return compareTo(p) == 0;
}
bool Personne::operator!=(const Personne& p) const{
    return compareTo(p) != 0;
}

void Personne::operator=(const Personne& p){
    this->firstName = p.firstName;
    this->lastName = p.lastName;
    this->phone = p.phone;
    this->email = p.email;
}

Personne::operator QString(void) const{
    return toQString();
}
Personne::operator string(void) const{
    return toString();
}



// ---------- Méthodes ----------
// On ajoute un RDV à la personne si elle n'est pas présente à un autre RDV au même moment
bool Personne::addRDV(RDV* rdv)
{
    for(unsigned i = 0; i < rdvList.size(); ++i)
    {
        if(rdv->date == rdvList[i]->date)
        {
            if(rdvList[i]->timeStart < rdv->timeEnd)
                if(rdvList[i]->timeStart >= rdv->timeStart || rdvList[i]->timeEnd > rdv->timeStart)
                    return false;
        }
    }

    unsigned ind{0};
    while(ind < rdvList.size() && *rdvList[ind] < *rdv) ++ind;
    if(rdvList.size() == 0)
        rdvList.push_back(rdv);

    else{
        rdvList.push_back(rdvList[rdvList.size() - 1]);
        for(unsigned i = rdvList.size() - 2; i > ind; --i)
            rdvList[i] = rdvList[i - 1];

        rdvList[ind] = rdv;
    }
    return true;
}

void Personne::afficher(ostream& ost) const{
    ost << toString();
}

// Retourn 1 si p > this, -1 si p < this, 0 sinon
int Personne::compareTo(const Personne& p) const{
    string thisLF = lastName + firstName, pLF = p.lastName + p.firstName;
    for(unsigned i = 0; i < thisLF.length(); ++i) thisLF[i] = toupper(thisLF[i]);
    for(unsigned i = 0; i < pLF.length(); ++i) pLF[i] = toupper(pLF[i]);

    if(thisLF > pLF) return -1;
    else if(thisLF < pLF) return 1;
    else return 0;
}

QString Personne::rdvToQString(void) const{
    return QString::fromStdString(rdvToString());
}

string Personne::rdvToString(void) const{
    string s = QString(QObject::tr("Rendez-vous", "Appointment%1", rdvList.size())).toStdString() + " (" + to_string(rdvList.size()) + ") : \n";
    if (rdvList.size() == 0) s += QString(QObject::tr("Aucun rendez-vous", "Any appointment")).toStdString() + "\n";
    else for(unsigned i = 0; i < rdvList.size(); ++i) s += rdvList[i]->toString() + "\n";
    return s;
}

bool Personne::removeRDV(RDV* rdv)
{
    unsigned i{0};
    bool found{false};
    while(i < rdvList.size() && !found){
        if(*rdvList[i] == *rdv) found = true;
        else ++i;
    }

    if(rdvList.size() == 0) return false;
    else if(found){
        for(unsigned j = i; j < rdvList.size() - 1; ++j)
            rdvList[j] = rdvList[j + 1];

        rdvList.pop_back();
        return true;
    }
    return false;
}

QString Personne::toQString(void) const{
    return QString::fromStdString(toString());
}

string Personne::toString(void) const{
    return lastName + " " + firstName + " - " + phone + " - " + email;
}



// ---------- Getteurs ----------
const string& Personne::getFirstName(void) const{
    return this->firstName;
}
const string& Personne::getLastName(void) const{
    return this->lastName;
}
const string& Personne::getPhone(void) const{
    return this->phone;
}
const string& Personne::getEmail(void) const{
    return this->email;
}
const vector<RDV*>& Personne::getRDVList(void) const{
    return this->rdvList;
}



// ---------- Setteurs ----------
void Personne::setFirstName(const string& firstName){
    this->firstName = firstName;
}
void Personne::setLastName(const string& lastName){
    this->lastName = lastName;
    for(unsigned i = 0; i < this->lastName.length(); ++i) this->lastName[i] = toupper(this->lastName[i]);
}
void Personne::setPhone(const string& phone){
    this->phone = phone;
}
void Personne::setEmail(const string& email){
    this->email = email;
}
void Personne::setRDVList(const vector<RDV*>& rdvList){
    this->rdvList = rdvList;
}



// ---------- Fonctions globales ----------
ostream& operator<<(ostream& ost, const Personne& p){
    p.afficher(ost);
    return ost;
}
