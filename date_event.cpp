//
// Created by ant1k on 1.cpp.4.18.
//

#include "date_event.h"

std::map<Date, listOfEvents>::iterator DateEvent::find(Date const &date) { return dates.find(date); }

void DateEvent::add(Date const &date, string const &event) {
    if (event.empty() || event.find_first_not_of(' ') == std::string::npos) return;
    auto itDate = find(date);
    const bool dateAvailability = itDate != dates.end();
    if (!dateAvailability) {
        listOfEvents new_events(event);
        dates.insert(make_pair(date, new_events));
    } else {
        itDate->second.addEvent(event);
    }
}
