//
// Created by martin on 02.06.23.
//

#ifndef P02_IKOMPONENTE_H
#define P02_IKOMPONENTE_H

#include <iostream>
#include <QJsonObject>


class IKomponente {
public:
    virtual ~IKomponente();
    virtual double calcTotalPath() const = 0;
    virtual double getXAbsolute() const = 0;
    virtual double getYAbsolute() const = 0;
    virtual double getX() const = 0;
    virtual double getY() const = 0;
    virtual double distance(IKomponente const* k) const = 0;
    virtual IKomponente const* getParent() const = 0;
    virtual void setParent(IKomponente const* p) = 0;
    virtual void output(std::ostream& os) const = 0;
    virtual QJsonObject toJson() const = 0;
};

inline std::ostream& operator<<(std::ostream& os, const IKomponente& ik) {
    ik.output(os);
    return os;
}

#endif //P02_IKOMPONENTE_H
