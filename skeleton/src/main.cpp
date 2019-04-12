#include <chrono>

#include <cstring>

#include "app/log.h"

int main(int /*argc*/, char ** /*argv*/) {
	logger->set_level(spdlog::level::info);

	logger->info("Hello World");

	auto tStart = std::chrono::high_resolution_clock::now();

	auto tElapsed = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - tStart).count();

	logger->info("Execution time was {:0.3f} seconds.", tElapsed);

	return 0;
}
