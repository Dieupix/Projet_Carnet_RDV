#ifndef RDV_H
#define RDV_H

#include "date.h"
#include "hour.h"
#include "personne.h"

class Personne;

class RDV
{
    friend class Personne;
private:
    string              name;
    Date                date;
    Hour                timeStart, timeEnd;
    vector<Personne*>   membersList;

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
    bool        addMember(Personne* p);
    void        afficher(ostream& ost = cout) const;
    int         compareTo(const RDV& rdv) const;
    bool        estImbrique(const RDV& r) const;
    QString     participantsToQString(void);
    string      participantsToString(void);
    bool        removeMember(Personne* p);
    QString     toQString(void) const;
    string      toString(void) const;

    // Getters
    const string&               getName(void) const;
    const Date&                 getDate(void) const;
    const Hour&                 getTimeStart(void) const;
    const Hour&                 getTimeEnd(void) const;
    const vector<Personne*>&    getMembersList(void) const;

    // Setters
    void setName(const string& name);
    void setDate(const Date& date);
    void setTimeStart(const Hour& timeStart);
    void setTimeEnd(const Hour& timeEnd);
    void setMembersList(const vector<Personne*>& membersList);
};

// Fonctions globales
ostream& operator<<(ostream&, const RDV&);

#endif // RDV_H_
