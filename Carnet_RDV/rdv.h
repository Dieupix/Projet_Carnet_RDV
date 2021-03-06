#ifndef RDV_H
#define RDV_H

#include "personne.h"
#include "date.h"
#include "hour.h"

class RDV
{
    friend class LDCR;
private:
    string name;
    Date date;
    Hour timeStart, timeEnd;
    vector<Personne*> membersList;

public:
    RDV(const string& name, const Date& date, const Hour& timeStart, const Hour& timeEnd, const vector<Personne*>& membersList = vector<Personne*>());

    // Surcharge d'opérateurs
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
    void afficher(ostream& ost = cout) const;
    string dateToString(void) const;
    string participantsToString(void) const;
    QString toQString(void) const;
    string toString(void) const;

    // Getteurs
    const string& getName(void) const;
    const string& getTimeStart(void) const;
    const string& getTimeEnd(void) const;
    Date& getDate(void);
    vector<Personne*>& getMembersList(void);

    // Setteurs
    void setName(const string& name);
    void setTimeStart(const string& timeStart);
    void setTimeEnd(const string& timeEnd);

};

// Fonctions globales
ostream& operator<<(ostream&, const RDV&);

#endif // RDV_H_
