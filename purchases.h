#pragma once

#ifndef OOP_PURCHASES_H
#define OOP_PURCHASES_H


#define MIN_PARAM1_VALUE 0
#define MAX_PARAM1_VALUE 1000
#define MIN_TIME_VALUE 0
#define MAX_HOURS_VALUE 24
#define MAX_TIME_VALUE 60


#include <iostream>
#include <string>


struct Time{
public:
    Time();

    Time(const int& _hours, const int& _minutes, const int& _seconds);
    int hours, minutes, seconds;
};

bool operator >=(const Time& _lhs, const Time& _rhs);
bool operator ==(const Time& _lhs, const Time& _rhs);
bool operator !=(const Time& _lhs, const Time& _rhs);
std::ostream& operator<<(std::ostream& out, const Time& _value);

struct Date{
public:
    Date();

    int day, month, year;
};

bool operator >=(const Date& _lhs, const Date& _rhs);
bool operator ==(const Date& _lhs, const Date& _rhs);
bool operator !=(const Date& _lhs, const Date& _rhs);

class Purchase{

public:
    Purchase();

    Purchase(const double &_price);

    Purchase(const double& _price, const Time & _time);

    Purchase(const Purchase & _other);

    virtual double getPrice() const;

    virtual Time getTime() const;

    Date getDate() const;

    virtual void setPrice(const double& _value);

//    void setTime(const Time& _value);
    virtual void setTime(const int& _hours, const int& _minutes, const int& _seconds);

private:
    double price;
    Time time;
    Date date;
};

#endif //OOP_PURCHASES_H
