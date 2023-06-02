#include "komponente.h"

Komponente::Komponente(double xPos, double yPos): x{xPos}, y{yPos} {
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
    os << "(" << x << ", " << y << ")";
}

