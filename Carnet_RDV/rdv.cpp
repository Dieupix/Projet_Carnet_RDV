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
    return compareTo(rdv) < 0;
}
bool RDV::operator>=(const RDV& rdv) const{
    return compareTo(rdv) <= 0;
}
bool RDV::operator<(const RDV& rdv) const{
    return compareTo(rdv) > 0;
}
bool RDV::operator<=(const RDV& rdv) const{
    return compareTo(rdv) >= 0;
}
bool RDV::operator==(const RDV& rdv) const{
    return compareTo(rdv) == 0;
}
bool RDV::operator!=(const RDV& rdv) const{
    return compareTo(rdv) != 0;
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
// Commentaires à supprimer après validation
// TODO - On ajoute un participant à un RDV s'il n'y est pas déjà présent, puis ne dois pas être présent à un autre RDV au même moment
// Si la personne peut être ajoutée, on ajoute le RDV auquel elle est ajoutée dans sa liste de RDV personnelle
bool RDV::addMember(Personne* p){
}

void RDV::afficher(ostream& ost) const{
    ost << toString();
}

// Retourne 1 si r > à this, -1 si r < this, 0 sinon
int RDV::compareTo(const RDV& r ) const
{
   if(name > r.name) return -1;
   else if(name < r.name) return 1;
   else if(date > r.date) return -1;
   else if(date < r.date) return 1;
   else if(timeStart > r.timeStart) return -1;
   else if(timeStart < r.timeStart) return 1;
   else if(timeEnd > r.timeEnd)  return -1;
   else if(timeEnd < r.timeEnd) return 1;
   else return 0;
}

QString RDV::participantsToQString(void) const{
    return QString::fromStdString(participantsToString());
}

string RDV::participantsToString(void) const{
    string s = "Participant" + (string) (membersList.size() == 1 ? "" : "s") + " " +
            "(" + to_string(membersList.size()) + ") :\n";
    if (membersList.size() == 0) s += "Aucun participant\n";
    else for(auto p : membersList) s += p->toString() + "\n";
    return s;
}

// Commentaires à supprimer après validation
// TODO - Quand on enlève un participant, il n'est pas << delete >> !
bool RDV::removeMember(Personne* p){
}

QString RDV::toQString(void) const{
    return QString::fromStdString(toString());
}

string RDV::toString(void) const{
    string s = name +
            " - Le " + date.toString() +
            " - De " + timeStart.toString() +
            " à " + timeEnd.toString();
    return s;
}

// ---------- Getteurs ----------
const string& RDV::getName(void) const{
    return this->name;
}
Date& RDV::getDate(void){
    return this->date;
}
Hour& RDV::getTimeStart(void){
    return this->timeStart;
}
Hour& RDV::getTimeEnd(void){
    return this->timeEnd;
}
const vector<Personne*>& RDV::getMembersList(void) const{
    return this->membersList;
}

// ---------- Setteurs ----------
void RDV::setName(const string& name){
    this->name = name;
}
void RDV::setDate(const Date& date){
    this->date = date;
}
void RDV::setTimeStart(const Hour& timeStart){
    this->timeStart = timeStart;
}
void RDV::setTimeEnd(const Hour& timeEnd){
    this->timeEnd = timeEnd;
}
void RDV::setMembersList(const vector<Personne*>& membersList){
    this->membersList = membersList;
}

// ---------- Fonctions globales ----------
ostream& operator<<(ostream& ost, const RDV& rdv){
    rdv.afficher(ost);
    return ost;
}
