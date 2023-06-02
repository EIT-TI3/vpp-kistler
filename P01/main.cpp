//
// Created by martin on 24.05.23.
//
#include <iostream>
#include "komponentenList.h"
#include "fraesung.h"


int main() {
    auto b1 = Bohrung(1, 2, 8);
    auto b2 = Bohrung(2, 6, 4);
    auto b3 = Bohrung(10, 8, 7);
    auto b4 = Bohrung(7, 2, 5);
    auto f1 = Fraesung(2, 3, 5, M_SQRT2*2, M_PI/4);
    auto f2 = Fraesung(6, 7, 6, 3);
    auto f3 = Fraesung(17, 6, 4, M_SQRT2 * 4, 1.25 * M_PI);
    auto kl = KomponentenList();
    kl.push_back(&b1);
    kl.push_back(&f1);
    kl.push_back(&b3);
    kl.push_back(&f2);
    kl.push_back(&b4);
    kl.push_back(&f3);
    kl.push_back(&b2);

    for (int i = 0; i < kl.size(); i++) {
        std::cout << *kl.at(i) << "\n";
    }
}