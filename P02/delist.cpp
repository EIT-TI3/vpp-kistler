//
// Created by martin on 24.05.23.
//

#include "delist.h"


DeList::DeList(): counter(0), first(nullptr) {}

int DeList::size() const {
    return counter;
}

Iterator DeList::end() const {
    return Iterator();
}


Iterator DeList::begin() const {
    return Iterator(first);
}


void DeList::push_back(IKomponente *k) {
    auto ke = new IKomponentenElement;
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


IKomponentenElement *DeList::getElement(Iterator it) const {
    auto selected_element = first;
    IKomponentenElement* found_element = nullptr;
    if (it != Iterator()) {
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


Iterator DeList::erase(Iterator pos) {
    auto ke = getElement(pos);
    if (ke == nullptr) return Iterator();

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

DeList::~DeList() {
    clear();
}

void DeList::clear() {
    auto ke = first;
    while(ke) {
    //for (int i = 0; i < counter && ke != nullptr; i++) {
        auto ke_next = ke->next;
        delete ke;
        ke = ke_next;
    }
    first = nullptr;
    counter = 0;
}


DeList::DeList(const DeList &rhs) {
    counter = 0;
    first = nullptr;
    for (auto element : rhs) {
        push_back(element);
    }
}


DeList &DeList::operator=(const DeList &rhs) {
    if (this != &rhs) {
        clear();
        for (auto element : rhs) {
            push_back(element);
        }
    }
    return *this;
}

