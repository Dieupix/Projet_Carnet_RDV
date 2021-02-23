#include "personne.h"

Personne::Personne(const string& firstName, const string& lastName, const string& phone, const string& email){
    this->firstName = firstName;
    this->lastName = lastName;
    this->phone = phone;
    this->email = email;
}

QString Personne::toQString(void) const{
    return QString::fromStdString(lastName + " " + firstName + " - " + phone + " - " + email);
}

string Personne::getFirstName(void) const{
    return this->firstName;
}
string Personne::getLastName(void) const{
    return this->lastName;
}
string Personne::getPhone(void) const{
    return this->phone;
}
string Personne::getEmail(void) const{
    return this->email;
}

void Personne::afficher(ostream &ost) const{
    ost << lastName << " " << firstName << " - " << phone << " - " << email;
}

ostream& operator<<(ostream& ost, const Personne& p){
    p.afficher(ost);
    return ost;
}
