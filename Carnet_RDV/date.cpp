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

bool Date::operator==(const Date&) const{
    return NULL;
}
bool Date::operator!=(const Date&) const{
    return NULL;
}
bool Date::operator>(const Date&) const{
    return NULL;
}
bool Date::operator>=(const Date&) const{
    return NULL;
}
bool Date::operator<(const Date&) const{
    return NULL;
}
bool Date::operator<=(const Date&) const{
    return NULL;
}

Date Date::operator+(const Date&) const{
    return Date();
}
Date& Date::operator+=(const Date&){
    return *this;
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


// ---------- Setteurs ----------


// ---------- Fonctions globales ----------
ostream& operator<<(ostream& ost, const Date& d){
    d.afficher(ost);
    return ost;
}
