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
    return getX() + getLength() * std::cos(getAngle());
}

double Fraesung::getEndY() const {
    return getY() + getLength() * std::sin(getAngle());
}

void Fraesung::output(std::ostream &os) const {
    os << "Fraesung mit Start: ";
    Komponente::output(os);
    os << " und Endpunkt: (" << getEndX() << ", " << getEndY() << "), Durchmesser: " << getDiameter();
}

double Fraesung::calcTotalPath() const {
    return 2 * getLength();
}

QJsonObject Fraesung::toJson() const {
    auto jo = Bohrung::toJson();
    jo["type"] = "Fraesung";
    jo["angle"] = getAngle();
    jo["length"] = getLength();
    return jo;
}
