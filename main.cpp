#include "Student.h"
#include "Utils.h"
#include <iostream>
#include <vector>

int main() {
  try {
    std::vector<int> sizes = {10000, 100000, 1000000, 10000000};

    for (int size : sizes) {
      std::string filename = "students_" + std::to_string(size) + ".txt";
      std::cout << "\n--- Size: " << size << " records ---" << std::endl;

      std::cout << "Generating data..." << std::endl;
      Utils::generateDataFile(filename, size);

      std::cout << "Processing records (vector only)..." << std::endl;
      Utils::processRecords(filename, "passed_" + std::to_string(size), 
                            "failed_" + std::to_string(size), "vector");
    }
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
