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
    for (auto dateIterator = dates.begin(); dateIterator != dates.end();) {
        bool eraseDate = false;
        auto &events = dateIterator->second.sequentialEvents;
        for (auto eventIterator = events.begin(); eventIterator != events.end();) {
            auto const findBy = findByPredicate(predicate, dateIterator, eventIterator);
            if (findBy == Cursor::NEXT_DATE) {
                break;
            }
            if (findBy == Cursor::THIS) {
                quantity++;
                dateIterator->second.delEvent(*eventIterator);
                if (dateIterator->second.isEmpty()) {
                    dateIterator = dates.erase(dateIterator);
                    eraseDate = true;
                }

            } else {
                ++eventIterator;
            }
        }
        if (!eraseDate) {
            ++dateIterator;
        }
    }
    return to_string(quantity);
}


std::vector<pair<Date, std::string>>
Database::FindIf(const Predicate &predicate) {
    std::vector<pair<Date, std::string>> quantity;
    auto &dates = database.dates;
    for (auto dateIterator = dates.begin(); dateIterator != dates.end(); ++dateIterator) {
        auto &events = dateIterator->second.sequentialEvents;
        for (auto eventIterator = events.begin(); eventIterator != events.end(); ++eventIterator) {
            auto const findBy = findByPredicate(predicate, dateIterator, eventIterator);
            if (findBy == Cursor::NEXT_DATE) {
                break;
            }
            if (findBy == Cursor::THIS) {
                quantity.emplace_back(dateIterator->first, *eventIterator);
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

Cursor Database::findByPredicate(const Predicate &function,
                                 map<Date, listOfEvents>::iterator dateIterator,
                                 std::vector<string>::iterator eventIterator) {
    auto result = function(dateIterator->first, *eventIterator);
    switch (result.date) {
        case Condition::Any:
        case Condition::This:
            switch (result.event) {
                case Condition::Any:
                case Condition::This:
                    return Cursor::THIS;
                case Condition::None:
                    return Cursor::NEXT_EVENT;
            }
        case Condition::None:
            return Cursor::NEXT_DATE;

    }
}


std::ostream &operator<<(std::ostream &stream, const std::pair<Date, std::string> &dateEvent) {
    stream << dateEvent.first << dateEvent.second;
    return stream;
}

