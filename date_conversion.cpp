//
// Created by ant1k on 16.3.18.
//

#include <utility>
#include "date.h"


DateConversion::DateConversion(std::string encryptedDate) : date(std::move(encryptedDate)) {
    std::stringstream ss(date);
    theFirstCharacter(ss);
    ensureNextSymbolAndSkip(ss);
    checkMonth(ss);
    ensureNextSymbolAndSkip(ss);
    checkDay(ss);
    theLastCharacter(ss);

}

void DateConversion::theFirstCharacter(std::stringstream &ss) {
    int _year = ss.peek();
    if (std::isdigit(ss.peek()) == 0 || ss.eof() || _year < 0) {
        errors.emplace_back(errorNumber::dateError, 0);
    }
    int year;
    ss >> year;
    changeYear(year);

}

void DateConversion::ensureNextSymbolAndSkip(std::stringstream &ss) {
    auto symbol = static_cast<char>(ss.peek());
    bool trueSymbol = (symbol != '-');
    if (trueSymbol) {
        errors.emplace_back(errorNumber::dateError, 0);
    }
    ss.ignore(1);
}

void DateConversion::checkMonth(std::stringstream &ss) {
    int month;
    ss >> month;
    if (month < 1 || month > 12) {
        errors.emplace_back(errorNumber::monthError, month);
    } else {
        changeMonth(month);
    }
}

void DateConversion::checkDay(std::stringstream &ss) {
    int day;
    ss >> day;
    if (day < 1 || day > 31) {
        errors.emplace_back(errorNumber::dayError, day);
    } else {
        changeDay(day);
    }
}

void DateConversion::theLastCharacter(std::stringstream &ss) {
    bool f2 = !ss.eof();
    if (f2) {
        errors.emplace_back(errorNumber::dateError, 0);
    }
}

DateConversion::~DateConversion() = default;

bool DateConversion::checkException() {
    return errors.empty();
}

void DateConversion::myException() {
        std::ostringstream error;
    auto it = errors.begin();
        switch (it->first) {
            case (errorNumber::dateError):
                error << "Wrong date format: " + date;
                throw std::runtime_error(error.str());
            case (errorNumber::monthError):
                error << "Month value is invalid: " + std::to_string(it->second);
                throw std::runtime_error(error.str());
            case (errorNumber::dayError):
                error << "Day value is invalid: " + std::to_string(it->second);
                throw std::runtime_error(error.str());
        }

}
