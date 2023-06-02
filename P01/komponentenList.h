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
    KomponentenElement* getElement(int pos);
public:
    KomponentenList();
    ~KomponentenList();
    int size() const;
    Komponente const* at(int pos);
    int erase(int pos);
    void push_back(Komponente* k);
    static KomponentenElement* end();
    KomponentenElement* begin();
};

#endif //PRAKTIKUM1_KOMPONENTENLIST_H
