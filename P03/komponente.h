#ifndef PRAKTIKUM1_KOMPONENTE_H
#define PRAKTIKUM1_KOMPONENTE_H

#include <ostream>
#include "ikomponente.h"


class Komponente: public IKomponente {
private:
    double x;
    double y;
    IKomponente const* parent;
public:
    explicit Komponente(double xPos=0.0, double yPos=0.0);
    virtual ~Komponente();
    double getX() const override;
    double getY() const override;
    double getXAbsolute() const override;
    double getYAbsolute() const override;
    double distance(IKomponente const* k) const override;
    IKomponente const* getParent() const override;
    void setParent(IKomponente const* p) override;
    void output(std::ostream& os) const override;
    double calcTotalPath() const override;
    QJsonObject toJson() const override;
};


#endif //PRAKTIKUM1_KOMPONENTE_H
