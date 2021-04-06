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
bool Date::operator==(const Date& d) const
{
    return compareTo(d) == 0;
}
bool Date::operator!=(const Date& d) const
{
    return compareTo(d) != 0;
}
bool Date::operator>(const Date& d) const
{
   return compareTo(d) == -1;
}
bool Date::operator>=(const Date& d) const
{
    return compareTo(d) <= 0;
}
bool Date::operator<(const Date& d) const
{
    return compareTo(d) == 1;
}
bool Date::operator<=(const Date& d) const
{
   return compareTo(d) >= 0;
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
    else if(day == (unsigned)lengthMonth())
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
        day = lengthMonth();
    }
    else --day;
    return *this;
}

Date& Date::operator=(const Date& d)
{
    year = d.year;
    month = d.month;
    day = d.day;
    return *this;
}

Date::operator QString(void) const{
    return QString::fromStdString(toString());
}
Date::operator string(void) const{
    return toString();
}



// ---------- Méthodes ----------
Date& Date::add(int nbJours)
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

void Date::afficher(ostream& ost) const
{
    ost << toString();
}

// Retourne 1 si d > this, -1 si d < this, 0 sinon
int Date::compareTo(const Date& d) const
{
    if(year > d.year) return -1;
    else if(year < d.year) return 1;
    else if(month > d.month) return -1;
    else if(month < d.month) return 1;
    else if(day > d.day) return -1;
    else if(day < d.day) return 1;
    else return 0;
}

// Retourne vrai si l'année est bissextile, faux sinon
bool Date::isLeap(void) const{
    return (year % 4 == 0 and year % 10 != 0) or year % 400 == 0;
}

int Date::lengthMonth(void) const
{
    if(month==2)
    {
        if(isLeap())
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

Date& Date::remove(int nbJours)
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

QString Date::toQString(void) const{
    return QString::fromStdString(toString());
}

string Date::toString(void) const{
    string s = (day < 10 ? "0" : "") + to_string(day) + "/" + (month < 10 ? "0" : "") + to_string(month) + "/" + to_string(year);
    return s;
}



// ---------- Getteurs ----------
unsigned Date::getDay(void) const
{   return day;     }

unsigned Date::getMonth(void) const
{   return month;   }

unsigned Date::getYear(void) const
{   return year;    }


// ---------- Setteurs ----------
void Date::setDay(const unsigned& d)
{   day = d;        }
void Date::setMonth(const unsigned& m)
{   month = m;      }
void Date::setYear(const unsigned& y)
{   year = y;       }



// ---------- Fonctions globales ----------
ostream& operator<<(ostream& ost, const Date& d){
    d.afficher(ost);
    return ost;
}

bool stoDate(const string& str, Date& date){
    string s = str + '/';
    bool isValide = true;
    int d = -1, m = -1, y = -1;
    string tmp = "";
    for(unsigned i = 0; i < s.length(); ++i){
        char c = s[i];
        if(c == '/'){
            if(tmp != ""){
                if(d == -1 and m == -1 and y == -1){
                    try{
                       d = stoi(tmp);
                    } catch(...){
                        isValide = false;
                        cerr << "Erreur : Ce n'est pas un entier" << endl;
                    }
                }else if(d != -1 and m == -1 and y == -1){
                    try{
                        m = stoi(tmp);
                    } catch(...){
                        isValide = false;
                        cerr << "Erreur : Ce n'est pas un entier" << endl;
                    }
                }else if(d != -1 and m != -1 and y == -1){
                    try{
                        y = stoi(tmp);
                    } catch(...){
                        isValide = false;
                        cerr << "Erreur : Ce n'est pas un entier" << endl;
                    }
                }
                tmp = "";
            }
        }else tmp += c;
    }

    if(m < 1 or m > 12){
        isValide = false;
        cerr << "Erreur : Le mois est incorrect" << endl;
    }else if(m == 2){
        if((y % 4 == 0 and y % 10 != 0) or y % 400 == 0){
            if(d < 1 or d > 29){
                isValide = false;
                cerr << "Erreur : Le jour est incorrect" << endl;
            }
        }else if(d < 1 or d > 28){
            isValide = false;
            cerr << "Erreur : Le jour est incorrect" << endl;
        }
    }else if(m == 4 or m == 6 or m == 9 or m == 11){
        if(d < 1 or d > 30){
            isValide = false;
            cerr << "Erreur : Le jour est incorrect" << endl;
        }
    }else if(d < 0 or d > 31){
        isValide = false;
        cerr << "Erreur : Le jour est incorrect" << endl;
    }

    if(isValide){
        date.setDay(d);
        date.setMonth(m);
        date.setYear(y);
    }

    return isValide;
}

Date today(void)
{
    Date dt{};
    time_t t = time(NULL);
    tm* now = localtime(&t);
    dt.day = now->tm_mday;
    dt.month = now->tm_mon;
    dt.year = now->tm_year + 1900;
    return dt;
}
