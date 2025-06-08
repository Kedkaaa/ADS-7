// Copyright 2021 NNTU-CS
#include "train.h"
#include <iostream>
Train::Train() : countOp(0), first(nullptr) {}

void Train::addCar(bool light) {
    Car* carr = new Car{ light, nullptr, nullptr };
    if (!first) {
        carr->next = carr;
        carr->prev = carr;
        first = carr;
    } else {
        Car* last = first->prev;
        carr->next = first;
        carr->prev = last;
        last->next = carr;
        first->prev = carr;
    }
}

int Train::getLength() {
    if (!first) return 0;
    countOp = 0;
    Car* currentt = first;

    // Включаем лампу в начальном вагоне
    currentt->light = true;
    ++countOp;

    int maxSteps = 1000000; // защита от бесконечного цикла

    while (maxSteps-- > 0) {
        int stepss = 1;
        const Car* walkerr = currentt->next;
        ++countOp;

        // Идём вперёд до включённой лампочки
        while (!walkerr->light) {
            ++stepss;
            walkerr = walkerr->next;
            ++countOp;
        }
        Car* checkerr = walkerr;
        // Вернуться назад на steps шагов
        for (int i = 0; i < stepss; ++i) {
            checkerr = checkerr->prev;
            ++countOp;
        }

        if (checkerr == currentt && checkerr->light)
            return stepss;

        // иначе — продолжаем с нового вагона, выключив свет здесь
        currentt->light = false;
        currentt = currentt->next;
        ++countOp;
    }
    std::cerr << "Ошибка: превышен лимит шагов. Возможен бесконечный цикл.\n";
    return -1; // ошибка
}
int Train::getOpCount() {
    return countOp;
}
