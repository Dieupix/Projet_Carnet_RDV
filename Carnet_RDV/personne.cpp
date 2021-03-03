#include "personne.h"

Personne::Personne(const string& firstName, const string& lastName, const string& phone, const string& email){
    this->firstName = firstName;
    this->lastName = lastName;
    this->phone = phone;
    this->email = email;
}

Personne::operator QString(void) const{
    return QString::fromStdString(lastName + " " + firstName + " - " + phone + " - " + email);
}

QString Personne::toQString(void) const{
    return QString::fromStdString(lastName + " " + firstName + " - " + phone + " - " + email);
}

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

void Personne::afficher(ostream &ost = cout) const{
    ost << lastName << " " << firstName << " - " << phone << " - " << email;
}

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

ostream& operator<<(ostream& ost, const Personne& p){
    p.afficher(ost);
    return ost;
}
