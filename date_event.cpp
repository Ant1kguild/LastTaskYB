//
// Created by ant1k on 1.cpp.4.18.
//

#include "date_event.h"

std::map<Date, listOfEvents>::iterator DateEvent::find(Date const &date) { return dates.find(date); }

void DateEvent::add(Date const &date, string const &event) {
    if (event.empty()) return;
    auto dateIterator = find(date);
    const bool hasDate = dateIterator != dates.end();
    if (!hasDate) {
        listOfEvents new_events;
        new_events.addEvent(event);
        dates.insert(make_pair(date, new_events));
    } else {
        dateIterator->second.addEvent(event);
    }
}
