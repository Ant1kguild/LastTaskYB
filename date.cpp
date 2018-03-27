//
// Created by ant1k on 16.3.18.
//

#include "date.h"

Date::Date() : Year(0), Month(1), Day(1) {}

Date::Date(int _Year, int _Month, int _Day)
        : Year(_Year), Month(_Month), Day(_Day) {}

int Date::getYear() const {
    return Year;
}

int Date::getMonth() const {
    return Month;
}

int Date::getDay() const {
    return Day;
}

void Date::changeYear(const int &cYear) {
    Year = cYear;
}

void Date::changeMonth(const int &cMonth) {
    Month = cMonth;
}

void Date::changeDay(const int &cDay) {
    Day = cDay;
}


std::ostream &operator<<(std::ostream &stream, const Date &data) {
    stream << std::setfill('0');
    stream << std::setw(4) << std::to_string(data.getYear()) << "-";
    stream << std::setw(2) << std::to_string(data.getMonth()) << "-";
    stream << std::setw(2) << std::to_string(data.getDay()) << " ";
    return stream;
}

bool operator!=(const Date &lhs, const Date &rhs) {
    return std::tie(lhs.Year, lhs.Month, lhs.Day) !=
           std::tie(rhs.Year, rhs.Month, rhs.Day);
}

bool operator==(const Date &lhs, const Date &rhs) {
    return std::tie(lhs.Year, lhs.Month, lhs.Day) ==
           std::tie(rhs.Year, rhs.Month, rhs.Day);
}

bool operator<(const Date &lhs, const Date &rhs) {
    return std::tie(lhs.Year, lhs.Month, lhs.Day) <
           std::tie(rhs.Year, rhs.Month, rhs.Day);
}

bool operator<=(const Date &lhs, const Date &rhs) {
    return std::tie(lhs.Year, lhs.Month, lhs.Day) <=
           std::tie(rhs.Year, rhs.Month, rhs.Day);
}

bool operator>(const Date &lhs, const Date &rhs) {
    return std::tie(lhs.Year, lhs.Month, lhs.Day) >
           std::tie(rhs.Year, rhs.Month, rhs.Day);
}

bool operator>=(const Date &lhs, const Date &rhs) {
    return std::tie(lhs.Year, lhs.Month, lhs.Day) >=
           std::tie(rhs.Year, rhs.Month, rhs.Day);
}

bool operator<(const Date &lhs, const pair<Date, pair<std::set<std::string>, std::vector<std::string>>> &rhs) {
    return lhs < rhs.first;
}

bool operator<(const pair<Date, pair<std::set<std::string>, std::vector<std::string>>> &lhs, const Date &rhs) {
    return lhs.first < rhs;
}


std::string &operator<<(std::string str,const Date &data) {
    std::setfill('0');
    std::setw(4);
    str = std::to_string(data.getYear()) + "-";
    std::setw(2);
    str += std::to_string(data.getMonth()) + "-";
    std::setw(2);
    str += std::to_string(data.getDay());
    return str;
}




