#include "rdv.h"

RDV::RDV(const string& name, const vector<char>& date, const string& timeStart, const string& timeEnd, const vector<Personne*>& membersList)
{
    this->name = name;
    this->date = date;
    this->timeStart = timeStart;
    this->timeEnd = timeEnd;
    this->membersList = membersList;
}

RDV::operator QString(void) const{
    QString str = QString::fromStdString(name + " - Le " + date[0] + date[1] + "/" + date[2] + date[3] + "/" + date[4] + date[5] + date[6] + date[7] + " - De " + timeStart + " à " + timeEnd + "\n");
    str += "Participant";
    str += membersList.size() == 1 ? "" : "s";
    str += " (";
    str += QString::number(membersList.size());
    str += ") :\n";
    for(auto p : membersList)
        str += *p + "\n";
    return str;
}

QString RDV::toQString(void) const{
    QString str = QString::fromStdString(name + " - Le " + date[0] + date[1] + "/" + date[2] + date[3] + "/" + date[4] + date[5] + date[6] + date[7] + " - De " + timeStart + " à " + timeEnd + "\n");
    str += "Participant";
    str += membersList.size() == 1 ? "" : "s";
    str += " (";
    str += QString::number(membersList.size());
    str += ") :\n";
    for(auto p : membersList)
        str += *p + "\n";
    return str;
}

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

void RDV::afficher(ostream& ost = cout) const{
    ost << name << " - Le " << date[0] << date[1] << "/" << date[2] << date[3] << "/" << date[4] << date[5] << date[6] << date[7] << " - De " << timeStart << " a " << timeEnd << endl;
    ost << "Participant" << (membersList.size() == 1 ? "" : "s") << " (" << membersList.size() << ") :" << endl;
    if(membersList.size() == 0) ost << "Aucun participant" << endl;
    else for(auto p : membersList) ost << "* " << *p << endl;
}

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

ostream& operator<<(ostream& ost, const RDV& rdv){
    rdv.afficher(ost);
    return ost;
}
