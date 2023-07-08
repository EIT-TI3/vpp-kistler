#ifndef PRAKTIKUM1_FRAESUNG_H
#define PRAKTIKUM1_FRAESUNG_H

#include "bohrung.h"
#include <cmath>

class Fraesung: public Bohrung {
private:
    double length;
    double angle;
public:
    Fraesung(double x, double y, double diam, double l, double a = 0.0);
    ~Fraesung() override;
    double getLength() const;
    double getAngle() const;
    double getEndX() const;
    double getEndY() const;
    void output(std::ostream& os) const override;
    double calcTotalPath() const override;
    QJsonObject toJson() const override;
};

#endif //PRAKTIKUM1_FRAESUNG_H
