#include "Utils.h"

namespace Utils {

void generateDataFile(const std::string &filename, int count) {
  std::ofstream out(filename);
  if (!out)
    throw std::runtime_error("Could not create file: " + filename);

  out << std::left << std::setw(20) << "Name" << std::setw(20) << "Surname";
  for (int i = 1; i <= 5; ++i)
    out << std::setw(10) << "HW" + std::to_string(i);
  out << std::setw(10) << "Exam" << "\n";

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> scoreDis(1, 10);

  for (int i = 1; i <= count; ++i) {
    out << std::left << std::setw(20) << ("Name" + std::to_string(i))
        << std::setw(20) << ("Surname" + std::to_string(i));
    for (int j = 0; j < 5; ++j)
      out << std::setw(10) << scoreDis(gen);
    out << std::setw(10) << scoreDis(gen) << "\n";
  }
  out.close();
}

} // namespace Utils
