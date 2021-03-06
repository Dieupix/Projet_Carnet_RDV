#include "hour.h"

Hour::Hour(void)
{
    this->second = this->minute = this->hour = 0;
}

Hour::Hour(const unsigned& hour, const unsigned& minute, const unsigned& second){
    this->second = second;
    this->minute = minute;
    this->hour = hour;
}

// ---------- Surchargde des opérateurs ----------
bool Hour::operator==(const Hour&) const{
    return NULL;
}
bool Hour::operator!=(const Hour&) const{
    return NULL;
}
bool Hour::operator>(const Hour&) const{
    return NULL;
}
bool Hour::operator>=(const Hour&) const{
    return NULL;
}
bool Hour::operator<(const Hour&) const{
    return NULL;
}
bool Hour::operator<=(const Hour&) const{
    return NULL;
}

Hour Hour::operator+(const Hour&) const{
    return Hour();
}
Hour& Hour::operator+=(const Hour&){
    return *this;
}

void Hour::operator=(const Hour&) const{
}

void Hour::afficher(ostream& ost) const{
}

Hour::operator QString(void) const{
    return QString::fromStdString(toString());
}
Hour::operator string(void) const{
    return toString();
}

// ---------- Méthodes ----------


// ---------- Getteurs ----------
QString Hour::toQString(void) const{
    return QString::fromStdString(toString());
}

string Hour::toString(void) const{
    string s = ""; s += hour; s += "h"; s += minute;
    if(second != 0){
        s += "m";
        s += second;
    }
    return s;
}


// ---------- Setteurs ----------


// ---------- Fonctions globales ----------
ostream& operator<<(ostream& ost, const Hour& h){
    h.afficher(ost);
    return ost;
}
