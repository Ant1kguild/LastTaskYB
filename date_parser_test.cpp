//
// Created by ant1k on 16.3.18.
//

#include "date.h"


void TestDateParser() {
    vector<Date> date = {Date(2017, 11, 18), Date(1985, 10, 28), Date(1987, 10, 2)};
    {
        istringstream is("2017-11-18");
        JUnit::AssertEqual(ParseDate(is), date.at(0), "Date 2017-11-18");
    }
    {
        istringstream is("1985-10-28");
        JUnit::AssertEqual(ParseDate(is), date.at(1), "Date 1985-10-28");

    }
    {
        istringstream is("1987-10-2");
        JUnit::AssertEqual(ParseDate(is), date.at(2), "Date 1987-10-02");
    }
}