#ifndef PERSONNE_H
#define PERSONNE_H

#include <iostream>

#include <QString>

using namespace std;

class Personne
{
private:
    string firstName, lastName, phone, email;

public:
    Personne(const string&, const string&, const string&, const string&);

    operator QString(void) const;

    QString toQString(void) const;

    string getFirstName(void) const;
    string getLastName(void) const;
    string getPhone(void) const;
    string getEmail(void) const;

    void afficher(ostream&) const;
    void setFirstName(const string&);
    void setLastName(const string&);
    void setPhone(const string&);
    void setEmail(const string&);
};

ostream& operator<<(ostream&, const Personne&);

#endif // PERSONNE_H
