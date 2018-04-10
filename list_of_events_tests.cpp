//
// Created by ant1k on 29.3.18.
//

#include "list_of_events.h"
#include "test_runner.h"


std::ostream &operator<<(std::ostream &stream, const std::vector<std::string> &vecStr) {
    stream << "{";
    for (const auto &i : vecStr) {
        stream << "[" << i << "]";
    }
    stream << "}" << endl;
    return stream;
}


std::ostream &operator<<(std::ostream &stream, const std::set<std::string> &setSrt) {
    stream << "{";
    for (const auto &i :setSrt) {
        stream << "[" << i << "]";
    }
    stream << "}" << endl;
    return stream;
}

void TestAddEvent() {
    listOfEvents testDB;
    std::set<std::string> testSet;
    std::vector<std::string> testVec;
    {
        {
            testSet.insert("test event #1.cpp");
            testVec.emplace_back("test event #1.cpp");
            testDB.addEvent("test event #1.cpp");
            JUnit::AssertEqual(testDB.orderedEvents, testSet, "Test #1.cpp.1.cpp");
            JUnit::AssertEqual(testDB.sequentialEvents, testVec, "Test #1.cpp.2");
            JUnit::AssertEqual(testDB.sequentialEvents.size(), testDB.orderedEvents.size(), "Test# 1.cpp.3");
        }

        {
            testDB.addEvent("test event #1.cpp");
            JUnit::AssertEqual(testDB.orderedEvents, testSet, "Test #2.1.cpp");
            JUnit::AssertEqual(testDB.sequentialEvents, testVec, "Test #2.2");
            JUnit::AssertEqual(testDB.sequentialEvents.size(), testDB.orderedEvents.size(), "Test# 2.3");
        }

        {
            testSet.insert("test event #2");
            testVec.emplace_back("test event #2");
            testDB.addEvent("test event #2");
            JUnit::AssertEqual(testDB.orderedEvents, testSet, "Test #3.1.cpp");
            JUnit::AssertEqual(testDB.sequentialEvents, testVec, "Test #3.2");
            JUnit::AssertEqual(testDB.sequentialEvents.size(), testDB.orderedEvents.size(), "Test# 3.3");
        }

        {
            testDB.addEvent("test event #1.cpp");
            testDB.addEvent("test event #2");
            JUnit::AssertEqual(testDB.orderedEvents, testSet, "Test #4.1.cpp");
            JUnit::AssertEqual(testDB.sequentialEvents, testVec, "Test #4.2");
            JUnit::AssertEqual(testDB.sequentialEvents.size(), testDB.orderedEvents.size(), "Test# 4.3");
        }

        {
            testDB.addEvent("test event #3");
            JUnit::Assert((testDB.orderedEvents.size() == 3), "Test# 5.1.cpp");
            JUnit::Assert((testDB.sequentialEvents.size() == 3), "Test# 5.2");
            testDB.addEvent("test event #1.cpp");
            testDB.addEvent("test event #2");
            JUnit::Assert((testDB.orderedEvents.size() == 3), "Test# 5.3");
            JUnit::Assert((testDB.sequentialEvents.size() == 3), "Test# 5.4");
            testSet.insert("test event #3");
            testVec.emplace_back("test event #3");
            JUnit::AssertEqual(testDB.orderedEvents, testSet, "Test #5.5");
            JUnit::AssertEqual(testDB.sequentialEvents, testVec, "Test #5.6");
            JUnit::AssertEqual(testDB.sequentialEvents.size(), testDB.orderedEvents.size(), "Test# 5.7");
        }
        {
            testDB.addEvent("test event #1.cpp");
            testDB.addEvent("test event #2");
            testDB.addEvent("test event #3");
            JUnit::Assert((testDB.orderedEvents.size() == 3), "Test# 6.1.cpp");
            JUnit::Assert((testDB.sequentialEvents.size() == 3), "Test# 6.2");
            JUnit::Assert(!(testDB.orderedEvents.empty()), "Test# 6.3");
            JUnit::Assert(!(testDB.sequentialEvents.empty()), "Test# 6.4");
            JUnit::AssertEqual(testDB.orderedEvents, testSet, "Test #6.5");
            JUnit::AssertEqual(testDB.sequentialEvents, testVec, "Test #6.6");
            JUnit::AssertEqual(testDB.sequentialEvents.size(), testDB.orderedEvents.size(), "Test# 6.7");
            testDB.addEvent("test event #4");
            testSet.insert("test event #4");
            testVec.emplace_back("test event #4");
            JUnit::AssertEqual(testDB.orderedEvents, testSet, "Test #7.7");
            JUnit::AssertEqual(testDB.sequentialEvents, testVec, "Test #7.8");
            JUnit::AssertEqual(testDB.sequentialEvents.size(), testDB.orderedEvents.size(), "Test# 7.9");
        }
    }
}

