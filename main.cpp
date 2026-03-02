#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include "Person.h"

// Function to generate test files (as discussed)
void generateData(std::string name, int count);

int main() {
    // 1. Setup the sizes for testing
    std::vector<int> testSizes = {10000, 100000, 1000000};
    
    for (int size : testSizes) {
        std::string filename = "students" + std::to_string(size) + ".txt";
        
        std::cout << "\n--- Testing with " << size << " records ---" << std::endl;
        
        // Step A: Generate the file
        generateData(filename, size);

        // Step B: Start Timer
        auto start = std::chrono::high_resolution_clock::now();

        try {
            std::ifstream inFile(filename);
            if (!inFile) throw std::runtime_error("Could not open file!");

            std::vector<Person> allStudents;
            std::vector<Person> passed;
            std::vector<Person> failed;

            // Step C: Read and Process (Simulation of the loop)
            // In reality, you would use your overloaded >> or a custom read function
            // ... (Reading Logic) ...

            // Step D: Split into two categories
            for (auto& s : allStudents) {
                if (s.getFinal() >= 5.0) passed.push_back(s);
                else failed.push_back(s);
            }

            // Step E: Save to two files
            std::ofstream outP("passed.txt"), outF("failed.txt");
            for (const auto& p : passed) outP << p << "\n";
            for (const auto& f : failed) outF << f << "\n";

        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }

        // Step F: Stop Timer
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        
        std::cout << "Total time for " << size << ": " << diff.count() << " seconds" << std::endl;
    }

    return 0;
}
