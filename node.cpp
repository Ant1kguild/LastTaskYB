//
// Created by ant1k on 17.3.18.
//

#include "node.h"


DateComparisonNode::DateComparisonNode(Comparison cmp, Date date)
        : _cmp(cmp), _date(date) {}

bool DateComparisonNode::Evaluate(Date date, const std::string &event) {
    Date emptyDate{};
    if (emptyDate == date) {
        return false;
    } else {
        switch (_cmp) {
            case Comparison::Less:
                return (date < _date);
            case Comparison::LessOrEqual:
                return (date <= _date);
            case Comparison::Greater:
                return (date > _date);
            case Comparison::GreaterOrEqual:
                return (date >= _date);
            case Comparison::Equal:
                return (date == _date);
            case Comparison::NotEqual:
                return (date != _date);
        }
    }
}


EventComparisonNode::EventComparisonNode(Comparison cmp, std::string value)
        : _cmp(cmp), _value(std::move(value)) {}

bool EventComparisonNode::Evaluate(Date date, const std::string &event) {
    switch (_cmp) {
        case Comparison::Equal:
            return (event == _value);
        case Comparison::NotEqual:
            return (event != _value);
        case Comparison::Less:
            return (false);
        case Comparison::LessOrEqual:
            return (false);
        case Comparison::Greater:
            return (false);
        case Comparison::GreaterOrEqual:
            return (false);
    }
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation &logical_operation,
                                           std::shared_ptr<Node> left,
                                           std::shared_ptr<Node> right)
        : _logical_operation(logical_operation),
          _left(std::move(left)),
          _right(std::move(right)) {}

bool LogicalOperationNode::Evaluate(Date date, const std::string &event) {
    auto lhs = _left.get()->Evaluate(date, event);
    auto rhs = _right.get()->Evaluate(date, event);
    switch (_logical_operation) {
        case LogicalOperation::And:
            return (lhs && rhs);
        case LogicalOperation::Or:
            return (lhs || rhs);
    }
}
