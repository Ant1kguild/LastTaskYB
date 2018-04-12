//
// Created by ant1k on 16.3.18.
//

#include "database.h"

void Database::Add(const Date &date, const std::string &event) {
    database.add(date, event);
}

void Database::Print(std::ostream &stream) {
    for (const auto &itPair : database.dates) {
        for (const auto &itEvent : itPair.second.sequentialEvents) {
            if (!itEvent.empty()) stream << itPair.first << " " << itEvent << endl;
        }
    }
}

std::string Database::RemoveIf(const Predicate &predicate) {
    uint64_t quantity = 0;
    auto &dates = database.dates;
    for (auto it = dates.begin(); it != dates.end(); ++it) {
        auto &date = it->first;
        auto &eventsV = it->second.sequentialEvents;
        auto &eventsS = it->second.orderedEvents;
        auto dellEvent = remove_if(eventsV.begin(), eventsV.end(), [&](const auto &event) {
            if (predicate(date, event)) {
                ++quantity;
                eventsS.erase(event);
                return true;
            }
            return false;
        });
        eventsV.erase(dellEvent, eventsV.end());
    }
    { // очищаем даты в которых нет событий
        auto it = dates.begin();
        while (it != dates.end()) {
            if (it->second.isEmpty()) {
                it = dates.erase(it);
            } else {
                ++it;
            };
        }
    }
    return to_string(quantity);
}


std::vector<std::string> Database::FindIf(const Predicate &predicate) {
    std::vector<std::string> quantity;
    std::stringstream buffer;
    for(const auto& date : database.dates)
        for(const auto& event : date.second.sequentialEvents)
            if (predicate(date.first, event)) {
                buffer << date.first << " " << event;
                quantity.push_back(buffer.str());
                buffer.str(std::string());
            }
    return quantity;
}


std::string Database::Last(const Date &date) {
    const auto &firstDate = database.dates.begin()->first;
    if (database.dates.empty() || date < database.dates.begin()->first) {
        throw invalid_argument("");
    } else {
        std::stringstream buffer;
        auto it = database.dates.upper_bound(date);
        it = prev(it);
        buffer << it -> first << " " << it -> second.sequentialEvents.back();
        return (buffer.str());
    }
}







