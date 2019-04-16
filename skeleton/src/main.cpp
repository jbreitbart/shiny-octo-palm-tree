#include <chrono>
#include <iostream>

int main(int /*argc*/, char** /*argv*/)
{
    auto start = std::chrono::high_resolution_clock::now();

    std::cout << "Hello world!" << std::endl;

    auto elapsed = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count();
    std::cout << "Execution time was " << elapsed << " seconds.";

    return 0;
}
