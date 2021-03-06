#ifndef RDV_H
#define RDV_H

#include <vector>

#include "ldcp.h"

class RDV
{
private:
    string name, timeStart, timeEnd;
    vector<char> date;
    LDCP membersList;

public:
    RDV(const string& name, const vector<char>& date, const string& timeStart, const string& timeEnd, const LDCP& membersList = LDCP());

    // Surcharge d'opérateurs
    bool operator>(const RDV&) const;
    bool operator>=(const RDV&) const;
    bool operator<(const RDV&) const;
    bool operator<=(const RDV&) const;
    bool operator==(const RDV&) const;
    bool operator!=(const RDV&) const;
    void operator=(const RDV&);

    operator QString(void) const;

    // Méthodes
    void afficher(ostream& ost = cout) const;
    string dateToString(void) const;
    QString toQString(void) const;

    // Getteurs
    const string& getName(void) const;
    const string& getTimeStart(void) const;
    const string& getTimeEnd(void) const;
    const vector<char>& getDate(void) const;
    vector<Personne*>& getMembersList(void);

    // Setteurs
    void setName(const string& name);
    void setTimeStart(const string& timeStart);
    void setTimeEnd(const string& timeEnd);
    void setDate(const vector<char>& date);

};

// Fonctions globales
ostream& operator<<(ostream&, const RDV&);

#endif // RDV_H
