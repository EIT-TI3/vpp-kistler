#ifndef PRAKTIKUM1_KOMPONENTE_H
#define PRAKTIKUM1_KOMPONENTE_H

#include <ostream>

class Komponente {
private:
    double x;
    double y;
public:
    explicit Komponente(double xPos=0.0, double yPos=0.0);
    virtual ~Komponente();
    double getX() const;
    double getY() const;

    virtual void output(std::ostream& os) const;
};

inline std::ostream& operator<<(std::ostream& os, const Komponente& k) {
    k.output(os);
    return os;
}
#endif //PRAKTIKUM1_KOMPONENTE_H
