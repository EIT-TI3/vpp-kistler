#include "fraesung.h"


Fraesung::Fraesung(double x, double y, double diam, double l, double a): Bohrung(x, y, diam), length(l), angle(a) {
    if (length < 0) length = 0;
    if (angle < 0) angle = 0;
    if (angle > 360) angle = 360;
};

Fraesung::~Fraesung() = default;

double Fraesung::getLength() const {
    return length;
}

double Fraesung::getAngle() const {
    return angle;
}

double Fraesung::getEndX() const {
    return getX() + length * std::cos(angle);

}

double Fraesung::getEndY() const {
    return getY() + length * std::sin(angle);
}

void Fraesung::output(std::ostream &os) const {
    os << "Fraesung mit Start: ";
    Komponente::output(os);
    os << " und Endpunkt: (" << getEndX() << ", " << getEndY() << "), Durchmesser: " << getDiameter();
}
