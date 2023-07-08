#include <iostream>
#include "fraesung.h"
#include "delist.h"
#include "werkstueck.h"
#include <cmath>


int main() {
    Werkstueck w0{0, 0, 18, 25};
    Bohrung b1{1, 2, 8};
    Bohrung b2{2, 6, 4};
    Bohrung b3{10, 8, 7};
    Bohrung b4{7, 2, 5};
    Fraesung f1{2, 3, 5, M_SQRT2 * 2, 0.25 * M_PI};
    Fraesung f2{6, 7, 6, 3, 0};
    Fraesung f3{17, 6, 4, M_SQRT2 * 4, 1.25 * M_PI};
    w0.add(&b1);
    w0.add(&b2);
    w0.add(&b3);
    w0.add(&b4);
    w0.add(&f1);
    w0.add(&f2);
    w0.add(&f3);

    Werkstueck w1{6, 10, 7, 18};
    w0.add(&w1);
    Bohrung b5{1, 2, 6};
    Bohrung b6{5, 1, 8};
    Fraesung f4{3, 3, 3, sqrt(2*2 + 1), M_PI - atan(1.0/2)};
    w1.add(&b5);
    w1.add(&b6);
    w1.add(&f4);

    Werkstueck w2{6, 3, 3, 10};
    w1.add(&w2);
    Bohrung b7{5, 2.5, 8};
    Bohrung b8{6, 0.5, 6};
    Fraesung f5{1, 2, 4, M_SQRT2 * 1, 1.75 * M_PI};
    w2.add(&b7);
    w2.add(&b8);
    w2.add(&f5);

    std::cout << w0 << std::endl;
    std::cout << "total Path w0: " << w0.calcTotalPath() << std::endl;
    std::cout << "Path length w0: " << w0.calcPathLength() << std::endl;
    std::cout << "total Path w1: " << w1.calcTotalPath() << std::endl;
    std::cout << "Path length w1: " << w1.calcPathLength() << std::endl;
    std::cout << "total Path w2: " << w2.calcTotalPath() << std::endl;
    std::cout << "Path length w2: " << w2.calcPathLength() << std::endl;

    w0.optimizePath();
    std::cout << "\nOptimierung der Pfad-Laenge:" << std::endl;
    std::cout << w0 << std::endl;
    std::cout << "total Path w0: " << w0.calcTotalPath() << std::endl;
    std::cout << "Path length w0: " << w0.calcPathLength() << std::endl;
    std::cout << "total Path w1: " << w1.calcTotalPath() << std::endl;
    std::cout << "Path length w1: " << w1.calcPathLength() << std::endl;
    std::cout << "total Path w2: " << w2.calcTotalPath() << std::endl;
    std::cout << "Path length w2: " << w2.calcPathLength() << std::endl;

    return 0;
}