//
// Created by martin on 16.06.23.
//

#ifndef PRAKTIKUM2_WERKSTUECK_H
#define PRAKTIKUM2_WERKSTUECK_H

#include "komponente.h"
#include "delist.h"

class Werkstueck: public Komponente {

private:
    double height;
    double width;
    bool pathIsOptimized;
    DeList components;
    Iterator getNearest(IKomponente const* pk) const;

public:
    explicit Werkstueck(double xPos = 0.0, double yPos = 0.0, double h = 1, double w = 1);
    ~Werkstueck() override = default;

    void add(IKomponente* k);
    void remove(IKomponente* k);
    double getHeight() const;
    double getWidth() const;
    IKomponente const* getChild(int i) const;
    double calcTotalPath() const override;
    double calcPathLength() const;
    void optimizePath();
    void output(std::ostream& os) const override;

};


#endif //PRAKTIKUM2_WERKSTUECK_H
