#include "hour.h"

Hour::Hour(void)
{
    this->second = this->minute = this->hour = 0;
}

Hour::Hour(const unsigned& hour, const unsigned& minute, const unsigned& second){
    this->second = second;
    this->minute = minute;
    this->hour = hour;
}
