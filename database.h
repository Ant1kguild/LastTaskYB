//
// Created by ant1k on 16.3.18.
//

#pragma once

#include "date.h"
#include "node.h"
#include <map>
#include <algorithm>
#include <functional>
#include <set>


struct DateEvent {
    std::map<Date, std::vector<string>> dates;

    std::map<Date, std::vector<string>>::iterator
    find(Date const &date) { return dates.find(date); }

    void add(Date const &date, string const &event) {
        auto dateIterator = find(date);

        const bool hasDate = dateIterator != dates.end();

        if (!hasDate) {
            dates.insert(make_pair(date, vector<string>{event}));
            return;
        }

        const bool hasEvent = std::find(dateIterator->second.begin(), dateIterator->second.end(), event) != dateIterator->second.end();

        if (hasEvent) {
            return;
        } else {
            dateIterator->second.emplace_back(event);
        }

    }
};

enum class Cursor {
    NEXT_DATE,
    NEXT_EVENT,
    THIS
};


class Database {
public:
    void Add(const Date &date, const std::string &event);

    void Print(std::ostream &cout);

    using Predicate =  std::function<PredicateIt(const Date &, const std::string &)>;

    std::string RemoveIf(const Predicate &predicate);

    std::vector<pair<Date, std::string>> FindIf(const Predicate &predicate);

    friend void TestAddDateEvent();

    std::string Last(const Date &date);

private:
    DateEvent database;

    Cursor findByPredicate(const Predicate &function,
                           map<Date, std::vector<std::string>>::iterator dateIterator,
                           std::vector<string>::iterator eventIterator);

};


std::ostream &operator<<(std::ostream &stream, const std::pair<Date, std::string> &map);

void TestAddDateEvent();