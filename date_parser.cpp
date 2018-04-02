//
// Created by ant1k on 16.3.18.
//

#include "date.h"



Date ParseDate(std::istream &is) {
    std::string parseDate;
    is >> parseDate;
    if (parseDate.empty()) {
        throw invalid_argument(parseDate);
    }
    DateConversion date(parseDate);
    if (date.checkException()) {
        return {date.getYear(), date.getMonth(), date.getDay()};
    } else {
        date.myException();
    }
}
