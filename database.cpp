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
    const auto dellAll = predicate(emptyDate, emptyEvent);
    if (dellAll) {
        for (auto &i : dates) {
            quantity += i.second.getSize();
        }
        dates.clear();
    } else {
        for (auto it = dates.begin(); it != dates.end();/*++*/) {
            const auto dellDate = predicate(it->first, emptyEvent);
            if (dellDate) {
                quantity += it->second.getSize();
                it = dates.erase(it);
            } else {
                auto &eventsV = it->second.sequentialEvents;
                auto &eventsS = it->second.orderedEvents;
                for (auto itEvent = eventsV.begin(); itEvent != eventsV.end(); /*++*/) {
                    const auto dellEvent = predicate(it->first, *itEvent);
                    if (dellEvent) {
                        itEvent = eventsV.erase(itEvent);
                        eventsS.erase(*itEvent);
                        ++quantity;
                    } else {
                        ++itEvent;
                    }
                }
                ++it;
            }
        }
    }
    return to_string(quantity);
}


std::vector<pair<Date, string>> Database::FindIf(const Predicate &predicate) {
    std::vector<pair<Date, string>> quantity;
    Date emptyDate{};
    std::string emptyEvent;
    const auto findAll = predicate(emptyDate, emptyEvent);
    const auto &dates = database.dates;
    if (findAll) {
        for (const auto &itPair : dates) {
            const auto &myDate = itPair.first;
            const auto &myEvents = itPair.second.sequentialEvents;
            for (const auto &itEvent : myEvents) {
                quantity.emplace_back(make_pair(myDate, itEvent));
            }
        }
    } else {
        for (const auto &itPair : dates) {
            const auto &myDate = itPair.first;
            const auto &myEvents = itPair.second;
            const auto findAllEvent = predicate(myDate, emptyEvent);
            if (findAllEvent) {
                getAllEvents(myDate, myEvents, quantity);
            } else {
                const auto &sequentialEvents = myEvents.sequentialEvents;
                for (const auto &Event : sequentialEvents) {
                    const auto findEvent = predicate(myDate, Event);
                    if (findEvent) quantity.emplace_back(make_pair(myDate, Event));
                }
            }
        }
    }
    return quantity;
}


bool operator<(std::pair<const Date, std::vector<string>> const &lhs, Date const &rhs) {
    return lhs.first < rhs;
}

std::string Database::Last(const Date &date) {
    Date emptyDate{};
    std::string DateEvent;
    std::ostringstream DateEventStr;
    auto needDate = database.dates.lower_bound(date);
    const auto firstDate = getFirstDate();
    if (date < firstDate) {
        throw invalid_argument(DateEventStr.str());
    } else {
        auto it = database.dates.find(date);
        if (it != database.dates.end()) { // если нашло пишем последнне событие с даты
            DateEventStr << it->first << it->second.getLastEvent();
        } else { // иначе получаем последнне событие меньшее чем установленное
            --needDate;
            DateEventStr << needDate->first << needDate->second.getLastEvent();
        }
        DateEvent = DateEventStr.str();
    }
    return DateEvent;
}

void Database::deleteDateByConditions(const Database::Predicate &function,
                                      const Date &date,
                                      listOfEvents &events,
                                      int &quantity) {
    for (auto it = events.sequentialEvents.begin(); it != events.sequentialEvents.end(); /*it++*/) {
        const std::string needEvent = *it;
        const auto dellEvent = function(date, needEvent);
        if (dellEvent) {
            events.delEvent(it);
            ++quantity;
        } else {
            ++it;
        }
    }
}


void Database::getAllEvents(const Date &date,
                            const listOfEvents &DatesEvents,
                            vector<pair<Date, string>> &quantity) {
    for (const auto &event : DatesEvents.sequentialEvents) {
        quantity.emplace_back(make_pair(date, event));
    }
}

Date Database::getFirstDate() {
    Date emptyDate{};
    const auto firstDate = database.dates.lower_bound(emptyDate);
    if (firstDate == database.dates.end()) throw invalid_argument("");
    return firstDate->first;
}


std::ostream &operator<<(std::ostream &stream, const std::pair<Date, std::string> &dateEvent) {
    stream << dateEvent.first << dateEvent.second;
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const std::pair<Date, listOfEvents> &dateEvent) {
    for (const auto &it : dateEvent.second.sequentialEvents) {
        stream << dateEvent.first << it << "\n";
    }
    return stream;
}