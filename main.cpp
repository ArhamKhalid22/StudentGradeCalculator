#include "Student.h"
#include "Utils.h"
#include <deque>
#include <iostream>
#include <list>
#include <vector>

int main() {
  try {
    // Requirements for v0.25: 1000, 10000, 100000, 1000000, 10000000
    std::vector<int> sizes = {1000, 10000, 100000, 1000000, 10000000};

    for (int size : sizes) {
      std::string filename = "students_" + std::to_string(size) + ".txt";
      std::cout << "\n--- Size: " << size << " records ---" << std::endl;

      std::cout << "Generating data..." << std::endl;
      Utils::generateDataFile(filename, size);

      std::cout << "Processing records (vector, deque, list)..." << std::endl;
      Utils::processRecords<std::vector<Student>>(filename, "passed_" + std::to_string(size), 
                                                   "failed_" + std::to_string(size), "vector");
      Utils::processRecords<std::deque<Student>>(filename, "passed_" + std::to_string(size), 
                                                 "failed_" + std::to_string(size), "deque");
      Utils::processRecords<std::list<Student>>(filename, "passed_" + std::to_string(size), 
                                                "failed_" + std::to_string(size), "list");
    }
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
