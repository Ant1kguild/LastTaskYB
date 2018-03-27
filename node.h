//
// Created by ant1k on 17.3.18.
//

#pragma once

#include <utility>
#include <memory>

#include "comparison.h"
#include "logical_operation.h"
#include "date.h"

enum class Condition {
    Any,
    None,
    This
};

enum class LogicOpPr {
    NoneNone,
    NoneAny,
    NoneThis,
    AnyAny,
    AnyNone,
    AnyThis,
    ThisThis,
    ThisNone,
    ThisAny
};



struct PredicateIt {
    PredicateIt(Condition _date, Condition _event) : date(_date), event(_event) {}

    Condition date;
    Condition event;

    static PredicateIt createDate(bool result) {
        return PredicateIt(result ? Condition::This : Condition::None, Condition::Any);
    }

    static PredicateIt createEvent(bool result) {
        return PredicateIt(Condition::Any, result ? Condition::This : Condition::None);
    }

    static LogicOpPr makeLogicOpPr(Condition lhs, Condition rhs) {
        if (lhs == Condition::None && rhs == Condition::None) return LogicOpPr::NoneNone;
        if (lhs == Condition::None && rhs == Condition::Any) return LogicOpPr::NoneAny;
        if (lhs == Condition::None && rhs == Condition::This) return LogicOpPr::NoneThis;
        if (lhs == Condition::Any && rhs == Condition::Any) return LogicOpPr::AnyAny;
        if (lhs == Condition::Any && rhs == Condition::None) return LogicOpPr::AnyNone;
        if (lhs == Condition::Any && rhs == Condition::This) return LogicOpPr::AnyThis;
        if (lhs == Condition::This && rhs == Condition::This) return LogicOpPr::ThisThis;
        if (lhs == Condition::This && rhs == Condition::None) return LogicOpPr::ThisNone;
        if (lhs == Condition::This && rhs == Condition::Any) return LogicOpPr::ThisAny;


    }

    static void changeConditionAnd(LogicOpPr lop, Condition &val) {
        switch (lop) {
            case LogicOpPr::NoneNone:
                val = Condition::None;
                break;
            case LogicOpPr::NoneAny:
                val = Condition::None;
                break;
            case LogicOpPr::NoneThis:
                val = Condition::None;
                break;
            case LogicOpPr::AnyAny:
                val = Condition::Any;
                break;
            case LogicOpPr::AnyNone:
                val = Condition::None;
                break;
            case LogicOpPr::AnyThis:
                val = Condition::This;
                break;
            case LogicOpPr::ThisThis:
                val = Condition::This;
                break;
            case LogicOpPr::ThisNone:
                val = Condition::None;
                break;
            case LogicOpPr::ThisAny:
                val = Condition::This;
                break;
        }
    }

    static void changeConditionOr(LogicOpPr lop, Condition &val) {
        switch (lop) {
            case LogicOpPr::NoneNone:
                val = Condition::None;
                break;
            case LogicOpPr::NoneAny:
                val = Condition::Any;
                break;
            case LogicOpPr::NoneThis:
                val = Condition::This;
                break;
            case LogicOpPr::AnyAny:
                val = Condition::Any;
                break;
            case LogicOpPr::AnyNone:
                val = Condition::Any;
                break;
            case LogicOpPr::AnyThis:
                val = Condition::Any;
                break;
            case LogicOpPr::ThisThis:
                val = Condition::This;
                break;
            case LogicOpPr::ThisNone:
                val = Condition::This;
                break;
            case LogicOpPr::ThisAny:
                val = Condition::Any;
                break;
        }
    }

    static PredicateIt createLogicalOP_and(PredicateIt it1, PredicateIt it2) {
        Condition date, event;
        auto forDate = makeLogicOpPr(it1.date, it2.date);
        auto forEvent = makeLogicOpPr(it1.event, it2.event);
        changeConditionAnd(forDate, date);
        changeConditionAnd(forEvent, event);
        return {date, event};
    }

    static PredicateIt createLogicalOP_or(PredicateIt it1, PredicateIt it2) {
        Condition date, event;
        auto forDate = makeLogicOpPr(it1.date, it2.date);
        auto forEvent = makeLogicOpPr(it1.event, it2.event);
        changeConditionOr(forDate, date);
        changeConditionOr(forEvent, event);
        return {date, event};
    }

};


class Node {
public:
    Node() = default;

    virtual PredicateIt Evaluate(Date date, const std::string &event) = 0;
};

class EmptyNode : public Node {
public:
    EmptyNode() = default;

    PredicateIt Evaluate(Date date, const std::string &event) override {
        return PredicateIt(Condition::Any, Condition::Any);
    }


};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(Comparison cmp, Date date);

    PredicateIt Evaluate(Date date, const std::string &event) override;

private:
    Comparison _cmp;
    Date _date;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(Comparison cmp, std::string value);

    PredicateIt Evaluate(Date date, const std::string &event) override;

private:
    Comparison _cmp;
    std::string _value;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(const LogicalOperation &logical_operation,
                         std::shared_ptr<Node> left,
                         std::shared_ptr<Node> right);

    PredicateIt Evaluate(Date date, const std::string &event) override;

private:
    LogicalOperation _logical_operation;
    std::shared_ptr<Node> _left;
    std::shared_ptr<Node> _right;
};


