#include "Student.h"
#include "Utils.h"
#include <deque>
#include <iostream>
#include <list>
#include <vector>

int main() {
  try {
    int choice;
    std::cout << "Select Strategy:\n";
    std::cout << "1. Strategy 1: Split into two new containers (Inefficient memory)\n";
    std::cout << "2. Strategy 2: Remove from original container (Potentially slow deletion)\n";
    std::cout << "3. Strategy 3: Optimized with <algorithm> (Fastest)\n";
    std::cout << "Enter choice: ";
    if (!(std::cin >> choice) || choice < 1 || choice > 3) {
        std::cerr << "Invalid choice.\n";
        return 1;
    }

    std::vector<int> sizes = {1000, 10000, 100000, 1000000}; // Removed 10M for quick testing if needed, or keep 1M

    for (int size : sizes) {
      std::string filename = "students_" + std::to_string(size) + ".txt";
      std::cout << "\n--- Size: " << size << " records ---" << std::endl;

      if (std::ifstream(filename).fail()) {
          std::cout << "Generating data..." << std::endl;
          Utils::generateDataFile(filename, size);
      }

      std::cout << "Processing records..." << std::endl;
      Utils::processRecords<std::vector<Student>>(filename, choice, "vector");
      Utils::processRecords<std::deque<Student>>(filename, choice, "deque");
      Utils::processRecords<std::list<Student>>(filename, choice, "list");
    }
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
