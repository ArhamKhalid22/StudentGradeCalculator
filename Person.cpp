#include "Person.h"
#include <numeric>
#include <iomanip>

// Default Constructor
Person::Person() : exam(0), finalGrade(0.0) {}

// Parameterized Constructor
Person::Person(std::string f, std::string l, std::vector<int> h, int e) 
    : firstName(f), lastName(l), homeworks(h), exam(e) {
    calculateFinal(false); // Default to average
}

// 1. Destructor
Person::~Person() {
    homeworks.clear(); // Vector handles its own memory, but we clear it explicitly
}

// 2. Copy Constructor
Person::Person(const Person& other) {
    firstName = other.firstName;
    lastName = other.lastName;
    homeworks = other.homeworks;
    exam = other.exam;
    finalGrade = other.finalGrade;
}

// 3. Copy Assignment Operator
Person& Person::operator=(const Person& other) {
    if (this == &other) return *this; // Protect against self-assignment

    firstName = other.firstName;
    lastName = other.lastName;
    homeworks = other.homeworks;
    exam = other.exam;
    finalGrade = other.finalGrade;

    return *this;
}

// Final Grade Calculation
void Person::calculateFinal(bool useMedian) {
    if (homeworks.empty()) {
        finalGrade = 0.6 * exam;
        return;
    }

    double hwResult = 0;
    if (useMedian) {
        std::vector<int> temp = homeworks;
        std::sort(temp.begin(), temp.end());
        size_t size = temp.size();
        hwResult = (size % 2 == 0) ? (temp[size/2 - 1] + temp[size/2]) / 2.0 : temp[size/2];
    } else {
        hwResult = std::accumulate(homeworks.begin(), homeworks.end(), 0.0) / homeworks.size();
    }
    
    finalGrade = 0.4 * hwResult + 0.6 * exam;
}

// Overloaded >> (Input)
std::istream& operator>>(std::istream& in, Person& p) {
    in >> p.firstName >> p.lastName;
    int grade;
    p.homeworks.clear();
    // Logic depends on file structure, but for manual input:
    while (in >> grade && grade != -1) { // -1 to stop
        p.homeworks.push_back(grade);
    }
    in >> p.exam;
    return in;
}

// Overloaded << (Output)
std::ostream& operator<<(std::ostream& out, const Person& p) {
    out << std::left << std::setw(15) << p.firstName 
        << std::setw(15) << p.lastName 
        << std::fixed << std::setprecision(2) << p.finalGrade;
    return out;
}
