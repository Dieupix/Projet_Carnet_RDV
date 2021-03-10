#include "date.h"
// pour les operateurs +,- :
#include<cmath>

Date::Date(void)
{
    this->day = this->month = 1;
    this->year = 1970;
}

Date::Date(const unsigned& day, const unsigned& month, const unsigned& year){
    this->day = day;
    this->month = month;
    this->year = year;
}

// ---------- Surchargde des opérateurs ----------
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
   int i = compareTo(d);
   if(i==-1)
   {
       return true;
   }
   else return false;
}
bool Date::operator>=(const Date& d) const
{
    int i = compareTo(d);
    if(i==-1 || i==0)
    {
        return true;
    }
    else return false;
}
bool Date::operator<(const Date& d) const
{
    int i = compareTo(d);
    if(i==1)
    {
        return true;
    }
    else return false;
}
bool Date::operator<=(const Date& d) const
{
   int i = compareTo(d);
   if(i==1 || i==0)
   {
       return true;
   }
   else return false;
}

Date Date::operator+(int nbJours) const
{
    Date nD = {day,month,year};
    if(nbJours > 0)
    {
        for(int i = 0 ; i < nbJours ; ++i)
        {
            ++nD;
        }
    }
    else if(nbJours < 0)
    {
        for(int i = 0 ; i < nbJours ; ++i)
        {
            --nD;
        }
    }
    return nD;
}
Date& Date::operator+=(int nbJours)
{
    if(nbJours > 0)
    {
        for(int i = 0 ; i < nbJours ; ++i)
        {
            ++*this;
        }
    }
    else
    {
        for(int i = 0 ; i < nbJours ; ++i)
        {
            --*this;
        }
    }
    return *this;
}
Date Date::operator-(int nbJours) const
{
    Date nD = {day,month,year};
    if(nbJours > 0)
    {
        for(int i = 0 ; i < nbJours ; ++i)
        {
            --nD;
        }
    }
    else if(nbJours < 0)
    {
        for(int i = 0 ; i < nbJours ; ++i)
        {
            ++nD;
        }
    }
    return nD;
}
Date& Date::operator-=(int nbJours)
{
    if(nbJours > 0)
    {
        for(int i = 0 ; i < nbJours ; ++i)
        {
            --*this;
        }
    }
    else
    {
        for(int i = 0 ; i < nbJours ; ++i)
        {
            ++*this;
        }
    }
    return *this;
}
//i++
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
//++i
Date& Date::operator++(void)
{
    if(month == 12 && day == 31)
    {
        day = 1;
        month = 1;
        ++year;
    }
    else if(day == lengthMonth()) //lengthMonth() doit me dire si bissextile ou pas
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

void Date::operator=(const Date&) const
{

}

Date::operator QString(void) const{
    return QString::fromStdString(toString());
}
Date::operator string(void) const{
    return toString();
}


// ---------- Méthodes ----------
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

// ---------- Setteurs ----------
// Commentaires à supprimer après validation
// TODO - Remplir les setteurs

// ---------- Fonctions globales ----------
ostream& operator<<(ostream& ost, const Date& d){
    d.afficher(ost);
    return ost;
}
