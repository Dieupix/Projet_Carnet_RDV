#include "rdv.h"

RDV::RDV(const string& name, const Date& date, const Hour& timeStart, const Hour& timeEnd, const vector<Personne*>& membersList)
{
    this->name = name;
    this->date = date;
    this->timeStart = timeStart;
    this->timeEnd = timeEnd;
    this->membersList = membersList;
}

// ---------- Surcharge des opérateurs ----------
bool RDV::operator>(const RDV& rdv) const{
    return QString::fromStdString(date) > QString::fromStdString(rdv.date);
}
bool RDV::operator>=(const RDV& rdv) const{
    return QString::fromStdString(date) >= QString::fromStdString(rdv.date);
}
bool RDV::operator<(const RDV& rdv) const{
    return QString::fromStdString(date) < QString::fromStdString(rdv.date);
}
bool RDV::operator<=(const RDV& rdv) const{
    return QString::fromStdString(date) <= QString::fromStdString(rdv.date);
}
bool RDV::operator==(const RDV& rdv) const{
    return QString::fromStdString(name + date.toString() + timeStart.toString() + timeEnd.toString()) == QString::fromStdString(rdv.name + rdv.date.toString() + rdv.timeStart.toString() + rdv.timeEnd.toString());
}
bool RDV::operator!=(const RDV& rdv) const{
    return QString::fromStdString(name + date.toString() + timeStart.toString() + timeEnd.toString()) != QString::fromStdString(rdv.name +rdv.date.toString() + rdv.timeStart.toString() + rdv.timeEnd.toString());
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
// Commentaire à supprimer après validation
// TODO - On ajoute un participant à un RDV s'il n'y est pas déjà présent, puis ne dois pas être présent à un autre RDV au même moment
// Si la personne peut être ajoutée, on ajoute le RDV auquel elle est ajoutée dans sa liste de RDV personnelle
bool RDV::addMember(Personne* p){
}

void RDV::afficher(ostream& ost) const{
    ost << toString();
}

string RDV::participantsToString(void) const {
    string s = "";
    if (membersList.size() == 0) s = "Aucun participant\n";
    else for(auto p : membersList) s += p->toString() + "\n";
    return s;
}

// Commentaire à supprimer après validation
// TODO - Quand on enlève un participant, il n'est pas << delete >> !
bool RDV::removeMember(Personne* p){
}

QString RDV::toQString(void) const{
    return QString::fromStdString(toString());
}

string RDV::toString(void) const{
    string s = name + " - Le " + date.toString() + " - De " + timeStart.toString() + " à " + timeEnd.toString() + "\nParticipant" + (membersList.size() == 1 ? "" : "s") + " (";
    s += membersList.size();
    s += ") :\n" + participantsToString();
    return s;
}

// ---------- Getteurs ----------
const string& RDV::getName(void) const{
    return this->name;
}
Hour& RDV::getTimeStart(void){
    return this->timeStart;
}
Hour& RDV::getTimeEnd(void){
    return this->timeEnd;
}
Date& RDV::getDate(void){
    return this->date;
}
const vector<Personne*>& RDV::getMembersList(void) const{
    return this->membersList;
}

// ---------- Setteurs ----------
void RDV::setName(const string& name){
    this->name = name;
}
void RDV::setTimeStart(const Hour& timeStart){
    this->timeStart = timeStart;
}
void RDV::setTimeEnd(const Hour& timeEnd){
    this->timeEnd = timeEnd;
}
void RDV::setDate(const Date& date){
}
void RDV::setMembersList(const vector<Personne*>& membersList){
}

// ---------- Fonctions globales ----------
ostream& operator<<(ostream& ost, const RDV& rdv){
    rdv.afficher(ost);
    return ost;
}
