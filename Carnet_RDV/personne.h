#ifndef PERSONNE_H
#define PERSONNE_H

#include <iostream>
#include "rdv.h"

#include <QObject>
#include <QString>

class RDV;

using namespace std;

class Personne
{
    friend class RDV;
private:
    string          firstName, lastName, phone, email;
    vector<RDV*>    rdvList;

public:
    enum AddPersonneToOrRemovePersonneFromRdv {PersonneAdded = 1, PersonneRemoved, PersonneHasAnRdv, PersonneIsAlreadyInsideRdv, PersonneHasNotBeenAdded, PersonneHasNotBeenRemoved, RdvListIsEmpty,
                                               RdvAdded, RdvRemoved, RdvHasNotBeenAdded, RdvHasNotBeenRemoved, MembersListIsEmpty, };

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
    int         addRDV(RDV* rdv);
    void        afficher(ostream& ost = cout) const;
    int         compareTo(const Personne& p) const;
    QString     rdvToQString(void) const;
    string      rdvToString(void) const;
    int         removeRDV(RDV* rdv);
    QString     toQString(void) const;
    string      toString(void) const;

    // Getters
    const string&           getFirstName(void) const;
    const string&           getLastName(void) const;
    const string&           getPhone(void) const;
    const string&           getEmail(void) const;
    const vector<RDV*>&     getRDVList(void) const;

    // Setters
    void setFirstName(const string& firstName);
    void setLastName(const string& lastName);
    void setPhone(const string& phone);
    void setEmail(const string& email);
    void setRDVList(const vector<RDV*>& rdvList);
};

// Fonctions globales
ostream& operator<<(ostream&, const Personne&);

#endif // PERSONNE_H
