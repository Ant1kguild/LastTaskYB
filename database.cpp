//
// Created by ant1k on 16.3.18.
//

#include "database.h"
#include <set>


void Database::Add(const Date &date, const std::string &event) {
    database.add(date, event);
}

void Database::Print(std::ostream &cout) {
    for (const auto &itPair : database.dates) {
        for(const auto &itEvent : itPair.second.sequentialEvents) {
            cout << itPair.first << " " << itEvent << endl;
        }
    }
}


std::string Database::RemoveIf(const Predicate &predicate) {
    int quantity = 0;
    auto &dates = database.dates;
    for (auto it = dates.begin(); it != dates.end();/*++*/) {
        auto &myDate = it->first;
        auto &myEventsV = it->second.sequentialEvents;
        auto &myEventsS = it->second.orderedEvents;
        for (auto event = myEventsV.begin(); event != myEventsV.end();/*++*/) {
            const auto delEvent = predicate(myDate, *event);
            if (delEvent) {
                myEventsS.erase(*event);
                event = myEventsV.erase(event);
                ++quantity;
            } else {
                ++event;
            }
        }
        if (it->second.isEmpty()) {
            it = dates.erase(it);
        } else {
            ++it;
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

std::pair<Date, std::string> Database::Last(const Date &date) {
    if (database.dates.empty()) {
        throw invalid_argument("");
    } else {
        auto it = database.dates.find(date);
        if (it != database.dates.end()) { // если нашло пишем последнне событие с даты
            return {it->first, it->second.sequentialEvents.back()};
        } else { // иначе получаем последнне событие меньшее чем установленное
            auto needDate = database.dates.lower_bound(date);
            if (needDate == database.dates.begin()) throw invalid_argument("");
            --needDate;
            return {needDate->first, needDate->second.sequentialEvents.back()};
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


std::ostream &operator<<(std::ostream &stream, const std::pair<Date, std::string> &dateEvent) {
    stream << dateEvent.first << " " << dateEvent.second;
}