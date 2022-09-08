#include <iostream>
#include "Date.h"
#include <stdexcept>
using namespace std;

const string Date::monthName[13] = {"", "January", "February", "March", "April", "May", "June",
                              "July", "August", "September", "October", "November", "December"};

const unsigned int Date::daysPerMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Date::Date(unsigned int y, unsigned int m, unsigned int d)
{
    setYear(y);
    setMonth(m);
    setDay(d);
}

void Date::setYear(unsigned int y)
{
    year = y;
}

unsigned int Date::getYear() const
{
    return year;
}

void Date::setMonth(unsigned int m)
{
    if(m >= 1 && m <= 12)
        month = m;
    else
        throw std::invalid_argument("Invalid month!");
}

unsigned int Date::getMonth() const
{
    return month;
}

void Date::setDay(unsigned int d)
{
    if(checkDay(d))
        day = d;
    else
        throw std::invalid_argument("Invalid day for current month and year!");
}

unsigned int Date::getDay() const
{
    return day;
}

bool Date::leap(unsigned int testYear)
{
    if (testYear % 400 == 0 ||
       (testYear % 4 == 0 && testYear % 100 != 0))
       return true;
    else
        return false;
}

bool Date::endOfMonth(unsigned int testDay)
{
    if(leap(year) && month == 2)
        return testDay == 29;
    else
        return testDay == Date::daysPerMonth[month];
}

void Date::print() const
{
    std::cout << year << "/" << month << "/" << day << std::endl;
}

bool Date::checkDay(unsigned int testDay) const
{

    if(testDay <= daysPerMonth[month])
        return true;
    if((month == 2 && testDay == 29) &&
       (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)))
        return true;
    return false;
}

void Date::increament()
{
    if(!endOfMonth(day))
        ++day;
    else if(month != 12)
    {
        ++month;
        day = 1;
    }
    else
    {
        ++year;
        month = day = 1;
    }
}

Date &Date::operator++()
{
    increament();
    return *this;
}

Date Date::operator++(int)
{
    Date t = *this;
    increament();
    return t;
}

Date &Date::operator+=(unsigned int daysToAdd)
{
    for(unsigned int i = 0; i < daysToAdd; ++i)
        increament();
    return *this;
}

bool Date::operator==(Date d)
{
    if(d.getDay() == day && d.getMonth() == month && d.getYear() == year)
        return true;
    else
        return false;
}
ostream &operator<<(ostream &output, Date date)
{
    output << date.day << "." << date.month << "." << date.year;
    return output;
}

istream &operator>>(istream &input, Date& d)
{
    int yy, mm, dd;
    input >> yy >> mm >> dd;
    d.setYear(yy);
    d.setMonth(mm);
    d.setDay(dd);
    return input;
}
