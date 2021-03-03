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

    operator QString(void) const;

    QString toQString(void) const;

    void afficher(ostream&) const;
};

ostream& operator<<(ostream&, const RDV&);

#endif // RDV_H
