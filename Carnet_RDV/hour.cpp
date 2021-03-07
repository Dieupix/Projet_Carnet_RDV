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
// Commentaires à supprimer après validation
// TODO - Utiliser compareTo() pour les opérateurs de comparaison
bool Hour::operator==(const Hour& h) const{
}
bool Hour::operator!=(const Hour& h) const{
}
bool Hour::operator>(const Hour& h) const{
}
bool Hour::operator>=(const Hour& h) const{
}
bool Hour::operator<(const Hour& h) const{
}
bool Hour::operator<=(const Hour& h) const{
}

// Commentaires à supprimer après validation
// TODO - Utiliser add() et remove() pour les opérateurs d'addition
Hour Hour::operator+(const Hour& h) const{
}
Hour& Hour::operator+=(const Hour& h){
}
Hour Hour::operator-(const Hour& h) const{
}
Hour& Hour::operator-=(const Hour& h){
}

Hour Hour::operator++(int){
}
Hour Hour::operator--(int){
}

Hour& Hour::operator++(void){
}
Hour& Hour::operator--(void){
}

void Hour::operator=(const Hour&) const{
}

Hour::operator QString(void) const{
    return QString::fromStdString(toString());
}
Hour::operator string(void) const{
    return toString();
}

// ---------- Méthodes ----------
void Hour::add(const Hour& h){
}

void Hour::afficher(ostream& ost) const{
}

// Commentaires à supprimer après validation
// TODO - Retourne 1 si h > this, -1 si h < this, 0 sinon
int Hour::compareTo(const Hour& h) const{
}

void Hour::remve(const Hour& h){
}

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

// ---------- Getteurs ----------


// ---------- Setteurs ----------


// ---------- Fonctions globales ----------
ostream& operator<<(ostream& ost, const Hour& h){
    h.afficher(ost);
    return ost;
}
