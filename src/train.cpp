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
    const Car* currentt = first;

    // Защита от бесконечного цикла
    const int maxIterations = 1'000'000;

    for (int iter = 0; iter < maxIterations; ++iter) {
        // 1. Выключаем лампу в текущем вагоне
        currentt->light = false;

        // 2. Идём вперёд, пока не встретим выключенную лампу
        const Car* walkerr = currentt->next;
        int stepss = 1; // начинаем с 1, потому что уже сдвинулись от текущего
        countOp++;

        while (walkerr->light) {
            walkerr = walkerr->next;
            stepss++;
            countOp++;
        }

        // 3. Возвращаемся назад на steps шагов
        Car* checkerr = walkerr;
        for (int i = 0; i < stepss; ++i) {
            checkerr = checkerr->prev;
            countOp++;
        }

        // 4. Проверяем, погашена ли лампа на исходном вагоне
        if (!checkerr->light) {
            return stepss + 1;
        }

        // Иначе — включаем обратно и идём на следующий вагон
        currentt->light = true;
        currentt = currentt->next;
        countOp++;
    }

    std::cerr << "Ошибка: превышен лимит шагов. Возможен бесконечный цикл.\n";
    return -1;    
}
int Train::getOpCount() {
    return countOp;
}
