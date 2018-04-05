//
// Created by ant1k on 17.3.18.
//

#pragma once

#include <utility>
#include <memory>

#include "comparison.h"
#include "logical_operation.h"
#include "date.h"



class Node {
public:
    Node() = default;

    virtual bool Evaluate(Date date, const std::string &event) = 0;
};

class EmptyNode : public Node {
public:
    EmptyNode() = default;

    bool Evaluate(Date date, const std::string &event) override {
        return true;
    }


};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(Comparison cmp, Date date);

    bool Evaluate(Date date, const std::string &event) override;

private:
    Comparison _cmp;
    Date _date;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(Comparison cmp, std::string value);

    bool Evaluate(Date date, const std::string &event) override;

private:
    Comparison _cmp;
    std::string _value;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(const LogicalOperation &logical_operation,
                         std::shared_ptr<Node> left,
                         std::shared_ptr<Node> right);

    bool Evaluate(Date date, const std::string &event) override;

private:
    LogicalOperation _logical_operation;
    std::shared_ptr<Node> _left;
    std::shared_ptr<Node> _right;
};


