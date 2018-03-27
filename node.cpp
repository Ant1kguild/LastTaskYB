//
// Created by ant1k on 17.3.18.
//

#include "node.h"


DateComparisonNode::DateComparisonNode(Comparison cmp, Date date)
        : _cmp(cmp), _date(date) {}

PredicateIt DateComparisonNode::Evaluate(Date date, const std::string &event) {
    switch (_cmp) {
        case Comparison::Less:
            return PredicateIt::createDate(date < _date);
        case Comparison::LessOrEqual:
            return PredicateIt::createDate(date <= _date);
        case Comparison::Greater:
            return PredicateIt::createDate(date > _date);
        case Comparison::GreaterOrEqual:
            return PredicateIt::createDate(date >= _date);
        case Comparison::Equal:
            return PredicateIt::createDate(date == _date);
        case Comparison::NotEqual:
            return PredicateIt::createDate(date != _date);
    }
}


EventComparisonNode::EventComparisonNode(Comparison cmp, std::string value)
        : _cmp(cmp), _value(std::move(value)) {}

PredicateIt EventComparisonNode::Evaluate(Date date, const std::string &event) {
    switch (_cmp) {
        case Comparison::Equal:
            return PredicateIt::createEvent(event == _value);
        case Comparison::NotEqual:
            return PredicateIt::createEvent(event != _value);
        case Comparison::Less:
            return PredicateIt::createEvent(false);
        case Comparison::LessOrEqual:
            return PredicateIt::createEvent(false);
        case Comparison::Greater:
            return PredicateIt::createEvent(false);
        case Comparison::GreaterOrEqual:
            return PredicateIt::createEvent(false);
    }
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation &logical_operation,
                                           std::shared_ptr<Node> left,
                                           std::shared_ptr<Node> right)
        : _logical_operation(logical_operation),
          _left(std::move(left)),
          _right(std::move(right)) {}

PredicateIt LogicalOperationNode::Evaluate(Date date, const std::string &event) {
    auto lhs = _left.get()->Evaluate(date, event);
    auto rhs = _right.get()->Evaluate(date, event);
    switch (_logical_operation) {
        case LogicalOperation::And:
            return PredicateIt::createLogicalOP_and(lhs, rhs);
        case LogicalOperation::Or:
            return PredicateIt::createLogicalOP_or(lhs, rhs);
    }
}
