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

    const string& getName(void) const;
    const string& getTimeStart(void) const;
    const string& getTimeEnd(void) const;
    const vector<char>& getDate(void) const;
    vector<Personne*>& getMembersList(void);

    void afficher(ostream&) const;
    void setName(const string&);
    void setTimeStart(const string&);
    void setTimeEnd(const string&);
    void setDate(const vector<char>&);

};

ostream& operator<<(ostream&, const RDV&);

#endif // RDV_H
