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
    currentt->light = false;
    ++countOp;

    int stepss = 0;
    Car* walkerr = currentt->next;

    // Идем вперед, пока не встретим выключенную лампу
    while (walkerr->light) {
        ++stepss;
        walkerr = walkerr->next;
        ++countOp;
    }

    // вернулись назад на steps шагов
    const Car* checkerr = walkerr;
    for (int i = 0; i < stepss; ++i) {
        checkerr = checkerr->prev;
        ++countOp;
    }

    if (!checkerr->light)
        return stepss + 1;

    // запасной вариант
    int fallbackk = 1;
    const Car* tmpp = currentt->next;
    ++countOp;

    while (tmpp != current) {
        ++fallback;
        tmpp = tmpp->next;
        ++countOp;
    }

    return fallbackk;
}

int Train::getOpCount() {
    return countOp;
}
