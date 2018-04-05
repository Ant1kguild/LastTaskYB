//
// Created by ant1k on 16.3.18.
//

#pragma once


#include "node.h"
#include "date_event.h"
#include <algorithm>
#include <functional>


enum class Cursor {
    NEXT_DATE,
    NEXT_EVENT,
    THIS
};


class Database {
public:
    void Add(const Date &date, const std::string &event);

    void Print(std::ostream &cout);

    using Predicate =  std::function<bool(const Date &, const std::string &)>;

    std::string RemoveIf(const Predicate &predicate);

    std::vector<pair<Date, std::string>> FindIf(const Predicate &predicate);

    friend void TestAddDateEvent();

    std::string Last(const Date &date);

private:
    DateEvent database;
};

std::ostream &operator<<(std::ostream &stream, const std::pair<Date, std::string> &dateEvent);


void TestAddDateEvent();