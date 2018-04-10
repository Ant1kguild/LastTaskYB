#include <iostream>
#include <stdexcept>
#include <sstream>
#include <functional>
#include <algorithm>
#include <cctype>
#include <locale>


#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"


using namespace std;

void TestDataBaseCondition();

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

string ParseEvent(istream &is) {
    string event;
    getline(is, event);
    ltrim(event);
    return event;
}

void TestAll();

int main() {
    TestAll();

    Database db;

    for (string line; getline(cin, line);) {
        istringstream is(line);
        string command;
        is >> command;
        if (command == "Add") {
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        } else if (command == "Print") {
            db.Print(cout);
        } else if (command == "Del") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date &date, const string &event) {
                return condition->Evaluate(date, event);
            };
            auto count = db.RemoveIf(predicate);
            cout << "Removed " << count << " entries" << endl;
        } else if (command == "Find") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date &date, const string &event) {
                return condition->Evaluate(date, event);
            };

            const auto entries = db.FindIf(predicate);
            for (const auto &entry : entries) {
                cout << entry << endl;
            }
            cout << "Found " << entries.size() << " entries" << endl;
        } else if (command == "Last") {
            try {
                cout << db.Last(ParseDate(is)) << endl;
            } catch (invalid_argument &) {
                cout << "No entries" << endl;
            }
        } else if (command.empty()) {
            continue;
        } else {
            throw logic_error("Unknown command: " + command);
        }

    }

    return 0;
}

void TestParseEvent() {
    {
        istringstream is("event");
        JUnit::AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
    }
    {
        istringstream is("   sport event ");
        JUnit::AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
    }
    {
        istringstream is("  first event  \n  second event");
        vector<string> events;
        events.push_back(ParseEvent(is));
        events.push_back(ParseEvent(is));
        JUnit::AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
    }
}

void TestAll() {
//    TestRunner tr;
//    tr.RunTest(TestDataBaseCondition, "TestDataBaseCondition");
//    tr.RunTest(TestParseEvent, "TestParseEvent");
//    tr.RunTest(TestDateParser, "TestDateParser");
//    tr.RunTest(TestComparingDates, "TestComparingDates");
//    tr.RunTest(TestParseCondition, "TestParseCondition");
//    tr.RunTest(TestAddDateEvent, "TestAddDateEvent");
//    tr.RunTest(TestAddEvent, "TestAddEvent");
//    tr.RunTest(TestDelEvent, "TestDelEvent");
//    tr.RunTest(TestGetLastEvent, "TestGetLastEvent");
}
