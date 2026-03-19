#ifndef UTILS_H
#define UTILS_H

#include "Student.h"
#include <chrono>
#include <deque>
#include <fstream>
#include <iostream>
#include <list>
#include <random>
#include <sstream>
#include <string>
#include <type_traits>
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

template <typename Container>
void processRecords(const std::string &inputFile, const std::string &passedFile,
                    const std::string &failedFile,
                    const std::string &containerName) {
  Timer totalTimer;

  std::ifstream in(inputFile);
  if (!in)
    throw std::runtime_error("File not found: " + inputFile);

  Container students;
  std::string line;
  std::getline(in, line); // Skip header

  Timer readTimer;
  while (std::getline(in, line)) {
    if (line.empty())
      continue;
    std::stringstream ss(line);
    std::string n, s;
    if (!(ss >> n >> s)) continue;
    
    std::vector<int> hws;
    int val;
    for (int i = 0; i < 5; ++i) {
      if (ss >> val)
        hws.push_back(val);
    }
    int exam;
    if (ss >> exam) {
      students.emplace_back(n, s, hws, exam);
    }
  }
  double readTime = readTimer.elapsed();
  in.close();

  Timer sortTimer;
  auto comp = [](const Student &a, const Student &b) {
    return a.getSurname() < b.getSurname();
  };

  if constexpr (std::is_same_v<Container, std::list<Student>>) {
    students.sort(comp);
  } else {
    std::sort(students.begin(), students.end(), comp);
  }
  double sortTime = sortTimer.elapsed();

  Timer splitTimer;
  Container passed, failed;
  for (const auto &s : students) {
    if (s.getFinalPoint() >= 5.0)
      passed.push_back(s);
    else
      failed.push_back(s);
  }
  double splitTime = splitTimer.elapsed();

  Timer writeTimer;
  std::ofstream outPassed(passedFile + "_" + containerName + ".txt");
  std::ofstream outFailed(failedFile + "_" + containerName + ".txt");

  if (!outPassed || !outFailed)
    throw std::runtime_error("Could not open output files");

  outPassed << std::left << std::setw(15) << "Surname" << std::setw(15)
            << "Name" << "Final\n";
  for (const auto &s : passed)
    outPassed << s << "\n";

  outFailed << std::left << std::setw(15) << "Surname" << std::setw(15)
            << "Name" << "Final\n";
  for (const auto &s : failed)
    outFailed << s << "\n";

  double writeTime = writeTimer.elapsed();

  std::cout << "Container: " << std::left << std::setw(10) << containerName
            << " | Read: " << std::fixed << std::setprecision(4) << readTime
            << "s | Sort: " << sortTime << "s | Split: " << splitTime
            << "s | Write: " << writeTime << "s\n";
}

} // namespace Utils

#endif
