#include "komponente.h"
#include <cmath>


Komponente::Komponente(double xPos, double yPos): x{xPos}, y{yPos}, parent(nullptr) {
    if (x < 0) x = 0;
    if (y < 0) y = 0;
}

Komponente::~Komponente() = default;

double Komponente::getX() const {
    return x;
}

double Komponente::getY() const {
    return y;
}

void Komponente::output(std::ostream &os) const {
    os << "(" << getX() << ", " << getY() << ")";
}

double Komponente::getXAbsolute() const {
    double xabs = getX();

    IKomponente const* p = getParent();
    if (p != nullptr) xabs += p->getXAbsolute();

    return xabs;
}

double Komponente::getYAbsolute() const {
    double yabs = getY();

    IKomponente const* p = getParent();
    if (p != nullptr) yabs += p->getYAbsolute();

    return yabs;
}

double Komponente::distance(const IKomponente *k) const {
    if (k == nullptr) return 0;
    double dx = getXAbsolute() - k->getXAbsolute();
    double dy = getYAbsolute() - k->getYAbsolute();
    return std::sqrt(dx*dx + dy*dy);
}

IKomponente const *Komponente::getParent() const {
    return parent;
}

void Komponente::setParent(const IKomponente *p) {
    parent = p;
}

double Komponente::calcTotalPath() const {
    return 0.0;
}

QJsonObject Komponente::toJson() const {
    return QJsonObject{
            {"type",      "Komponente"},
            {"x",         getX()},
            {"y",         getY()},
            {"hasParent", getParent() != nullptr}};
}
