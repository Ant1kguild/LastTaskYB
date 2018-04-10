//
// Created by ant1k on 29.3.18.
//

#include "list_of_events.h"

std::set<std::string, std::less<>>::iterator listOfEvents::findSetEvent(const std::string &event) {
    auto it = orderedEvents.find(event);
    return it;
}

std::vector<std::string>::iterator listOfEvents::findVecEvent(const std::string &event)  {
    auto it = find(sequentialEvents.begin(), sequentialEvents.end(), event);
    return it;
}

void listOfEvents::addEvent(const std::string &event) {
    if (findSetEvent(event) == orderedEvents.end()) { // если не нашло событий внести
        orderedEvents.insert(event);
        sequentialEvents.emplace_back(event);
    }
}

void listOfEvents::delEvent(std::vector<std::string>::iterator &it) {
    orderedEvents.erase(*it);
    it = sequentialEvents.erase(it);
}

std::string listOfEvents::getLastEvent()  {
    return sequentialEvents.back();
}

bool listOfEvents::isEmpty()  {
    return (orderedEvents.empty() && sequentialEvents.empty());
}

unsigned long listOfEvents::getSize() {
    return sequentialEvents.size();
}




