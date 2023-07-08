//
// Created by martin on 16.06.23.
//

#ifndef PRAKTIKUM2_IKOMPONENTENELEMENT_H
#define PRAKTIKUM2_IKOMPONENTENELEMENT_H

#include "ikomponente.h"

struct IKomponentenElement {
    IKomponente* k;
    IKomponentenElement* before;
    IKomponentenElement* next;
};

#endif //PRAKTIKUM2_IKOMPONENTENELEMENT_H
