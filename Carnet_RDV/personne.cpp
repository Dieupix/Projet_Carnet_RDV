#include "personne.h"

Personne::Personne(const string& firstName, const string& lastName, const string& phone, const string& email, const LDCR& rdvList){
    this->firstName = firstName;
    this->lastName = lastName;
    this->phone = phone;
    this->email = email;
    this->rdvList = rdvList;
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

void Personne::operator=(const Personne& p){
    this->firstName = p.firstName;
    this->lastName = p.lastName;
    this->phone = p.phone;
    this->email = p.email;
}

Personne::operator QString(void) const{
    return toQString();
}

// ---------- Méthodes ----------
void Personne::afficher(ostream& ost) const{
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
