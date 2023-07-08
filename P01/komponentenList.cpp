//
// Created by martin on 24.05.23.
//

#include "komponentenList.h"


KomponentenList::KomponentenList(): counter(0), first(nullptr) {}

int KomponentenList::size() const {
    return counter;
}

KomponentenElement *KomponentenList::end() const {
    return nullptr;
}

KomponentenElement *KomponentenList::begin() const {
    return first;
}

void KomponentenList::push_back(Komponente *k) {
    auto ke = new KomponentenElement;
    ke->k = k;
    ke->next = nullptr;
    if (first == nullptr) {
        ke->before = nullptr;
        first = ke;
    } else {
        auto ke_last = getElement(counter - 1);
        ke_last->next = ke;
        ke->before = ke_last;
    }

    counter++;
}

KomponentenElement *KomponentenList::getElement(int pos) const {
    if (pos < 0 or pos > counter - 1) return nullptr;

    auto ke = first;

    for (int i = 0; i < pos && ke != nullptr; i++) {
        ke = ke->next;
    }
    return ke;
}


const Komponente *KomponentenList::at(int pos) const {

    auto ke = getElement(pos);
    return ke == nullptr? nullptr: ke->k;
}

int KomponentenList::erase(int pos) {
    auto ke = getElement(pos);
    if (ke == nullptr) return -1;

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

    return pos;
}

KomponentenList::~KomponentenList() {
    auto ke = first;
    for (int i = 0; i < counter && ke != nullptr; i++) {
        auto ke_next = ke->next;
        delete ke;
        ke = ke_next;
    }
    first = nullptr;
    counter = 0;
}