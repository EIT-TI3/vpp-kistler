//
// Created by martin on 23.06.23.
//

#ifndef PRAKTIKUM3_SERIALIZER_H
#define PRAKTIKUM3_SERIALIZER_H

#include "ikomponente.h"


class Serializer {
private:
    IKomponente const& ik;
public:
    Serializer(IKomponente const& root);
    ~Serializer();
    void writeToJson(char const* fname);
};

#endif //PRAKTIKUM3_SERIALIZER_H
