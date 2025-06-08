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

    Car* start = first;
    bool originalLight = start->light;
    start->light = false;
    ++countOp;

    Car* currentt = start->next;
    int stepss = 1;
    ++countOp;

    // Идем вперед, пока не встретим выключенную лампу
    while (currentt != start && currentt->light) {
        ++stepss;
        currentt = currentt->next;
        ++countOp;
    }

    // Вернуться назад на steps шагов
    Car* back = currentt;
    for (int i = 0; i < stepss; ++i) {
        back = back->prev;
        ++countOp;
    }

    // Вернём лампочку в исходное состояние
    start->light = originalLight;

    if (back == start)
        return stepss;
    
    // fallback — медленный способ (по кольцу, если что-то пошло не так)
    int fallbackk = 1;
    Car* tempp = start->next;
    ++countOp;
    while (tempp != start) {
        ++fallbackk;
        tempp = tempp->next;
        ++countOp;
    }

    return fallbackk;
}

int Train::getOpCount() {
    return countOp;
}
