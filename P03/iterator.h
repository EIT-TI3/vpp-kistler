//
// Created by martin on 15.06.23.
//

#ifndef PRAKTIKUM2_ITERATOR_H
#define PRAKTIKUM2_ITERATOR_H

#include "telement.h"


template<typename T>
class Iterator {
private:
    TElement<T>* curr;
public:
    explicit Iterator(TElement<T>* begin = nullptr): curr(begin) {}
    ~Iterator() = default;

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

    T operator*() const {
        return curr->k;
    }
};


#endif //PRAKTIKUM2_ITERATOR_H
