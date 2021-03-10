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
    // On suppose que les paramètres sont toujours valides
    Date(void);
    Date(const Date& d);
    Date(const unsigned& day, const unsigned& month, const unsigned& year);

    // Surcharge des opérateurs
    bool operator==(const Date&) const;
    bool operator!=(const Date&) const;
    bool operator>(const Date&) const;
    bool operator>=(const Date&) const;
    bool operator<(const Date&) const;
    bool operator<=(const Date&) const;

    Date operator+(int) const;
    Date& operator+=(int);
    Date operator-(int) const;
    Date& operator-=(int);

    Date operator++(int);
    Date operator--(int);

    Date& operator++(void);
    Date& operator--(void);

    void operator=(const Date&);

    operator QString(void) const;
    operator string(void) const;

    // Méthodes
    void add(int val);
    void afficher(ostream& ost = cout) const;
    int compareTo(const Date& d) const;
    bool leap(void) const;
    int lengthMonth(void) const;
    void remove(int val);
    QString toQString(void) const;
    string toString(void) const;

    // Getteurs
    unsigned getDay(void) const;
    unsigned getMonth(void) const;
    unsigned getYear(void) const;

    // Setteurs
    void setDay(const unsigned& d);
    void setMonth(const unsigned& m);
    void setYear(const unsigned& y);

};

// Fonctions globales
ostream& operator<<(ostream& ost, const Date& d);

#endif // DATE_H
