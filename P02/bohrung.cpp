#include "bohrung.h"

Bohrung::Bohrung(double x_, double y_, double diam): Komponente(x_, y_), diameter(diam) {
    if (diameter <= 0) diameter = 6.;
}

Bohrung::~Bohrung() = default;

double Bohrung::getDiameter() const {
    return diameter;
}

void Bohrung::output(std::ostream &os) const {
    os << "Bohrung: ";
    Komponente::output(os);
    os << ", Durchmesser: " << getDiameter();
}