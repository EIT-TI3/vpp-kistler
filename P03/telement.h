//
// Created by martin on 16.06.23.
//

#ifndef PRAKTIKUM2_TELEMENT_H
#define PRAKTIKUM2_TELEMENT_H


template<typename T>
struct TElement {
    T k;
    TElement* before;
    TElement* next;
};

#endif //PRAKTIKUM2_TELEMENT_H
