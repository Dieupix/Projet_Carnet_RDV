#ifndef PERSONNE_H
#define PERSONNE_H

#include <iostream>

#include <QString>

class RDV;

using namespace std;

class Personne
{
private:
    string firstName, lastName, phone, email;
    vector<RDV*> rdvList;

public:
    Personne(const string& firstName, const string& lastName, const string& phone, const string& email, const vector<RDV*>& rdvList = vector<RDV*>());

    // Surcharge des opérateurs
    bool operator>(const Personne&) const;
    bool operator>=(const Personne&) const;
    bool operator<(const Personne&) const;
    bool operator<=(const Personne&) const;
    bool operator==(const Personne&) const;
    bool operator!=(const Personne&) const;
    void operator=(const Personne&);

    operator QString(void) const;
    operator string(void) const;

    // Méthodes
    bool addRDV(RDV* rdv);
    void afficher(ostream& ost = cout) const;
    bool removeRDV(RDV* rdv);
    QString toQString(void) const;
    string toString(void) const;

    // Getteurs
    const string& getFirstName(void) const;
    const string& getLastName(void) const;
    const string& getPhone(void) const;
    const string& getEmail(void) const;
    const vector<RDV*>& getRDVList(void) const;

    // Setteurs
    void setFirstName(const string& firstName);
    void setLastName(const string& lastName);
    void setPhone(const string& phone);
    void setEmail(const string& email);
};

// Fonctions globales
ostream& operator<<(ostream&, const Personne&);

#endif // PERSONNE_H
