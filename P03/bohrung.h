#ifndef PRAKTIKUM1_BOHRUNG_H
#define PRAKTIKUM1_BOHRUNG_H

#include "komponente.h"

class Bohrung: public Komponente {
private:
    double diameter;
public:
    explicit Bohrung(double x_=0.0, double y_=0.0, double diam=6.0);
    ~Bohrung() override;
    double getDiameter() const;
    void output(std::ostream& os) const override;
    QJsonObject toJson() const override;
};

#endif //PRAKTIKUM1_BOHRUNG_H
