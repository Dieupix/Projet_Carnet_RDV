#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <ctime>

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

    Date& operator=(const Date&);

    operator QString(void) const;
    operator string(void) const;

    // Méthodes
    Date& add(int nbJours);
    void afficher(ostream& ost = cout) const;
    int compareTo(const Date& d) const;
    bool isLeap(void) const;
    int lengthMonth(void) const;
    Date& remove(int nbJours);
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

    friend Date today(void);
};

// Fonctions globales
bool stoDate(const string& s, Date& d);
ostream& operator<<(ostream&, const Date&);

#endif // DATE_H
