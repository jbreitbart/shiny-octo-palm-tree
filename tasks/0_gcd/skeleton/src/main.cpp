#include <chrono>
#include <iostream>

#include "lib/gcd.hpp"

int main(int /*argc*/, char** /*argv*/)
{
    auto start = std::chrono::high_resolution_clock::now();

    std::cout << "gcd (4,12) = " << gcd(4, 12) << std::endl;

    auto elapsed = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count();
    std::cout << "Execution time was " << elapsed << " seconds.";

    return 0;
}
