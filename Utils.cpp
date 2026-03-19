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

void processRecords(const std::string &inputFile, const std::string &passedFile,
                    const std::string &failedFile,
                    const std::string &containerName) {
  Timer totalTimer;

  std::ifstream in(inputFile);
  if (!in)
    throw std::runtime_error("File not found: " + inputFile);

  std::vector<Student> students;
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

  std::sort(students.begin(), students.end(), comp);
  double sortTime = sortTimer.elapsed();

  Timer splitTimer;
  std::vector<Student> passed, failed;
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
