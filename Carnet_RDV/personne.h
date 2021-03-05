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

    // Surcharge d'opérateurs
    bool operator>(const Personne&) const;
    bool operator>=(const Personne&) const;
    bool operator<(const Personne&) const;
    bool operator<=(const Personne&) const;
    bool operator==(const Personne&) const;
    bool operator!=(const Personne&) const;
    void operator=(const Personne&);

    operator QString(void) const;

    // Méthodes
    void afficher(ostream&) const;
    QString toQString(void) const;

    // Getteurs
    const string& getFirstName(void) const;
    const string& getLastName(void) const;
    const string& getPhone(void) const;
    const string& getEmail(void) const;

    // Setteurs
    void setFirstName(const string&);
    void setLastName(const string&);
    void setPhone(const string&);
    void setEmail(const string&);
};

// Fonctions globales
ostream& operator<<(ostream&, const Personne&);

#endif // PERSONNE_H
