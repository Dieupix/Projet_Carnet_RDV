#ifndef DATE_H
#define DATE_H

#include <iostream>

#include <QString>

using namespace std;

class Date
{
private:
    unsigned day, month, year;

public:
    Date(void);
    Date(const unsigned& day, const unsigned& month, const unsigned& year);

    // Surcharge d'opérateurs
    bool operator==(const Date& d) const;
    bool operator!=(const Date& d) const;
    bool operator>(const Date& d) const;
    bool operator>=(const Date& d) const;
    bool operator<(const Date& d) const;
    bool operator<=(const Date& d) const;


    // Méthodes
    void add(const Date& d);
    void afficher(ostream& ost = cout) const;
    bool bisextile(void) const;
    int comparerA(const Date& d) const;
    QString ToQString(void) const;
    string ToString(void) const;

    // Getteurs
    unsigned getDay(void) const;
    unsigned getMonth(void) const;
    unsigned getYear(void) const;

    // Setteurs
    void setDay(const unsigned& day);
    void setMonth(const unsigned& month);
    void setYear(const unsigned& year);

};

// Fonctions globales
ostream& operator<<(ostream& ost, const Date& d);

#endif // DATE_H
