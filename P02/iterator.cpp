//
// Created by martin on 15.06.23.
//

#include "iterator.h"

Iterator::Iterator(IKomponentenElement* begin) {
    curr = begin;
}

Iterator::~Iterator() = default;

