#include "rdv.h"

RDV::RDV(const string& name, const vector<char>& date, const string& timeStart, const string& timeEnd, const vector<Personne*>& membersList)
{
    this->name = name;
    this->date = date;
    this->timeStart = timeStart;
    this->timeEnd = timeEnd;
    this->membersList = membersList;
}

// ---------- Surcharge d'opérateurs ----------
bool RDV::operator>(const RDV& rdv) const{

}
bool RDV::operator>=(const RDV& rdv) const{

}
bool RDV::operator<(const RDV& rdv) const{

}
bool RDV::operator<=(const RDV& rdv) const{

}
bool RDV::operator==(const RDV& rdv) const{
    return QString::fromStdString(this->name + dateToString() + this->timeStart + this->timeEnd) == QString::fromStdString(rdv.name +rdv.dateToString() + rdv.timeStart + rdv.timeEnd);
}
bool RDV::operator!=(const RDV& rdv) const{
    return QString::fromStdString(this->name + dateToString() + this->timeStart + this->timeEnd) != QString::fromStdString(rdv.name +rdv.dateToString() + rdv.timeStart + rdv.timeEnd);
}

void RDV::operator=(const RDV& rdv){
    this->name = rdv.name;
    this->date = rdv.date;
    this->timeStart = rdv.timeStart;
    this->timeEnd = rdv.timeEnd;
    this->membersList = rdv.membersList;
}

RDV::operator QString(void) const{
    return toQString();
}

// ---------- Méthodes ----------
void RDV::afficher(ostream& ost = cout) const{
    ost << name << " - Le " << dateToString() << " - De " << timeStart << " a " << timeEnd << endl;
    ost << "Participant" << (membersList.size() == 1 ? "" : "s") << " (" << membersList.size() << ") :" << endl;
    if(membersList.size() == 0) ost << "Aucun participant" << endl;
    else for(auto p : membersList) ost << "* " << *p << endl;
}

string RDV::dateToString(void) const{
    string s = "";
    s += date[0]; s += date[1]; s += '/'; s += date[2]; s += date[3]; s += '/'; s += date[4]; s += date[5]; s += date[6]; s += date[7];
    return s;
}

QString RDV::toQString(void) const{
    QString str = QString::fromStdString(name + " - Le " + dateToString() + " - De " + timeStart + " à " + timeEnd + "\n");
    str += "Participant";
    str += membersList.size() == 1 ? "" : "s";
    str += " (";
    str += QString::number(membersList.size());
    str += ") :\n";
    for(auto p : membersList)
        str += *p + "\n";
    return str;
}

// ---------- Getteurs ----------
const string& RDV::getName(void) const{
    return this->name;
}
const string& RDV::getTimeStart(void) const{
    return this->timeStart;
}
const string& RDV::getTimeEnd(void) const{
    return this->timeEnd;
}
const vector<char>& RDV::getDate(void) const{
    return this->date;
}
vector<Personne*>& RDV::getMembersList(void) {
    return this->membersList;
}

// ---------- Setteurs ----------
void RDV::setName(const string& name){
    this->name = name;
}
void RDV::setTimeStart(const string& timeStart){
    this->timeStart = timeStart;
}
void RDV::setTimeEnd(const string& timeEnd){
    this->timeEnd = timeEnd;
}
void RDV::setDate(const vector<char>& date){
    this->date = date;
}

// ---------- Fonctions globales ----------
ostream& operator<<(ostream& ost, const RDV& rdv){
    rdv.afficher(ost);
    return ost;
}
