//
// Created by ant1k on 16.3.18.
//

#include "database.h"
#include <set>


void Database::Add(const Date &date, const std::string &event) {
    database.add(date, event);
}

void Database::Print(std::ostream &cout) {
    for (const auto &i : database.dates) {
        for (const auto &j : i.second.sequentialEvents) {
            cout << i.first << j << endl;
        }
    }
}


std::string Database::RemoveIf(const Predicate &predicate) {
    int quantity = 0;
    auto &dates = database.dates;
    Date emptyDate{};
    std::string emptyEvent;
    auto dellAll = predicate(emptyDate, emptyEvent);
    if (dellAll) {
        for (auto &i : dates) {
            quantity += i.second.getSize();
        }
        dates.clear();
    } else {
        for (auto dateIterator = dates.begin(); dateIterator != dates.end();/*++*/) {
            auto &itDate = dateIterator->first;
            const auto dellDate = predicate(itDate, emptyEvent);
            if (dellDate) {
                quantity += dateIterator->second.getSize();
                dateIterator = dates.erase(dateIterator);
            } else {
                auto &itEvent = dateIterator->second.sequentialEvents;
                for (auto eventIt = itEvent.begin(); eventIt != itEvent.end();/*++*/) {
                  const auto dellEvent = predicate(itDate, *eventIt);
                    if (dellEvent) {
                        ++quantity;
                        eventIt = itEvent.erase(eventIt);
                    } else {
                        ++eventIt;
                    }
                }
                ++dateIterator;
            }
        }
    }
    return to_string(quantity);
}


std::vector<pair<Date, std::string>>
Database::FindIf(const Predicate &predicate) {
    std::vector<pair<Date, std::string>> quantity;
    auto &dates = database.dates;
    for (auto &date : dates) {
        auto &events = date.second.sequentialEvents;
        for (auto &event : events) {
            auto const findBy = predicate(date.first, event);
            if (findBy ) {
                quantity.emplace_back(date.first, event);
            }
        }
    }
    return quantity;
}

bool operator<(std::pair<const Date, std::vector<string>> const &lhs, Date const &rhs) {
    return lhs.first < rhs;
}

std::string Database::Last(const Date &date) {
    std::string DateEvent;
    std::ostringstream DateEventStr;
    if (date < (*database.dates.begin()).first || database.dates.empty()) {
        throw invalid_argument(DateEventStr.str());
    } else {
        auto it = database.dates.find(date);
        if (it != database.dates.end()) { // если нашло пишем последнне событие с даты
            if (it->second.getLastEvent().empty()) throw invalid_argument(DateEventStr.str());
            DateEventStr << it->first << it->second.getLastEvent();
        } else { // иначе получаем последнне событие меньшее чем установленное
            auto needDate = database.dates.lower_bound(date);
            --needDate;
            DateEventStr << needDate->first << needDate->second.getLastEvent();
        }
        DateEvent = DateEventStr.str();
    }
    return DateEvent;
}



std::ostream &operator<<(std::ostream &stream, const std::pair<Date, std::string> &dateEvent) {
    stream << dateEvent.first << dateEvent.second;
    return stream;
}

