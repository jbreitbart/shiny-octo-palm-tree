#ifdef _WIN32
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#endif

#include <app/app.h>

#include <chrono>

#include <cstring>

#include "app/log.h"

int main(int /*argc*/, char ** /*argv*/) {
	logger->set_level(spdlog::level::info);

	logger->info("************************");
	logger->info("* BREADTH-FIRST-SEARCH *");
	logger->info("************************");
	logger->info("Performing breadth-first-search...");

	auto tStart = std::chrono::high_resolution_clock::now();

	int result = Application().run();

	auto tElapsed = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - tStart).count();

	logger->info("Execution time was {:0.3f} seconds.", tElapsed);

	return result;
}
