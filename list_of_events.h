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
    listOfEvents() = default;

    explicit listOfEvents(const std::string &event);

    void addEvent(const std::string &event); // добовляет новое событие если его нет в списке

    void delEvent(std::vector<std::string>::iterator &it); // удаляет событие из контейнеров

    std::string getLastEvent(); // получить последнее событие из списка

    bool isEmpty(); // проверяет пусты ли контейнеры

    bool findSetEvent(const std::string &event); // возвращаем итератор на найденное событие в set

    std::set<std::string> orderedEvents;
    std::vector<std::string> sequentialEvents;

};

void TestAddEvent();

void TestDelEvent();

void TestGetLastEvent();


