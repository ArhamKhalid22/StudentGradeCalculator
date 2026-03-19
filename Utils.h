#ifndef UTILS_H
#define UTILS_H

#include "Student.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

namespace Utils {

void generateDataFile(const std::string &filename, int count);

class Timer {
private:
  std::chrono::time_point<std::chrono::high_resolution_clock> start;

public:
  Timer() : start(std::chrono::high_resolution_clock::now()) {}
  double elapsed() {
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    return diff.count();
  }
  void reset() { start = std::chrono::high_resolution_clock::now(); }
};

void processRecords(const std::string &inputFile, const std::string &passedFile,
                    const std::string &failedFile,
                    const std::string &containerName);

} // namespace Utils

#endif
