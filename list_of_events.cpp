//
// Created by ant1k on 29.3.18.
//

#include "list_of_events.h"

bool listOfEvents::findSetEvent(const std::string &event) {
    return orderedEvents.count(event) != 0;
}

void listOfEvents::addEvent(const std::string &event) {
    if (!findSetEvent(event)) { // если не нашло событий внести
        orderedEvents.insert(event);
        sequentialEvents.emplace_back(event);
    }
}

void listOfEvents::delEvent(std::vector<std::string>::iterator &it) {
    orderedEvents.erase(*it);
    it = sequentialEvents.erase(it);
}

std::string listOfEvents::getLastEvent() {
    return sequentialEvents.back();
}

bool listOfEvents::isEmpty() {
    return (orderedEvents.empty() && sequentialEvents.empty());
}

listOfEvents::listOfEvents(const std::string &event) {
    orderedEvents.insert(event);
    sequentialEvents.emplace_back(event);
}





