#include "date.h"

Date::Date(void)
{
    this->day = this->month = 1;
    this->year = 1970;
}

Date::Date(const Date& d){
    this->day = d.day;
    this->month = d.month;
    this->year = d.year;
}

Date::Date(const unsigned& day, const unsigned& month, const unsigned& year){
    this->day = day;
    this->month = month;
    this->year = year;
}

// ---------- Surcharge des opérateurs ----------
// Commentaires à supprimer après validation
// TODO - Utiliser compareTo() pour les opérateurs binaires
bool Date::operator==(const Date& d) const
{
    return(day==d.day && month==d.month && year==d.year);
}
bool Date::operator!=(const Date& d) const
{
    return(!operator==(d));
}
bool Date::operator>(const Date& d) const
{
   return (compareTo(d)==-1);
}
bool Date::operator>=(const Date& d) const
{
    return (compareTo(d) <= 0);
}
bool Date::operator<(const Date& d) const
{
    return (compareTo(d)==1);
}
bool Date::operator<=(const Date& d) const
{
   return (compareTo(d) >= 0);
}

Date Date::operator+(int nbJours) const
{
    Date nD = {day,month,year};
    nD.add(nbJours);
    return nD;
}
Date& Date::operator+=(int nbJours)
{
    add(nbJours);
    return *this;
}
Date Date::operator-(int nbJours) const
{
    Date nD = {day,month,year};
    nD.remove(nbJours);
    return nD;
}
Date& Date::operator-=(int nbJours)
{
    remove(nbJours);
    return *this;
}

// Post incrémentation : i++
Date Date::operator++(int)
{
    const Date& d(*this);
    operator++();
    return d;
}
Date Date::operator--(int)
{
    const Date& d(*this);
    operator--();
    return d;
}

// Pré incrémentation : ++i
Date& Date::operator++(void)
{
    if(month == 12 && day == 31)
    {
        day = 1;
        month = 1;
        ++year;
    }
    else if(day == (unsigned)lengthMonth()) //lengthMonth() doit me dire si bissextile ou pas
    {
        day = 1;
        ++month;
    }
    else ++day;
    return *this;
}
Date& Date::operator--(void)
{
    if(month == 1 && day == 1)
    {
        day = 31;
        month = 12;
        --year;
    }
    else if(day == 1)
    {
        --month;
        day = lengthMonth(); //prend la valeur du mois modifie en tenant compte de fev
    }
    else --day;
    return *this;
}

void Date::operator=(const Date& d)
{
    year = d.year;
    month = d.month;
    day = d.day;
}

Date::operator QString(void) const{
    return QString::fromStdString(toString());
}
Date::operator string(void) const{
    return toString();
}


// ---------- Méthodes ----------
void Date::add(int val)
{
    if(val > 0)
    {
        for(int i = 0 ; i < val ; ++i)
        {
            ++*this;
        }
    }
    else
    {
        for(int i = 0 ; i < val ; ++i)
        {
            --*this;
        }
    }
}

void Date::remove(int val)
{
    if(val > 0)
    {
        for(int i = 0 ; i < val ; ++i)
        {
            --*this;
        }
    }
    else
    {
        for(int i = 0 ; i < val ; ++i)
        {
            ++*this;
        }
    }
}
void Date::afficher(ostream& ost) const
{
    ost<<toString();
}

// Commentaires à supprimer après validation
// TODO - Retourne 1 si d > this, -1 si d < this, 0 sinon
int Date::compareTo(const Date& d) const
{
    int b;
    if(year > d.year) {b = -1;}
    else if(year < d.year) {b = 1;}
        else if(month > d.month) {b = -1;}
             else if(month < d.month) {b=1;}
                  else if(day > d.day) {b=-1;}
                       else if(day < d.day) {b=1;}
                            else b = 0;
    return b;
}

bool Date::leap(void) const{
    return (year % 4 == 0 and year % 10 != 0) or year % 400;
}

int Date::lengthMonth(void) const
{
    if(month==2)
    {
        if(leap())
        {
            return 29;
        }
        else return 28;
    }
    if(month==4||month==6||month==9||month==11)
    {
        return 30;
    }
    else return 31;
}

QString Date::toQString(void) const{
    return QString::fromStdString(toString());
}

string Date::toString(void) const{
    string s = ""; s += day; s += "/"; s += month; s += "/"; s += year;
    return s;
}

// ---------- Getteurs ----------
// Commentaires à supprimer après validation
// TODO - Remplir les getteurs
unsigned Date::getDay(void) const
{
    return day;
}

unsigned Date::getMonth(void) const
{
    return month;
}

unsigned Date::getYear(void) const
{
    return year;
}
// ---------- Setteurs ----------
// Commentaires à supprimer après validation
// TODO - Remplir les setteurs
void Date::setDay(const unsigned& d)
{
    day = d;
}
void Date::setMonth(const unsigned& m)
{
    month = m;
}
void Date::setYear(const unsigned& y)
{
    year = y;
}
// ---------- Fonctions globales ----------
ostream& operator<<(ostream& ost, const Date& d){
    d.afficher(ost);
    return ost;
}
