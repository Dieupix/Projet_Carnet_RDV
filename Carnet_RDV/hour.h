#ifndef HOUR_H
#define HOUR_H

#include <iostream>

#include <QString>

using namespace std;

class Hour
{
private:
    unsigned hour, minute, second;

public:
    Hour(void);
    Hour(const Hour& h);
    Hour(const unsigned& hour, const unsigned& minute, const unsigned& second);

    // Surcharge d'opérateurs
    bool operator==(const Hour&) const;
    bool operator!=(const Hour&) const;
    bool operator>(const Hour&) const;
    bool operator>=(const Hour&) const;
    bool operator<(const Hour&) const;
    bool operator<=(const Hour&) const;

    Hour operator+(const Hour&) const;
    Hour& operator+=(const Hour&);

    void operator=(const Hour&) const;

    operator QString(void) const;
    operator string(void) const;

    // Méthodes
    void afficher(ostream& ost = cout) const;
    int compareTo(const Hour& h) const;
    QString toQString(void) const;
    string toString(void) const;

    // Getteurs
    unsigned getSecond(void) const;
    unsigned getMinute(void) const;
    unsigned getHour(void) const;

    // Setteurs
    void setSecond(const unsigned& second);
    void setMinute(const unsigned& minute);
    void setHour(const unsigned& hour);

};

// Fonctions globales
ostream& operator<<(ostream& ost, const Hour& h);

#endif // HOUR_H
