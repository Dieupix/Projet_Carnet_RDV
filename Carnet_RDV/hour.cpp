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
bool Hour::operator==(const Hour& h) const
{
    return compareTo(h) == 0;
}
bool Hour::operator!=(const Hour& h) const
{
    return compareTo(h) != 0;
}
bool Hour::operator>(const Hour& h) const
{
    return compareTo(h) == -1;
}
bool Hour::operator>=(const Hour& h) const
{
    return compareTo(h) <= 0;
}
bool Hour::operator<(const Hour& h) const
{
    return compareTo(h) == 1 ;
}
bool Hour::operator<=(const Hour& h) const
{
    return compareTo(h) >= 0 ;
}

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

// Pré incrémentation : ++i
Hour& Hour::operator++(void)
{
    add(Hour(0, 0, 1));
    return *this;
}
Hour& Hour::operator--(void)
{
    remove(Hour(0, 0, 1));
    return *this;
}

Hour& Hour::operator=(const Hour& h)
{
    second = h.second;
    minute = h.minute;
    hour = h.hour;
    return *this;
}

Hour::operator QString(void) const{
    return QString::fromStdString(toString());
}
Hour::operator string(void) const{
    return toString();
}



// ---------- Méthodes ----------
Hour& Hour::add(const Hour& h)
{
    if(h.second == 0 and h.minute == 0 and h.hour % 24 == 0) return *this;
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
        else
        {
            hour += h.hour;
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
            if(hour >= 24)
            {
                hour %= 24;
            }
        }
    }
    return *this;
}

void Hour::afficher(ostream& ost) const
{
    ost<<toString();
}

// Retourne 1 si h > this, -1 si h < this, 0 sinon
int Hour::compareTo(const Hour& h) const{
    if(hour > h.hour) return -1;
    else if(hour < h.hour) return 1;
        else if(minute > h.minute) return -1;
            else if(minute < h.minute) return 1;
                else if(second > h.second) return -1;
                    else if(second < h.second) return 1;
                        else return 0;
}

Hour& Hour::remove(const Hour& h)
{
    if(h.second == 0 and h.minute == 0 and h.hour % 24 == 0) return *this;

    if(second < h.second){
        if(minute <= h.minute){
            if(hour <= h.hour)
                hour += 23;
            else --hour;
            minute += 59;
        }
        else --minute;
        second += 60;
    }else if(minute < h.minute){
        if(hour <= h.hour)
            hour += 23;
        else --hour;
        minute += 60;
    }else if(hour < h.hour)
        hour += 24;

    second -= h.second;
    minute -= h.minute;
    hour -= h.hour;

    return *this;
}

QString Hour::toQString(void) const{
    return QString::fromStdString(toString());
}

string Hour::toString(void) const{
    string s = to_string(hour) + "h" + (minute < 10 ? "0" : "") + to_string(minute);
    if(second != 0){
        s += (string) "m" + (second < 10 ? "0" : "") + to_string(second) + "s";
    }
    return s;
}



// ---------- Getteurs ----------
unsigned Hour::getSecond(void) const
{   return second;  }

unsigned Hour::getMinute(void) const
{   return minute;  }

unsigned Hour::getHour(void) const
{   return hour;    }



// ---------- Setteurs ----------
void Hour::setSecond(const unsigned& s)
{   second = s;     }

void Hour::setMinute(const unsigned& m)
{   minute = m;     }

void Hour::setHour(const unsigned& h)
{   hour = h;       }



// ---------- Fonctions globales ----------
bool stoHour(const string& s, Hour& h){
}
ostream& operator<<(ostream& ost, const Hour& h){
    h.afficher(ost);
    return ost;
}

Hour now(void)
{
    Hour h{};
    time_t t = time(NULL);
    tm* now = localtime(&t);
    h.hour = now->tm_hour;
    h.minute = now->tm_min;
    h.second = now->tm_sec;
    return h;
}
