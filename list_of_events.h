//
// Created by ant1k on 29.3.18.
//

#pragma once;

#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>


struct listOfEvents {
public:
    void addEvent(const std::string &event); // добовляет новое событие если его нет в списке

    void delEvent(const std::string &event); // удаляет событие из контейнеров

    std::string getLastEvent(); // получить последнее событие из списка

    bool isEmpty(); // проверяет пусты ли контейнеры

    std::set<std::string, std::less<>>::iterator
    findSetEvent(const std::string &event); // возвращаем итератор на найденное событие в set

    std::vector<std::string>::iterator
    findVecEvent(const std::string &event); // возвращает итератор на найденное событие в vector


    std::set<std::string> orderedEvents;
    std::vector<std::string> sequentialEvents;

};

void TestAddEvent();

void TestDelEvent();

void TestGetLastEvent();


