//
// Created by ant1k on 16.3.18.
//


#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <exception>
#include <tuple>
#include <set>
#include <vector>

#include "test_runner.h"

class Date {
public:
    Date();

    Date(int _Year, int _Month, int _Day); // Конструктор Год(_Year), Месяц(_Month), День(_Day)

    int getYear() const; // Возвращает параметр года

    int getMonth() const;// Возвращает параметр месяца

    int getDay() const; // Возвращает параметр дня

    void changeYear(const int &cYear);

    void changeMonth(const int &cMonth);

    void changeDay(const int &cDay);

    /* Сравнение даты на неравенство */
    friend bool operator!=(const Date &lhs, const Date &rhs);

    /* Сравнение даты на равенство */
    friend bool operator==(const Date &lhs, const Date &rhs);

    /* оператор меньше */
    friend bool operator<(const Date &lhs, const Date &rhs);

    /* оператор меньше либо равно*/
    friend bool operator<=(const Date &lhs, const Date &rhs);

    /* оператор больше */
    friend bool operator>(const Date &lhs, const Date &rhs);

    /* оператор больше либо равно*/
    friend bool operator>=(const Date &lhs, const Date &rhs);


private:
    int Year;
    int Month;
    int Day;


};

/* Набор тестов для парсинга даты*/
void TestDateParser();

/* Преобразовывает строку к дате формата ГГ-ММ-ДД */
Date ParseDate(std::istringstream &is);

/* Вывод даты в поток в формате ГГГГ-ММ-ДД */
std::ostream &operator<<(std::ostream &stream, const Date &data);

std::string &operator<<(std::string str, const Date &data);

void TestComparingDates();


/* Нумератор ошибок в дате
 * dateError - неверный формат даты,
 * monthError - значение месяца недействительно,
 * dayError -  значение дня недействительно */
enum class errorNumber : uint {
    dateError = 1,
    monthError,
    dayError
};


class DateConversion : public Date {
public:
    explicit DateConversion(std::string encryptedDate);

    bool checkException();

    ~DateConversion();

    void myException();

private:

    std::string date; /* Хранит дату в первоначально введенном формате */

    std::vector<pair<errorNumber, int>> errors; /* Хранилище для ошибок */

    /* Проверка первого символа:
     * - является ли он числом,
     * - является ли число положительным,
     * - не пуста ли дата.
     * при некорректном вводе, передает errorNumber в хранилище ошибок (std::vector errors)*/
    void theFirstCharacter(std::stringstream &ss);

    /* Проверка разделителя:
     * - между ГГ и ММ
     * - между ММ и ДД
     * при некорректном вводе, передает errorNumber в хранилище ошибок (std::vector errors) */
    void ensureNextSymbolAndSkip(std::stringstream &ss);

    /* Проверяет значение месяца.
     * при некорректном вводе, передает errorNumber в хранилище ошибок (std::vector errors)*/
    void checkMonth(std::stringstream &ss);

    /* Проверяет значение дня.
     * при некорректном вводе, передает errorNumber в хранилище ошибок (std::vector errors)*/
    void checkDay(std::stringstream &ss);

    /* Проверка последнего символа:
     * - нет ли мусора после даты,
     * - закончен ли ввода даты.
     * при некорректном вводе, передает errorNumber в хранилище ошибок (std::vector errors)*/
    void theLastCharacter(std::stringstream &ss);


};