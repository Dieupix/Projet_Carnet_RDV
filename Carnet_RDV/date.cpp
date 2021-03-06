#include "date.h"

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
