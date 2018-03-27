//
// Created by ant1k on 16.3.18.
//

#pragma once

#include <sstream>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<class V>
std::ostream &operator<<(std::ostream &stream, const std::vector<V> &vector1) {
    for (const auto &i : vector1) {
        stream << i << " ";
    }
    stream << endl;
    return stream;
}



class JUnit {

public:
    template<class T, class U>
    static void AssertEqual(const T &t, const U &u, const string &hint) {
        if (t != u) {
            ostringstream os;
            os << "Assertion failed: " << t << " != " << u
               << " hint: " << hint;
            throw runtime_error(os.str());
        }
    }

    static void Assert(bool b, const string &hint) {
        if (!b) {
            ostringstream os;
            os << "Assertion failed: " << b << " != " << true
               << " hint: " << hint;
            throw runtime_error(os.str());
        }
    }
};




class TestRunner {
public:
    template<class TestFunc>
    void RunTest(TestFunc func, const string &test_name)  {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (runtime_error& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        }
    }

    ~TestRunner();
private:
    int fail_count = 0;
};


