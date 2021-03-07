#include "date.h"

Date::Date(void)
{
    this->day = this->month = 1;
    this->year = 1970;
}

Date::Date(const unsigned& day, const unsigned& month, const unsigned& year){
    this->day = day;
    this->month = month;
    this->year = year;
}

// ---------- Surchargde des opérateurs ----------
// Commentaires à supprimer après validation
// TODO - Utiliser compareTo() pour les opérateurs binaires
bool Date::operator==(const Date& d) const{
}
bool Date::operator!=(const Date& d) const{
}
bool Date::operator>(const Date& d) const{
}
bool Date::operator>=(const Date& d) const{
}
bool Date::operator<(const Date& d) const{
}
bool Date::operator<=(const Date& d) const{
}

Date Date::operator+(const Date& d) const{
}
Date& Date::operator+=(const Date& d){
}
Date Date::operator-(const Date& d) const{
}
Date& Date::operator-=(const Date& d){
}

Date Date::operator++(int){
}
Date Date::operator--(int){
}

Date& Date::operator++(void){
}
Date& Date::operator--(void){
}

void Date::operator=(const Date&) const{
}

Date::operator QString(void) const{
    return QString::fromStdString(toString());
}
Date::operator string(void) const{
    return toString();
}


// ---------- Méthodes ----------
void Date::afficher(ostream& ost) const{
}

// Commentaires à supprimer après validation
// TODO - Retourne 1 si d > this, -1 si d < this, 0 sinon
int Date::compareTo(const Date& d) const{
}

bool Date::leap(void) const{
    return (year % 4 == 0 and year % 10 != 0) or year % 400;
}

QString Date::toQString(void) const{
    return QString::fromStdString(toString());
}

string Date::toString(void) const{
    string s = ""; s += day; s += "/"; s += month; s += "/"; s += year;
    return s;
}

// ---------- Getteurs ----------
// Commentaires à supprimer après validation
// TODO - Remplir les getteurs

// ---------- Setteurs ----------
// Commentaires à supprimer après validation
// TODO - Remplir les setteurs

// ---------- Fonctions globales ----------
ostream& operator<<(ostream& ost, const Date& d){
    d.afficher(ost);
    return ost;
}
