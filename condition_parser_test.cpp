#include "condition_parser.h"
#include "test_runner.h"

#include <sstream>
using namespace std;

void TestParseCondition() {
//    {
//        istringstream is("date != 2017-11-18");
//        shared_ptr<Node> root = ParseCondition(is);
//        JUnit::Assert(root->Evaluate({2017, 1, 1}, ""), "Parse condition 1");
//        JUnit::Assert(!root->Evaluate({2017, 11, 18}, ""), "Parse condition 2");
//    }
//    {
//        istringstream is(R"(event == "sport event")");
//        shared_ptr<Node> root = ParseCondition(is);
//        JUnit::Assert(root->Evaluate({2017, 1, 1}, "sport event"), "Parse condition 3");
//        JUnit::Assert(!root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 4");
//    }
//    {
//        istringstream is("date >= 2017-01-01 AND date < 2017-07-01");
//        shared_ptr<Node> root = ParseCondition(is);
//        JUnit::Assert(root->Evaluate({2017, 1, 1}, ""), "Parse condition 5");
//        JUnit::Assert(root->Evaluate({2017, 3, 1}, ""), "Parse condition 6");
//        JUnit::Assert(root->Evaluate({2017, 6, 30}, ""), "Parse condition 7");
//        JUnit::Assert(!root->Evaluate({2017, 7, 1}, ""), "Parse condition 8");
//        JUnit::Assert(!root->Evaluate({2016, 12, 31}, ""), "Parse condition 9");
//    }
//    {
//        istringstream is(R"(event != "sport event" AND event != "Wednesday")");
//        shared_ptr<Node> root = ParseCondition(is);
//        JUnit::Assert(root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 10");
//        JUnit::Assert(!root->Evaluate({2017, 1, 1}, "sport event"), "Parse condition 11");
//        JUnit::Assert(!root->Evaluate({2017, 1, 1}, "Wednesday"), "Parse condition 12");
//    }
//    {
//        istringstream is(R"(event == "holiday AND date == 2017-11-18")");
//        shared_ptr<Node> root = ParseCondition(is);
//        JUnit::Assert(!root->Evaluate({2017, 11, 18}, "holiday"), "Parse condition 13");
//        JUnit::Assert(!root->Evaluate({2017, 11, 18}, "work day"), "Parse condition 14");
//        JUnit::Assert(root->Evaluate({1, 1, 1}, "holiday AND date == 2017-11-18"), "Parse condition 15");
//    }
//    {
//        istringstream is(R"(((event == "holiday" AND date == 2017-01-01)))");
//        shared_ptr<Node> root = ParseCondition(is);
//        JUnit::Assert(root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 16");
//        JUnit::Assert(!root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 17");
//    }
//    {
//        istringstream is(R"(date > 2017-01-01 AND (event == "holiday" OR date < 2017-07-01))");
//        shared_ptr<Node> root = ParseCondition(is);
//        JUnit::Assert(!root->Evaluate({2016, 1, 1}, "holiday"), "Parse condition 18");
//        JUnit::Assert(root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 19");
//        JUnit::Assert(root->Evaluate({2017, 1, 2}, "workday"), "Parse condition 20");
//        JUnit::Assert(!root->Evaluate({2018, 1, 2}, "workday"), "Parse condition 21");
//    }
//    {
//        istringstream is(R"(date > 2017-01-01 AND event == "holiday" OR date < 2017-07-01)");
//        shared_ptr<Node> root = ParseCondition(is);
//        JUnit::Assert(root->Evaluate({2016, 1, 1}, "event"), "Parse condition 22");
//        JUnit::Assert(root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 23");
//        JUnit::Assert(root->Evaluate({2017, 1, 2}, "workday"), "Parse condition 24");
//        JUnit::Assert(!root->Evaluate({2018, 1, 2}, "workday"), "Parse condition 25");
//    }
//    {
//        istringstream is(R"(((date == 2017-01-01 AND event == "holiday")))");
//        shared_ptr<Node> root = ParseCondition(is);
//        JUnit::Assert(root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 26");
//        JUnit::Assert(!root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 27");
//    }
//    {
//        istringstream is(R"(((event == "2017-01-01" OR date > 2016-01-01)))");
//        shared_ptr<Node> root = ParseCondition(is);
//        JUnit::Assert(root->Evaluate({1, 1, 1}, "2017-01-01"), "Parse condition 28");
//        JUnit::Assert(!root->Evaluate({2016, 1, 1}, "event"), "Parse condition 29");
//        JUnit::Assert(root->Evaluate({2016, 1, 2}, "event"), "Parse condition 30");
//    }
}
