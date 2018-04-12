//
// Created by ant1k on 16.3.18.
//

#pragma once


#include "node.h"
#include "date_event.h"
#include <algorithm>
#include <functional>



class Database {
public:
    Database() = default;

    void Add(const Date &date, const std::string &event);

    void Print(std::ostream &stream);

    using Predicate =  std::function<bool(const Date &, const std::string &)>;

    std::string RemoveIf(const Predicate &predicate);

    std::vector<std::string> FindIf(const Predicate &predicate);

    std::string Last(const Date &date);

private:
    DateEvent database;
};