void TestDelEvent() {
    listOfEvents testDB;
    { // последовательное удаление от последнего -> первому
        std::set<std::string> testSet = {"test event #1.cpp", "test event #2", "test event #3", "test event #4"};
        std::vector<std::string> testVec = {"test event #1.cpp", "test event #2", "test event #3", "test event #4"};
        testDB.addEvent("test event #1.cpp");
        testDB.addEvent("test event #2");
        testDB.addEvent("test event #3");
        testDB.addEvent("test event #4");
        JUnit::AssertEqual(testDB.orderedEvents.size(), testDB.sequentialEvents.size(), "Test #1.cpp.1.cpp");
        JUnit::AssertEqual(testDB.orderedEvents.size(), 4, "Test #1.cpp.2");
        JUnit::AssertEqual(testDB.sequentialEvents.size(), 4, "Test #1.cpp.3");
        auto it4 = find(testVec.begin(), testVec.end(), "test event #4");
        testDB.delEvent(it4);
        testSet.erase(*it4);
        testVec.erase(it4);
        JUnit::AssertEqual(testDB.orderedEvents.size(), testDB.sequentialEvents.size(), "Test #1.cpp.4");
        JUnit::AssertEqual(testDB.orderedEvents.size(), 3, "Test #1.cpp.5");
        JUnit::AssertEqual(testDB.sequentialEvents.size(), 3, "Test #1.cpp.6");
        JUnit::AssertEqual(testDB.orderedEvents, testSet, "Test #1.cpp.7");
        JUnit::AssertEqual(testDB.sequentialEvents, testVec, "Test #1.cpp.8");
        auto it3 = find(testVec.begin(), testVec.end(), "test event #3");
        testDB.delEvent(it3);
        testSet.erase(*it3);
        testVec.erase(it3);
        JUnit::AssertEqual(testDB.orderedEvents.size(), testDB.sequentialEvents.size(), "Test #1.cpp.9");
        JUnit::AssertEqual(testDB.orderedEvents.size(), 2, "Test #1.cpp.10");
        JUnit::AssertEqual(testDB.sequentialEvents.size(), 2, "Test #1.cpp.11");
        JUnit::AssertEqual(testDB.orderedEvents, testSet, "Test #1.cpp.12");
        JUnit::AssertEqual(testDB.sequentialEvents, testVec, "Test #1.cpp.13");
        auto it2 = find(testVec.begin(), testVec.end(), "test event #2");
        testDB.delEvent(it2);
        testSet.erase(*it2);
        testVec.erase(it2);
        JUnit::AssertEqual(testDB.orderedEvents.size(), testDB.sequentialEvents.size(), "Test #1.cpp.14");
        JUnit::AssertEqual(testDB.orderedEvents.size(), 1, "Test #1.cpp.15");
        JUnit::AssertEqual(testDB.sequentialEvents.size(), 1, "Test #1.cpp.16");
        JUnit::AssertEqual(testDB.orderedEvents, testSet, "Test #1.cpp.17");
        JUnit::AssertEqual(testDB.sequentialEvents, testVec, "Test #1.cpp.18");
        auto it1 = find(testVec.begin(), testVec.end(), "test event #1.cpp");
        testDB.delEvent(it1);
        testSet.erase(*it1);
        testVec.erase(it1);
        JUnit::AssertEqual(testDB.orderedEvents.size(), testDB.sequentialEvents.size(), "Test #1.cpp.19");
        JUnit::AssertEqual(testDB.orderedEvents.size(), 0, "Test #1.cpp.20");
        JUnit::AssertEqual(testDB.sequentialEvents.size(), 0, "Test #1.cpp.21");
        JUnit::AssertEqual(testDB.orderedEvents, testSet, "Test #1.cpp.22");
        JUnit::AssertEqual(testDB.sequentialEvents, testVec, "Test #1.cpp.23");
        JUnit::Assert(testDB.isEmpty(), "Test #1.cpp.24");
    }
    { // произвольное удаление
        std::set<std::string> testSet = {"test event #1.cpp", "test event #2", "test event #3", "test event #4"};
        std::vector<std::string> testVec = {"test event #1.cpp", "test event #2", "test event #3", "test event #4"};
        testDB.addEvent("test event #1.cpp");
        testDB.addEvent("test event #2");
        testDB.addEvent("test event #3");
        testDB.addEvent("test event #4");
        JUnit::AssertEqual(testDB.orderedEvents.size(), testDB.sequentialEvents.size(), "Test #2.1.cpp");
        JUnit::AssertEqual(testDB.orderedEvents.size(), 4, "Test #2.2");
        JUnit::AssertEqual(testDB.sequentialEvents.size(), 4, "Test #2.3");
        auto it = find(testVec.begin(), testVec.end(), "test event #2");
        testDB.delEvent(it);
        testSet.erase(*it);
        testVec.erase(it);
        JUnit::AssertEqual(testDB.orderedEvents.size(), testDB.sequentialEvents.size(), "Test #2.4");
        JUnit::AssertEqual(testDB.orderedEvents.size(), 3, "Test #2.5");
        JUnit::AssertEqual(testDB.sequentialEvents.size(), 3, "Test #2.6");
        JUnit::AssertEqual(testDB.orderedEvents, testSet, "Test #2.7");
        JUnit::AssertEqual(testDB.sequentialEvents, testVec, "Test #2.8");
    }
}

void TestGetLastEvent() {
    {
        listOfEvents testDB;
        std::set<std::string> testSet = {"test event #1.cpp", "test event #2", "test event #3", "test event #4"};
        std::vector<std::string> testVec = {"test event #1.cpp", "test event #2", "test event #3", "test event #4"};
        testDB.addEvent("test event #1.cpp");
        testDB.addEvent("test event #2");
        testDB.addEvent("test event #3");
        testDB.addEvent("test event #4");
        JUnit::AssertEqual(testDB.getLastEvent(), testVec[3], "Test #1.cpp");
    }
    {
        listOfEvents testDB;
        std::set<std::string> testSet = {"test event #1.cpp", "test event #2", "test event #3", "test event #4"};
        std::vector<std::string> testVec = {"test event #1.cpp", "test event #2", "test event #3", "test event #1.cpp"};
        testDB.addEvent("test event #3");
        testDB.addEvent("test event #2");
        testDB.addEvent("test event #4");
        testDB.addEvent("test event #1.cpp");
        JUnit::AssertEqual(testDB.getLastEvent(), testVec[3], "Test #2");
    }
}


