#include "hour.h"

Hour::Hour(void)
{
    this->second = this->minute = this->hour = 0;
}

Hour::Hour(const Hour& h){
    this->second = h.second;
    this->minute = h.minute;
    this->hour = h.hour;
}

Hour::Hour(const unsigned& hour, const unsigned& minute, const unsigned& second){
    this->second = second;
    this->minute = minute;
    this->hour = hour;
}

// ---------- Surchargde des opérateurs ----------
// Commentaires à supprimer après validation
// TODO - Utiliser compareTo() pour les opérateurs de comparaison
bool Hour::operator==(const Hour& h) const
{return (compareTo(h)==0);}
bool Hour::operator!=(const Hour& h) const
{return compareTo(h)!=0;}
bool Hour::operator>(const Hour& h) const
{return compareTo(h)==-1;}
bool Hour::operator>=(const Hour& h) const
{return compareTo(h)<=0;}
bool Hour::operator<(const Hour& h) const
{return compareTo(h)==1;}
bool Hour::operator<=(const Hour& h) const
{return compareTo(h)>=0;}

// Commentaires à supprimer après validation
// TODO - Utiliser add() et remove() pour les opérateurs d'addition
Hour Hour::operator+(const Hour& h) const
{
    Hour nh{hour,minute,second};
    nh.add(h);
    return nh;
}
Hour& Hour::operator+=(const Hour& h)
{
    add(h);
    return *this;
}
Hour Hour::operator-(const Hour& h) const
{
    Hour nh{hour,minute,second};
    nh.remove(h);
    return nh;
}
Hour& Hour::operator-=(const Hour& h)
{
    remove(h);
    return *this;
}

// Post incrémentation : i++
Hour Hour::operator++(int)
{
    const Hour& h(*this);
    operator++();
    return h;
}
Hour Hour::operator--(int)
{
    const Hour& h(*this);
    operator--();
    return h;
}

//pre incrementation : ++i
Hour& Hour::operator++(void)
{
    if(second + 1 == 60)
    {
        second = 0;
        ++minute;
        if(minute == 60)
        {
            minute = 0;
            ++hour;
            if(hour == 24)
            {
                hour = 0;
            }
        }
    }
    else
    {++second;}
    return *this;
}
Hour& Hour::operator--(void)
{
    if(second - 1 < 0)
    {
        second = 59;
        --minute;
        if(minute < 0)
        {
            minute = 59;
            --hour;
            if(hour < 0)
            {
                hour = 23;
            }
        }
    }
    else --second;
    return *this;
}

void Hour::operator=(const Hour& h)
{
    second = h.second;
    minute = h.minute;
    hour = h.hour;
}

Hour::operator QString(void) const{
    return QString::fromStdString(toString());
}
Hour::operator string(void) const{
    return toString();
}

// ---------- Méthodes ----------
void Hour::add(const Hour& h)
{
    second += h.second;
    if(second >= 60)
    {
        second %= 60;
        minute = (minute+h.minute+1);
        if(minute >= 60)
        {
            minute %= 60;
            hour = (hour+h.hour+1);
            if(hour >= 24)
            {
                hour %= 24;
            }
        }
    }
    else
    {
        minute += h.minute;
        if(minute >= 60)
        {
            minute %= 60;
            hour = (hour+h.hour+1);
            if(hour >= 24)
            {
                hour %= 24;
            }
        }
        else
        {
            hour += h.hour;
            if(hour >= 24) {hour %= 24;}
        }
    }
}

void Hour::afficher(ostream& ost) const
{
    ost<<toString();
}

// Commentaires à supprimer après validation
// TODO - Retourne 1 si h > this, -1 si h < this, 0 sinon
int Hour::compareTo(const Hour& h) const
{
    if(hour > h.hour) {return -1;}
    else if(hour < h.hour) {return 1;}
        else if(minute > h.minute) {return -1;}
            else if(minute < h.minute) {return 1;}
                else if(second > h.second) {return -1;}
                    else if(second < h.second) {return 1;}
                        else return 0;
}

void Hour::remove(const Hour& h)
{
    if(second - h.second <= 0 )
    {
        second = (h.second - second);
        --minute;
        if(minute - h.minute <=0)
        {
            --hour;
            minute = (h.minute - h.minute );
           if(hour - h.hour <= 0)
           {
               hour = h.hour - hour;
           }
        }
        else
        {
            minute -= h.minute;
            if(hour - h.hour <= 0)
            {
                hour = h.hour - hour;
            }
            else hour -= h.hour;
        }
    }
    else
    {
        second -= h.second;
        if(minute - h.minute <=0)
        {
            --hour;
            minute = (h.minute - h.minute );
           if(hour - h.hour <= 0)
           {
               hour = h.hour - hour;
           }
        }
        else
        {
            minute -= h.minute;
            if(hour - h.hour <= 0)
            {
                hour = h.hour - hour;
            }
            else hour -= h.hour;
        }
    }
}

QString Hour::toQString(void) const{
    return QString::fromStdString(toString());
}

string Hour::toString(void) const{
    string s = ""; s += hour; s += "h"; s += minute;
    if(second != 0){
        s += "m";
        s += second;
    }
    return s;
}

// ---------- Getteurs ----------
// Commentaires à supprimer après validation
// TODO - Remplir les getteurs

unsigned Hour::getSecond(void) const
{return second;}

unsigned Hour::getMinute(void) const
{return minute;}

unsigned Hour::getHour(void) const
{return hour;}

// ---------- Setteurs ----------
// Commentaires à supprimer après validation
// TODO - Remplir les setteurs

void Hour::setSecond(const unsigned& s)
{second = s;}

void Hour::setMinute(const unsigned& m)
{minute = m;}

void Hour::setHour(const unsigned& h)
{hour = h;}

// ---------- Fonctions globales ----------

ostream& operator<<(ostream& ost, const Hour& h){
    h.afficher(ost);
    return ost;
}
