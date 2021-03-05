#ifndef RDV_H
#define RDV_H

#include <vector>

#include "personne.h"

class RDV
{
private:
    string name, timeStart, timeEnd;
    vector<char> date;
    vector<Personne*> membersList;

public:
    RDV(const string&, const vector<char>&, const string&, const string&, const vector<Personne*>&);

    // Surcharge d'opérateurs
    bool operator==(const RDV&) const;
    bool operator!=(const RDV&) const;
    void operator=(const RDV&);

    operator QString(void) const;

    // Méthodes
    void afficher(ostream&) const;
    string dateToString(void) const;
    QString toQString(void) const;

    // Getteurs
    const string& getName(void) const;
    const string& getTimeStart(void) const;
    const string& getTimeEnd(void) const;
    const vector<char>& getDate(void) const;
    vector<Personne*>& getMembersList(void);

    // Setteurs
    void setName(const string&);
    void setTimeStart(const string&);
    void setTimeEnd(const string&);
    void setDate(const vector<char>&);

};

// Fonctions globales
ostream& operator<<(ostream&, const RDV&);

#endif // RDV_H
