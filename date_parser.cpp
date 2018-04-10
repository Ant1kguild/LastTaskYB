//
// Created by ant1k on 16.3.18.
//

#include "date.h"


Date ParseDate(std::istream &is) {
    const auto noDate = is.eof();
    if (noDate) {
        throw invalid_argument("");
    }
    int Year, Month, Day;
    is >> Year;
    is.ignore(1);
    is >> Month;
    is.ignore(1);
    is >> Day;
    return {Year, Month, Day};

//    is >> parseDate;
//    if (parseDate.empty()) {
//        throw invalid_argument(parseDate);
//    }
//    DateConversion date(parseDate);
//    if (date.checkException()) {
//        return {date.getYear(), date.getMonth(), date.getDay()};
//    } else {
//        date.myException();
//    }

}
