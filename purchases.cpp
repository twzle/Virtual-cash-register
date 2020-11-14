#include "purchases.h"
#include <ctime>

Time::Time() {
    hours = 0;
    minutes = 0;
    seconds = 0;
}

Time::Time(const int &_hours, const int &_minutes, const int &_seconds) {
    if (_hours >= MIN_TIME_VALUE && _hours < MAX_HOURS_VALUE) {
        this->hours = _hours;
    }
    if (_minutes >= MIN_TIME_VALUE && _minutes < MAX_TIME_VALUE) {
        this->minutes = _minutes;
    }
    if (_seconds >= MIN_TIME_VALUE && _seconds < MAX_TIME_VALUE) {
        this->seconds = _seconds;
    }
}

std::ostream& operator<<(std::ostream& out, const Time& _value){
    if (_value.hours < 10)
        out << "0" + std::to_string(_value.hours) << ":";
    else
        out << std::to_string(_value.hours) << ":";
    if (_value.minutes < 10)
        out << "0" + std::to_string(_value.minutes) << ":";
    else
        out << std::to_string(_value.minutes) << ":";
    if (_value.seconds < 10)
        out << "0" + std::to_string(_value.seconds);
    else
        out << std::to_string(_value.seconds);
    return out;
}

bool operator>=(const Time &_lhs, const Time &_rhs) {
    if (_lhs.hours != _rhs.hours)
        return _lhs.hours > _rhs.hours;
    if (_lhs.minutes != _rhs.minutes)
        return _lhs.minutes > _rhs.minutes;
    if (_lhs.seconds != _rhs.seconds)
        return _lhs.seconds > _rhs.seconds;
    return 1;
}

bool operator==(const Time &_lhs, const Time &_rhs) {
    return _lhs.hours==_rhs.hours && _lhs.minutes==_rhs.minutes && _lhs.seconds==_rhs.seconds;
}

bool operator!=(const Time &_lhs, const Time &_rhs) {
    return _lhs.hours!=_rhs.hours || _lhs.minutes!=_rhs.minutes || _lhs.seconds!=_rhs.seconds;
}


Date::Date() {
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    day = now->tm_mday;
    month = now->tm_mon+1;
    year = now->tm_year + 1900;
}

bool operator>=(const Date &_lhs, const Date &_rhs) {
    if (_lhs.year != _rhs.year)
        return _lhs.year > _rhs.year;
    if (_lhs.month != _rhs.month)
        return _lhs.month > _rhs.month;
    if (_lhs.year != _rhs.year)
        return _lhs.year > _rhs.year;
    return 1;
}

bool operator==(const Date &_lhs, const Date &_rhs) {
    return _lhs.day==_rhs.day && _lhs.month==_rhs.month && _lhs.month==_rhs.month;
}

bool operator!=(const Date &_lhs, const Date &_rhs) {
    return _lhs.day!=_rhs.day || _lhs.month!=_rhs.month || _lhs.year!=_rhs.year;
}

Purchase::Purchase() {
    price = 0;
//    setPrice(0);
    setTime(0,0,0);
}

Purchase::Purchase(const double &_price, const Time &_time) {
    price = _price;
    setPrice(_price);
    setTime(_time.hours, _time.minutes, _time.seconds);
}

Purchase::Purchase(const double &_price) {
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    int h = now->tm_hour;
    int m = now->tm_min;
    int s = now->tm_sec;
    price = _price;
    setPrice(_price);
    setTime(h, m, s);
}

Purchase::Purchase(const Purchase &_other) {
    setPrice(_other.getPrice());
    setTime(_other.getTime().hours, _other.getTime().minutes, _other.getTime().seconds);
}

double Purchase::getPrice() const {
    return this->price;
}

Time Purchase::getTime() const {
    return this->time;
}

Date Purchase::getDate() const {
    return this->date;
}

void Purchase::setPrice(const double &_value) {
    if (_value < MAX_PARAM1_VALUE && _value >= MIN_PARAM1_VALUE)
        price = _value;
}

void Purchase::setTime(const int& _hours, const int& _minutes, const int& _seconds){
    if (_hours >= MIN_TIME_VALUE && _hours < MAX_HOURS_VALUE) {
        this->time.hours = _hours;
    }
    if (_minutes >= MIN_TIME_VALUE && _minutes < MAX_TIME_VALUE) {
        this->time.minutes = _minutes;
    }
    if (_seconds >= MIN_TIME_VALUE && _seconds < MAX_TIME_VALUE) {
        this->time.seconds = _seconds;
    }
}
