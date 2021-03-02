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
    RDV(const string& name, const vector<char>& date, const string& timeStart, const string& timeEnd, const vector<Personne*>& membersList);

    operator QString(void) const;

    QString toQString(void) const;

    void afficher(ostream& ost = cout) const;
};

ostream& operator<<(ostream& ost, const RDV& rdv);

#endif // RDV_H
