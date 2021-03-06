#ifndef HOUR_H
#define HOUR_H

#include <iostream>

#include <QString>
#include<ctime>
using namespace std;

class Hour
{
private:
    unsigned hour, minute, second;

public:
    // On suppose que les paramètres sont toujours valides
    Hour(void);
    Hour(const Hour& h);
    Hour(const unsigned& hour, const unsigned& minute, const unsigned& second);

    // Surcharge des opérateurs
    bool operator==(const Hour&) const;
    bool operator!=(const Hour&) const;
    bool operator>(const Hour&) const;
    bool operator>=(const Hour&) const;
    bool operator<(const Hour&) const;
    bool operator<=(const Hour&) const;

    Hour operator+(const Hour&) const;
    Hour& operator+=(const Hour&);
    Hour operator-(const Hour&) const;
    Hour& operator-=(const Hour&);

    Hour operator++(int);
    Hour operator--(int);

    Hour& operator++(void);
    Hour& operator--(void);

    Hour& operator=(const Hour&);

    operator QString(void) const;
    operator string(void) const;

    // Méthodes
    Hour& add(const Hour& h);
    void afficher(ostream& ost = cout) const;
    int compareTo(const Hour& h) const;
    Hour& remove(const Hour& h);
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

    friend Hour now(void);
};

// Fonctions globales
bool stoHour(const string& s, Hour& h);
ostream& operator<<(ostream& ost, const Hour& h);

#endif // HOUR_H
