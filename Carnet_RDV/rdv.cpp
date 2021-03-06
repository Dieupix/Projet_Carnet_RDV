#include "rdv.h"

RDV::RDV(const string& name, const Date& date, const string& timeStart, const string& timeEnd, const vector<Personne*>& membersList)
{
    this->name = name;
    this->date = date;
    this->timeStart = timeStart;
    this->timeEnd = timeEnd;
    this->membersList = membersList;
}

// ---------- Surcharge d'opérateurs ----------
bool RDV::operator>(const RDV& rdv) const{
    return QString::fromStdString(dateToString()) > QString::fromStdString(rdv.dateToString());
}
bool RDV::operator>=(const RDV& rdv) const{
    return QString::fromStdString(dateToString()) >= QString::fromStdString(rdv.dateToString());
}
bool RDV::operator<(const RDV& rdv) const{
    return QString::fromStdString(dateToString()) < QString::fromStdString(rdv.dateToString());
}
bool RDV::operator<=(const RDV& rdv) const{
    return QString::fromStdString(dateToString()) <= QString::fromStdString(rdv.dateToString());
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
RDV::operator string(void) const{
    return toString();
}

// ---------- Méthodes ----------
void RDV::afficher(ostream& ost) const{
    ost << name << " - Le " << dateToString() << " - De " << timeStart << " a " << timeEnd << endl;
    ost << "Participant" << (membersList.size() == 1 ? "" : "s") << " (" << membersList.size() << ") :" << endl;
    ost << participantsToString() << endl;
}

string RDV::participantsToString(void) const {
    string s = "";
    if (membersList.size() == 0) s = "Aucun participant";
    else for(auto p : membersList) s += p->toString() + "\n";
    return s;
}

/*string RDV::dateToString(void) const{
    string s = "";
    s += date[0]; s += date[1]; s += '/'; s += date[2]; s += date[3]; s += '/'; s += date[4]; s += date[5]; s += date[6]; s += date[7];
    return s;
}*/

QString RDV::toQString(void) const{
    return QString::fromStdString(toString());
}

string RDV::toString(void) const{
    string s = name + " - Le " + dateToString() + " - De " + timeStart + " à " + timeEnd + "\nParticipant" + (membersList.size() == 1 ? "" : "s") + " (";
    s += membersList.size();
    s += ") :\n" + participantsToString();
    return s;
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
Date& RDV::getDate(void){
    return this->date;
}
vector<Personne*>& RDV::getMembersList(void){
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

// ---------- Fonctions globales ----------
ostream& operator<<(ostream& ost, const RDV& rdv){
    rdv.afficher(ost);
    return ost;
}
