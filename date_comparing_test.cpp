//
// Created by ant1k on 18.3.18.
//

#include "date.h"

std::string getDate(Date &date) {
    return "Date(" + to_string(date.getYear()) + ","
           + to_string(date.getMonth()) + ","
           + to_string(date.getDay()) + ")";
}

void TestComparingDates() {
    std::vector<Date> dates1{Date(1985, 10, 28), Date(1985, 10, 28), Date(1985, 10, 29), Date(1985, 10, 27)},
            dates2{Date(1987, 10, 2), Date(1987, 10, 2), Date(1987, 10, 3), Date(1987, 10, 1)},
            dates3{Date(0, 0, 2), Date(0, 0, 2), Date(0, 0, 3), Date(0, 0, 1)},
            dates4{Date(0, 2, 2), Date(0, 2, 2), Date(0, 3, 2), Date(0, 1, 2)},
            dates5{Date(2, 2, 2), Date(2, 2, 2), Date(3, 2, 2), Date(1, 2, 2)};
    {
        JUnit::AssertEqual(dates1.at(0), dates1.at(1), getDate(dates1.at(0)) + "==" + getDate(dates1.at(1)) + "Test #1");
        JUnit::Assert((dates1.at(0) != dates1.at(2)), getDate(dates1.at(0)) + "!=" + getDate(dates1.at(2)) + "Test #2");
        JUnit::Assert((dates1.at(0) != dates1.at(3)), getDate(dates1.at(0)) + "!=" + getDate(dates1.at(3)) + "Test #3");
        JUnit::Assert((dates1.at(2) != dates1.at(3)), getDate(dates1.at(2)) + "!=" + getDate(dates1.at(3)) + "Test #4");
        JUnit::Assert((dates1.at(0) < dates1.at(2)), getDate(dates1.at(0)) + "<" + getDate(dates1.at(2)) + "Test #5");
        JUnit::Assert((dates1.at(0) <= dates1.at(1)), getDate(dates1.at(0)) + "<=" + getDate(dates1.at(1)) + "Test #6");
        JUnit::Assert((dates1.at(0) <= dates1.at(2)), getDate(dates1.at(0)) + "<=" + getDate(dates1.at(2)) + "Test #7");
        JUnit::Assert((dates1.at(0) > dates1.at(3)), getDate(dates1.at(0)) + ">" + getDate(dates1.at(3)) + "Test #8");
        JUnit::Assert((dates1.at(0) >= dates1.at(1)), getDate(dates1.at(0)) + ">=" + getDate(dates1.at(1)) + "Test #9");
        JUnit::Assert((dates1.at(0) >= dates1.at(3)), getDate(dates1.at(0)) + ">=" + getDate(dates1.at(3)) + "Test #10");
    }
    {
        JUnit::AssertEqual(dates2.at(0), dates2.at(1), getDate(dates2.at(0)) + "==" + getDate(dates2.at(1)) + "Test #11");
        JUnit::Assert((dates2.at(0) != dates2.at(2)), getDate(dates2.at(0)) + "!=" + getDate(dates2.at(2)) + "Test #12");
        JUnit::Assert((dates2.at(0) != dates2.at(3)), getDate(dates2.at(0)) + "!=" + getDate(dates2.at(3)) + "Test #13");
        JUnit::Assert((dates2.at(2) != dates2.at(3)), getDate(dates2.at(2)) + "!=" + getDate(dates2.at(3)) + "Test #14");
        JUnit::Assert((dates2.at(0) < dates2.at(2)), getDate(dates2.at(0)) + "<" + getDate(dates2.at(2)) + "Test #15");
        JUnit::Assert((dates2.at(0) <= dates2.at(1)), getDate(dates2.at(0)) + "<=" + getDate(dates2.at(1)) + "Test #16");
        JUnit::Assert((dates2.at(0) <= dates2.at(2)), getDate(dates2.at(0)) + "<=" + getDate(dates2.at(2)) + "Test #17");
        JUnit::Assert((dates2.at(0) > dates2.at(3)), getDate(dates2.at(0)) + ">" + getDate(dates2.at(3)) + "Test #18");
        JUnit::Assert((dates2.at(0) >= dates2.at(1)), getDate(dates2.at(0)) + ">=" + getDate(dates2.at(1)) + "Test #19");
        JUnit::Assert((dates2.at(0) >= dates2.at(3)), getDate(dates2.at(0)) + ">=" + getDate(dates2.at(3)) + "Test #20");
    }
    {
        JUnit::AssertEqual(dates3.at(0), dates3.at(1), getDate(dates3.at(0)) + "==" + getDate(dates3.at(1)) + "Test #21");
        JUnit::Assert((dates3.at(0) != dates3.at(2)), getDate(dates3.at(0)) + "!=" + getDate(dates3.at(2)) + "Test #22");
        JUnit::Assert((dates3.at(0) != dates3.at(3)), getDate(dates3.at(0)) + "!=" + getDate(dates3.at(3)) + "Test #23");
        JUnit::Assert((dates3.at(2) != dates3.at(3)), getDate(dates3.at(2)) + "!=" + getDate(dates3.at(3)) + "Test #24");
        JUnit::Assert((dates3.at(0) < dates3.at(2)), getDate(dates3.at(0)) + "<" + getDate(dates3.at(2)) + "Test #25");
        JUnit::Assert((dates3.at(0) <= dates3.at(1)), getDate(dates3.at(0)) + "<=" + getDate(dates3.at(1)) + "Test #26");
        JUnit::Assert((dates3.at(0) <= dates3.at(2)), getDate(dates3.at(0)) + "<=" + getDate(dates3.at(2)) + "Test #27");
        JUnit::Assert((dates3.at(0) > dates3.at(3)), getDate(dates3.at(0)) + ">" + getDate(dates3.at(3)) + "Test #28");
        JUnit::Assert((dates3.at(0) >= dates3.at(1)), getDate(dates3.at(0)) + ">=" + getDate(dates3.at(1)) + "Test #29");
        JUnit::Assert((dates3.at(0) >= dates3.at(3)), getDate(dates3.at(0)) + ">=" + getDate(dates3.at(3)) + "Test #30");
    }
    {
        JUnit::AssertEqual(dates4.at(0), dates4.at(1), getDate(dates4.at(0)) + "==" + getDate(dates4.at(1)) + "Test #31");
        JUnit::Assert((dates4.at(0) != dates4.at(2)), getDate(dates4.at(0)) + "!=" + getDate(dates4.at(2)) + "Test #32");
        JUnit::Assert((dates4.at(0) != dates4.at(3)), getDate(dates4.at(0)) + "!=" + getDate(dates4.at(3)) + "Test #33");
        JUnit::Assert((dates4.at(2) != dates4.at(3)), getDate(dates4.at(2)) + "!=" + getDate(dates4.at(3)) + "Test #34");
        JUnit::Assert((dates4.at(0) < dates4.at(2)), getDate(dates4.at(0)) + "<" + getDate(dates4.at(2)) + "Test #35");
        JUnit::Assert((dates4.at(0) <= dates4.at(1)), getDate(dates4.at(0)) + "<=" + getDate(dates4.at(1)) + "Test #36");
        JUnit::Assert((dates4.at(0) <= dates4.at(2)), getDate(dates4.at(0)) + "<=" + getDate(dates4.at(2)) + "Test #37");
        JUnit::Assert((dates4.at(0) > dates4.at(3)), getDate(dates4.at(0)) + ">" + getDate(dates4.at(3)) + "Test #38");
        JUnit::Assert((dates4.at(0) >= dates4.at(1)), getDate(dates4.at(0)) + ">=" + getDate(dates4.at(1)) + "Test #39");
        JUnit::Assert((dates4.at(0) >= dates4.at(3)), getDate(dates4.at(0)) + ">=" + getDate(dates4.at(3)) + "Test #40");
    }

    {
        JUnit::AssertEqual(dates5.at(0), dates5.at(1), getDate(dates5.at(0)) + "==" + getDate(dates5.at(1)) + "Test #41");
        JUnit::Assert((dates5.at(0) != dates5.at(2)), getDate(dates5.at(0)) + "!=" + getDate(dates5.at(2)) + "Test #42");
        JUnit::Assert((dates5.at(0) != dates5.at(3)), getDate(dates5.at(0)) + "!=" + getDate(dates5.at(3)) + "Test #43");
        JUnit::Assert((dates5.at(2) != dates5.at(3)), getDate(dates5.at(2)) + "!=" + getDate(dates5.at(3)) + "Test #44");
        JUnit::Assert((dates5.at(0) < dates5.at(2)), getDate(dates5.at(0)) + "<" + getDate(dates5.at(2)) + "Test #45");
        JUnit::Assert((dates5.at(0) <= dates5.at(1)), getDate(dates5.at(0)) + "<=" + getDate(dates5.at(1)) + "Test #46");
        JUnit::Assert((dates5.at(0) <= dates5.at(2)), getDate(dates5.at(0)) + "<=" + getDate(dates5.at(2)) + "Test #47");
        JUnit::Assert((dates5.at(0) > dates5.at(3)), getDate(dates5.at(0)) + ">" + getDate(dates5.at(3)) + "Test #48");
        JUnit::Assert((dates5.at(0) >= dates5.at(1)), getDate(dates5.at(0)) + ">=" + getDate(dates5.at(1)) + "Test #49");
        JUnit::Assert((dates5.at(0) >= dates5.at(3)), getDate(dates5.at(0)) + ">=" + getDate(dates5.at(3)) + "Test #50");
    }


};

