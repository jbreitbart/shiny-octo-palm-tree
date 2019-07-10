#include <chrono>
#include <iostream>

#include "lib/gcd.hpp"

int main(int /*argc*/, char** /*argv*/)
{
    auto start = std::chrono::high_resolution_clock::now();

    std::cout << "gcd(-100, 25) = " << gcd(-100, 25) << std::endl;
    std::cout << "gcd(100, 25) = " << gcd(100, 25) << std::endl;

    auto elapsed = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count();
    std::cout << "Execution time was " << elapsed << " seconds.\n";

    return 0;
}
