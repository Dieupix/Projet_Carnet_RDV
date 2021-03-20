#ifndef RDV_H
#define RDV_H

#include "personne.h"
#include "date.h"
#include "hour.h"
class Personne;

class RDV
{
private:
    string name;
    Date date;
    Hour timeStart, timeEnd;
    vector<Personne*> membersList;

public:
    RDV(const string& name, const Date& date, const Hour& timeStart, const Hour& timeEnd, const vector<Personne*>& membersList = vector<Personne*>());

    // Surcharge des opérateurs
    bool operator>(const RDV&) const;
    bool operator>=(const RDV&) const;
    bool operator<(const RDV&) const;
    bool operator<=(const RDV&) const;
    bool operator==(const RDV&) const;
    bool operator!=(const RDV&) const;
    void operator=(const RDV&);

    operator QString(void) const;
    operator string(void) const;

    // Méthodes
    bool addMember(Personne* p);
    void afficher(ostream& ost = cout) const;
    int compareTo(const RDV& rdv) const;
    string participantsToString(void) const;
    bool removeMember(Personne* p);
    QString toQString(void) const;
    string toString(void) const;

    // Getteurs
    const string& getName(void) const;
    Date& getDate(void);
    Hour& getTimeStart(void);
    Hour& getTimeEnd(void);
    const vector<Personne*>& getMembersList(void) const;

    // Setteurs
    void setName(const string& name);
    void setDate(const Date& date);
    void setTimeStart(const Hour& timeStart);
    void setTimeEnd(const Hour& timeEnd);
    void setMembersList(const vector<Personne*>& membersList);

};

// Fonctions globales
ostream& operator<<(ostream&, const RDV&);

#endif // RDV_H_
