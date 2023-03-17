#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <fstream>

#define U_MIN 4.5
#define U_MAX 5.5
#define OUTPUTFILENAME "samples.txt"


int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: generate_samples [SAMPLES]\n";
        return 1;
    }
    
    uint samples;
    try {
        samples = std::stoi(argv[1]);
        std::cout << samples;
    }
    catch(std::invalid_argument const& ex) {
        std::cout << "SAMPLES must be an 64 bit integer!\n";
        return 2;
    }
    catch(std::out_of_range const& ex) {
        std::cout << "SAMPLES must be an 64 bit integer!\n";
        return 2;
    }

    std::cout << "Generating samples...\n";

    std::srand(std::time(nullptr));

    std::ofstream outputfile;
    outputfile.open(OUTPUTFILENAME);

    for (uint i = 0; i < samples; i++) {
        double x = U_MIN + (static_cast<double>(std::rand()) / RAND_MAX) * (U_MAX - U_MIN);
        outputfile << x << "V\n";
        std::cout << 100*static_cast<double>(i)/samples << "%\n";
    }
    
    std::cout << "Finished!\n";
    return 0;
}
