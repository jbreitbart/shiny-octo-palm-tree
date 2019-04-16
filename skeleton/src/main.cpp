#include <chrono>
#include <iostream>

int main(int /*argc*/, char ** /*argv*/) {

	auto tStart = std::chrono::high_resolution_clock::now();

	std::cout << "Hello world!" << std::endl;

	auto tElapsed = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - tStart).count();
	std::cout << "Execution time was " << tElapsed << "{:0.3f} seconds.";

	return 0;
}
