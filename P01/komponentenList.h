//
// Created by martin on 24.05.23.
//

#ifndef PRAKTIKUM1_KOMPONENTENLIST_H
#define PRAKTIKUM1_KOMPONENTENLIST_H
#include "komponente.h"


struct KomponentenElement {
    Komponente* k;
    KomponentenElement* before;
    KomponentenElement* next;
};


class KomponentenList {
private:
    int counter;
    KomponentenElement* first;
    KomponentenElement* getElement(int pos) const;
public:
    KomponentenList();
    ~KomponentenList();
    int size() const;
    Komponente const* at(int pos) const;
    int erase(int pos);
    void push_back(Komponente* k);
    KomponentenElement* end() const;
    KomponentenElement* begin() const;
};

#endif //PRAKTIKUM1_KOMPONENTENLIST_H
