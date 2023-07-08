//
// Created by martin on 24.05.23.
//

#ifndef PRAKTIKUM1_KOMPONENTENLIST_H
#define PRAKTIKUM1_KOMPONENTENLIST_H

#include "komponente.h"
#include "iterator.h"
#include "telement.h"


template<typename T>
class DeList {
private:
    int counter;
    TElement<T>* first;

    TElement<T>* getElement(Iterator<T> it) const {
        auto selected_element = first;
        TElement<T>* found_element = nullptr;
        if (it != Iterator<T>()) {
            for (int i = 0; i < counter; i++) {
                if (selected_element->k == *it) {
                    found_element = selected_element;
                    break;
                }
                selected_element = selected_element->next;
            }
        }
        return found_element;
    }

public:
    DeList(): counter(0), first(nullptr) {}

    DeList(const DeList& rhs){
        counter = 0;
        first = nullptr;
        for (auto element : rhs) {
            push_back(element);
        }
    }

    ~DeList() {
        clear();
    }

    int size() const {
        return counter;
    };

    Iterator<T> erase(Iterator<T> pos) {
        auto ke = getElement(pos);
        if (ke == nullptr) return Iterator<T>();

        auto ke_next = ke->next;
        auto ke_before = ke->before;

        if (counter == 1) {
            first = nullptr;
        }

        else if (ke == first) {
            first = ke->next;
            ke_next->before = nullptr;
        }
        else if (ke->next == nullptr) {
            ke_before->next = nullptr;
        }
        else {
            ke_before->next = ke_next;
            ke_next->before = ke_before;
        }
        delete ke;
        counter --;

        return Iterator(ke_next);
    }

    void push_back(T k){
        auto ke = new TElement<T>;
        ke->k = k;
        ke->next = nullptr;
        ke->before = nullptr;

        if (first == nullptr) {
            first = ke;
        } else {
            auto ke_last = first;
            while (ke_last->next != nullptr) ke_last = ke_last->next;
            ke_last->next = ke;
            ke->before = ke_last;
        }

        counter++;
    }

    Iterator<T> end() const {
        return Iterator<T>();
    }

    Iterator<T> begin() const {
        return Iterator(first);
    }

    void clear() {
        auto ke = first;
        while(ke) {
            auto ke_next = ke->next;
            delete ke;
            ke = ke_next;
        }
        first = nullptr;
        counter = 0;
    }

    DeList& operator=(DeList const& rhs) {
        if (this != &rhs) {
            clear();
            for (auto element : rhs) {
                push_back(element);
            }
        }
        return *this;
    }

};

#endif //PRAKTIKUM1_KOMPONENTENLIST_H
