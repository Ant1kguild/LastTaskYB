//
// Created by ant1k on 1.4.18.
//


#pragma once;

#include "list_of_events.h"
#include "date.h"
#include <map>
#include <set>
#include <vector>

struct DateEvent {
    std::map<Date, listOfEvents>::iterator
    find(Date const &date);

    void add(Date const &date, string const &event);

    std::map<Date, listOfEvents> dates;
};
