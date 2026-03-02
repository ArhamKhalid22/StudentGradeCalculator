#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <deque>
#include <string>
#include <chrono>
#include <random>
#include <algorithm>
#include "Person.h"

// --- Utility: Generate random data file ---
void generateData(const std::string& filename, int count) {
    std::ofstream out(filename);
    if (!out) return;
    out << "Name Surname HW1 HW2 HW3 HW4 HW5 Exam\n";
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10);

    for (int i = 1; i <= count; ++i) {
        out << "Name" << i << " Surname" << i << " ";
        for (int j = 0; j < 5; ++j) out << dis(gen) << " ";
        out << dis(gen) << "\n";
    }
}

// --- Template logic for Vector, List, and Deque ---
template <typename T>
void runPerformanceTest(const std::string& containerName, const std::string& filename) {
    T students;
    T failed;

    auto start = std::chrono::high_resolution_clock::now();

    // 1. Reading
    std::ifstream in(filename);
    std::string header;
    std::getline(in, header); // Skip header

    std::string f, l;
    while (in >> f >> l) {
        std::vector<int> hws;
        int grade, exam;
        for (int i = 0; i < 5; ++i) {
            in >> grade;
            hws.push_back(grade);
        }
        in >> exam;
        students.emplace_back(f, l, hws, exam);
    }

    // 2. Sorting
    // Lists have their own member sort; Vectors/Deques use std::sort
    if constexpr (std::is_same_v<T, std::list<Person>>) {
        students.sort([](const Person& a, const Person& b) {
            return a.getLastName() < b.getLastName();
        });
    } else {
        std::sort(students.begin(), students.end(), [](const Person& a, const Person& b) {
            return a.getLastName() < b.getLastName();
        });
    }

    // 3. Splitting (Optimized Move)
    auto it = students.begin();
    while (it != students.end()) {
        if (it->getFinal() < 5.0) {
            failed.push_back(std::move(*it));
            it = students.erase(it);
        } else {
            ++it;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

    std::cout << containerName << " processed " << filename 
              << " in " << diff.count() << "s" << std::endl;
}

int main() {
    try {
        std::vector<int> sizes = {1000, 10000, 100000}; // Add 1M and 10M for full test

        for (int count : sizes) {
            std::string filename = "students" + std::to_string(count) + ".txt";
            std::cout << "\n--- Size: " << count << " ---" << std::endl;
            
            generateData(filename, count);

            // Run comparison
            runPerformanceTest<std::vector<Person>>("Vector", filename);
            runPerformanceTest<std::deque<Person>>("Deque ", filename);
            runPerformanceTest<std::list<Person>>("List  ", filename);
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
