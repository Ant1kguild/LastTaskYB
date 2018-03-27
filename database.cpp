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
        for (const auto &j : i.second) {
            cout << i.first << j << endl;
        }
    }
}


std::string Database::RemoveIf(const Predicate &predicate) {
    int quantity = 0;
    auto &dates = database.dates;
    for (auto dateIterator = dates.begin(); dateIterator != dates.end();) {
        bool eraseDate = false;
        auto &events = dateIterator->second;
        for (auto eventIterator = events.begin(); eventIterator != events.end();) {
            auto const findBy = findByPredicate(predicate, dateIterator, eventIterator);
            if (findBy == Cursor::NEXT_DATE) {
                break;
            }
            if (findBy == Cursor::THIS) {
                quantity++;
                eventIterator = events.erase(eventIterator);
                if (events.empty()) {
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
        auto &events = dateIterator->second;
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
        auto needDate = database.dates.lower_bound(date);
        if (needDate == database.dates.end()) { // если нашло значение большее либо равное date
            --needDate;
        }
        DateEventStr << needDate->first << needDate->second.back();
        DateEvent = DateEventStr.str();
    }

    return DateEvent;

}


void TestAddDateEvent() {
    {
//        Database db;
//        std::map<Date, std::vector<std::string>> test1;
//        test1[{1985, 10, 28}].emplace_back("My dr");
//        db.Add({1985, 10, 28}, "My dr");
//        JUnit::AssertEqual(test1, db.database, "Test #1");
//        JUnit::Assert((!db.database.empty()), "Test #1.1");
//        JUnit::Assert((db.database.size() == 1), "Test #1.2");
//        JUnit::Assert((db.database.size() < 2), "Test #1.3");
//        JUnit::Assert(!db.database.at({1985, 10, 28}).first.empty(), "Test #1.4.1");
//        JUnit::Assert(!db.database.at({1985, 10, 28}).second.empty(), "Test #1.4.2");
//        JUnit::Assert(db.database.at({1985, 10, 28}).first.size() == 1, "Test #1.5.1");
//        JUnit::Assert(db.database.at({1985, 10, 28}).second.size() == 1, "Test #1.5.2");
//        JUnit::Assert(db.database.at({1985, 10, 28}).first.size() < 2, "Test #1.6.1");
//        JUnit::Assert(db.database.at({1985, 10, 28}).second.size() < 2, "Test #1.6.2");
//        db.Add({1985, 10, 28}, "My dr");
//        JUnit::AssertEqual(test1, db.database, "Test #2");
//        JUnit::Assert((!db.database.empty()), "Test #2.1");
//        JUnit::Assert((db.database.size() == 1), "Test #2.2");
//        JUnit::Assert((db.database.size() < 2), "Test #2.3");
//        JUnit::Assert(!db.database.at({1985, 10, 28}).first.empty(), "Test #2.4.1");
//        JUnit::Assert(!db.database.at({1985, 10, 28}).second.empty(), "Test #2.4.2");
//        JUnit::Assert(db.database.at({1985, 10, 28}).first.size() == 1, "Test #2.5.1");
//        JUnit::Assert(db.database.at({1985, 10, 28}).second.size() == 1, "Test #2.5.2");
//        JUnit::Assert(db.database.at({1985, 10, 28}).first.size() < 2, "Test #2.6.1");
//        JUnit::Assert(db.database.at({1985, 10, 28}).second.size() < 2, "Test #2.6.2");
//        db.Add({1985, 10, 28}, "My dr");
//        JUnit::AssertEqual(test1, db.database, "Test #3");
//        JUnit::Assert((!db.database.empty()), "Test #3.1");
//        JUnit::Assert((db.database.size() == 1), "Test #3.2");
//        JUnit::Assert((db.database.size() < 2), "Test #3.3");
//        JUnit::Assert(!db.database.at({1985, 10, 28}).first.empty(), "Test #3.4.1");
//        JUnit::Assert(!db.database.at({1985, 10, 28}).second.empty(), "Test #3.4.2");
//        JUnit::Assert(db.database.at({1985, 10, 28}).first.size() == 1, "Test #3.5.1");
//        JUnit::Assert(db.database.at({1985, 10, 28}).second.size() == 1, "Test #3.5.2");
//        JUnit::Assert(db.database.at({1985, 10, 28}).first.size() < 2, "Test #3.6.1");
//        JUnit::Assert(db.database.at({1985, 10, 28}).second.size() < 2, "Test #3.6.2");
//        test1[{1985, 10, 28}].emplace_back("My Day");
//        db.Add({1985, 10, 28}, "My dr");
//        db.Add({1985, 10, 28}, "My Day");
//        db.Add({1985, 10, 28}, "My Day");
//        db.Add({1985, 10, 28}, "My Day");
//        JUnit::AssertEqual(test1, db.database, "Test #4");
//        JUnit::Assert((!db.database.empty()), "Test #4.1");
//        JUnit::Assert((db.database.size() == 1), "Test #4.2");
//        JUnit::Assert((db.database.size() < 2), "Test #4.3");
//        JUnit::Assert(!db.database.at({1985, 10, 28}).first.empty(), "Test #4.4.1");
//        JUnit::Assert(!db.database.at({1985, 10, 28}).second.empty(), "Test #4.4.2");
//        JUnit::Assert(db.database.at({1985, 10, 28}).first.size() == 1, "Test #4.5.1");
//        JUnit::Assert(db.database.at({1985, 10, 28}).second.size() == 1, "Test #4.5.2");
//        JUnit::Assert(db.database.at({1985, 10, 28}).first.size() < 3, "Test #4.6.1");
//        JUnit::Assert(db.database.at({1985, 10, 28}).second.size() < 3, "Test #4.6.2");
    }


}


Cursor Database::findByPredicate(const Predicate &function,
                                 map<Date, std::vector<std::string>>::iterator dateIterator,
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


std::ostream &operator<<(std::ostream &stream, const std::pair<Date, std::string> &map) {
    stream << map.first << map.second;
    return stream;
}
