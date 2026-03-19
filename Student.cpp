#include "Student.h"

Student::Student() : name(""), surname(""), exam(0), finalPoint(0.0) {}

Student::Student(std::string n, std::string s, std::vector<int> hw, int e)
    : name(n), surname(s), homeworks(hw), exam(e) {
  calculateFinal();
}

void Student::calculateFinal(bool useMedian) {
  if (homeworks.empty()) {
    finalPoint = 0.6 * exam;
    return;
  }

  double hwResult = 0.0;
  if (useMedian) {
    std::vector<int> sortedHw = homeworks;
    std::sort(sortedHw.begin(), sortedHw.end());
    size_t n = sortedHw.size();
    if (n % 2 == 0) {
      hwResult = (sortedHw[n / 2 - 1] + sortedHw[n / 2]) / 2.0;
    } else {
      hwResult = sortedHw[n / 2];
    }
  } else {
    hwResult = std::accumulate(homeworks.begin(), homeworks.end(), 0.0) /
               homeworks.size();
  }

  finalPoint = 0.4 * hwResult + 0.6 * exam;
}

std::ostream &operator<<(std::ostream &os, const Student &s) {
  os << std::left << std::setw(15) << s.surname << std::setw(15) << s.name
     << std::fixed << std::setprecision(2) << s.finalPoint;
  return os;
}

std::istream &operator>>(std::istream &is, Student &s) {
  if (!(is >> s.name >> s.surname))
    return is;
  // This version assumes a fixed number of HWs (5) then Exam
  std::vector<int> hws(5);
  for(int i=0; i<5; ++i) {
      if(!(is >> hws[i])) return is;
  }
  int ex;
  if(is >> ex) {
      s.homeworks = hws;
      s.exam = ex;
      s.calculateFinal();
  }
  return is;
}
