#include "personne.h"

Personne::Personne(const string& firstName, const string& lastName, const string& phone, const string& email){
    this->firstName = firstName;
    this->lastName = lastName;
    this->phone = phone;
    this->email = email;
}

// ---------- Surcharge d'opérateurs ----------

bool Personne::operator>(const Personne& p) const{
    return QString::fromStdString(this->lastName + this->firstName) > QString::fromStdString(p.lastName + p.firstName);
}
bool Personne::operator>=(const Personne& p) const{
    return QString::fromStdString(this->lastName + this->firstName) >= QString::fromStdString(p.lastName + p.firstName);
}
bool Personne::operator<(const Personne& p) const{
    return QString::fromStdString(this->lastName + this->firstName) < QString::fromStdString(p.lastName + p.firstName);
}
bool Personne::operator<=(const Personne& p) const{
    return QString::fromStdString(this->lastName + this->firstName) <= QString::fromStdString(p.lastName + p.firstName);
}
bool Personne::operator==(const Personne& p) const{
    return QString::fromStdString(this->lastName + this->firstName) == QString::fromStdString(p.lastName + p.firstName);
}
bool Personne::operator!=(const Personne& p) const{
    return QString::fromStdString(this->lastName + this->firstName) != QString::fromStdString(p.lastName + p.firstName);
}

Personne::operator QString(void) const{
    return QString::fromStdString(lastName + " " + firstName + " - " + phone + " - " + email);
}

// ---------- Méthodes ----------
void Personne::afficher(ostream &ost = cout) const{
    ost << lastName << " " << firstName << " - " << phone << " - " << email;
}

QString Personne::toQString(void) const{
    return QString::fromStdString(lastName + " " + firstName + " - " + phone + " - " + email);
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

// ---------- Setteurs ----------
void Personne::setFirstName(const string& firstName){
    this->firstName = firstName;
}
void Personne::setLastName(const string& lastName){
    this->lastName = lastName;
}
void Personne::setPhone(const string& phone){
    this->phone = phone;
}
void Personne::setEmail(const string& email){
    this->email = email;
}

// ---------- Fonctions globales ----------
ostream& operator<<(ostream& ost, const Personne& p){
    p.afficher(ost);
    return ost;
}
