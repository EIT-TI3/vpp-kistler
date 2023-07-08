//
// Created by martin on 16.06.23.
//
#include "werkstueck.h"
#include "ikomponente.h"
#include "iterator.h"


Werkstueck::Werkstueck(double xPos, double yPos, double h, double w) : Komponente(xPos, yPos), height{h}, width{w}, pathIsOptimized{false} {
    if (height < 0) height = 0;
    if (width < 0) width = 0;
}

double Werkstueck::getHeight() const {
    return height;
}

double Werkstueck::getWidth() const {
    return width;
}

void Werkstueck::add(IKomponente *k) {
    if (k != nullptr && k->getParent() != nullptr) {
        k->setParent(this);
        components.push_back(k);
        pathIsOptimized = false;
    }
}

void Werkstueck::remove(IKomponente *k) {
    auto iter_komponente = components.begin();
    while (iter_komponente != components.end()) {
        if (*iter_komponente == k) {
            components.erase(iter_komponente);
            k->setParent(nullptr);
            pathIsOptimized = false;
        }
        ++iter_komponente;
    }
}

IKomponente const *Werkstueck::getChild(int i) const {
    for (auto element: components) {
        if (i == 0) {
            return element;
        }
        i--;
    }
    return nullptr;
}


double Werkstueck::calcPathLength() const {
    double dist = 0;
    const IKomponente* pe = this;
    for (auto element: components) {
        dist += element->distance(pe);
        pe = element;
    }
    dist += pe->distance(this);
    return dist;
}

double Werkstueck::calcTotalPath() const {
    double dist = calcPathLength();
    for (auto element: components)
        dist += element->calcTotalPath();
    return dist;
}


void Werkstueck::output(std::ostream &os) const {
    std::string pad;
    const IKomponente* last_parent = getParent();
    while (last_parent != nullptr) {
        last_parent = last_parent->getParent();
        pad.append(" ");
    }

    os << pad << "Werkstueck:\n"
       << pad << "Verankerung: (" << getX() << ", " << getY() << ")\n"
       << pad << "height: " << height << ", width: " << width << "\n"
       << pad << "Komponenten:" << std::endl;

    for(auto element : components) {
        if (dynamic_cast<Werkstueck*>(element) == nullptr) {
            os << pad;
        }
        os << *element;
        if (dynamic_cast<Werkstueck*>(element) == nullptr) {
            os << std::endl;
        }
    }
}


Iterator Werkstueck::getNearest(const IKomponente *pk) const {
    auto iter_komponente = components.begin();
    if (iter_komponente == components.end()) {
        return Iterator();
    }

    auto nearest_iter = Iterator(iter_komponente);
    double nearest_distance = pk->distance(*nearest_iter);
    ++iter_komponente;

    while (iter_komponente != components.end()) {
        auto distance = pk->distance(*iter_komponente);
        if (distance < nearest_distance) {
            nearest_distance = distance;
            nearest_iter = Iterator(iter_komponente);
        }
        ++iter_komponente;
    }
    return nearest_iter;

}


// Solve approximately the Traveling salesman Problem (TSP) using a
// nearest neighbour strategy:
// round trip starts at the linking point of the Werkstueck.
// then go always to the nearest neighbour among the components
// that are not already on the new path
void Werkstueck::optimizePath() {
    if (!pathIsOptimized && components.size() > 0) {
        // first call optimizePath for all Components,
        // which are of type Werkstueck recursively
        Iterator it = components.begin();
        while (it != components.end()) {
            auto* w = dynamic_cast<Werkstueck*>(*it);
            if (w != nullptr) {
                w->optimizePath();
            }
            ++it;
        }
        // Now determine a nearest neighbour-sorting
        // of all components
        DeList componentsSorted;
        IKomponente* pcurrent = this;
        Iterator nearest = getNearest(pcurrent);
        componentsSorted.push_back(*nearest);
        pcurrent = *nearest;
        components.erase(nearest);
        while (components.size() > 0) {
            nearest = getNearest(pcurrent);
            componentsSorted.push_back(*nearest);
            pcurrent = *nearest;
            components.erase(nearest);
        }
        components = componentsSorted;
        pathIsOptimized = true;
    }
}