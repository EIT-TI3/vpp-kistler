//
// Created by martin on 24.05.23.
//

#ifndef PRAKTIKUM1_KOMPONENTENLIST_H
#define PRAKTIKUM1_KOMPONENTENLIST_H

#include "komponente.h"
#include "iterator.h"
#include "ikomponentenelement.h"

class DeList {
private:
    int counter;
    IKomponentenElement* first;
    IKomponentenElement* getElement(Iterator it) const;
public:
    DeList();
    DeList(const DeList& rhs);
    ~DeList();
    int size() const;
    Iterator erase(Iterator pos);
    void push_back(IKomponente* k);
    Iterator end() const;
    Iterator begin() const;
    void clear();

    DeList& operator=(DeList const& rhs);

};

#endif //PRAKTIKUM1_KOMPONENTENLIST_H
