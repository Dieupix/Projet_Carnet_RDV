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
    Personne(const string& firstName, const string& lastName, const string& phone, const string& email);

    QString toQString(void) const;

    string getFirstName(void) const;
    string getLastName(void) const;
    string getPhone(void) const;
    string getEmail(void) const;

    void afficher(ostream& ost = cout) const;
};

ostream& operator<<(ostream& ost, const Personne& p);

#endif // PERSONNE_H
