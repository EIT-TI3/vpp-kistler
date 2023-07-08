//
// Created by martin on 15.06.23.
//

#ifndef PRAKTIKUM2_ITERATOR_H
#define PRAKTIKUM2_ITERATOR_H

#include "ikomponentenelement.h"


class Iterator {
private:
    IKomponentenElement* curr;
public:
    explicit Iterator(IKomponentenElement* begin = nullptr);
    ~Iterator();

    Iterator& operator++() {
        curr = curr->next;
        return *this;
    }

    bool operator!=(Iterator const& it) const {
        return !operator==(it);
    }

    bool operator==(Iterator const& it) const {
        return this->curr == it.curr;
    }

    IKomponente* operator*() const {
        if (curr == nullptr) return nullptr;
        else return curr->k;
    }
};


#endif //PRAKTIKUM2_ITERATOR_H
