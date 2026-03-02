#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <fstream>
#include <sstream>
#include <random>

class Person {
private:
    std::string name;
    std::string surname;
    std::vector<int> homework;
    int exam;
    double finalGrade;

public:
    // Constructor
    Person() : exam(0), finalGrade(0.0) {}

    // Copy Constructor (Rule of Three)
    Person(const Person& other)
        : name(other.name),
          surname(other.surname),
          homework(other.homework),
          exam(other.exam),
          finalGrade(other.finalGrade) {}

    // Assignment Operator (Rule of Three)
    Person& operator=(const Person& other) {
        if (this != &other) {
            name = other.name;
            surname = other.surname;
            homework = other.homework;
            exam = other.exam;
            finalGrade = other.finalGrade;
        }
        return *this;
    }

    // Destructor (Rule of Three)
    ~Person() {}

    void calculateFinalAverage() {
        double avg = std::accumulate(homework.begin(), homework.end(), 0.0)
                     / homework.size();
        finalGrade = 0.4 * avg + 0.6 * exam;
    }

    void calculateFinalMedian() {
        std::vector<int> temp = homework;
        std::sort(temp.begin(), temp.end());
        double median;

        if (temp.size() % 2 == 0)
            median = (temp[temp.size()/2 - 1] + temp[temp.size()/2]) / 2.0;
        else
            median = temp[temp.size()/2];

        finalGrade = 0.4 * median + 0.6 * exam;
    }

    double getFinal() const { return finalGrade; }
    std::string getName() const { return name; }
    std::string getSurname() const { return surname; }

    friend std::istream& operator>>(std::istream& in, Person& p);
    friend std::ostream& operator<<(std::ostream& out, const Person& p);
};

// Input operator
std::istream& operator>>(std::istream& in, Person& p) {
    p.homework.clear();
    std::cout << "Enter name and surname: ";
    in >> p.name >> p.surname;

    std::cout << "Enter homework grades (0 to stop): ";
    int grade;
    while (in >> grade && grade != 0) {
        p.homework.push_back(grade);
    }

    std::cout << "Enter exam grade: ";
    in >> p.exam;

    return in;
}

// Output operator
std::ostream& operator<<(std::ostream& out, const Person& p) {
    out << std::left << std::setw(12) << p.name
        << std::setw(15) << p.surname
        << std::fixed << std::setprecision(2)
        << std::setw(10) << p.finalGrade;
    return out;
}

void readFromFile(const std::string& filename, std::vector<Person>& students) {
    std::ifstream file(filename);
    std::string line;

    getline(file, line); // skip header

    while (getline(file, line)) {
        std::istringstream iss(line);
        Person p;
        iss >> p;
        students.push_back(p);
    }
}

int main() {
    std::vector<Person> students;
    int choice;

    std::cout << "1 - Manual input\n2 - File input\nChoice: ";
    std::cin >> choice;

    if (choice == 1) {
        Person p;
        std::cin >> p;
        students.push_back(p);
    } else {
        readFromFile("Students.txt", students);
    }

    std::cout << "Choose calculation method (1-Avg, 2-Median): ";
    int method;
    std::cin >> method;

    for (auto& s : students) {
        if (method == 1)
            s.calculateFinalAverage();
        else
            s.calculateFinalMedian();
    }

    std::sort(students.begin(), students.end(),
        [](const Person& a, const Person& b) {
            return a.getSurname() < b.getSurname();
        });

    std::cout << "\nName       Surname       Final\n";
    std::cout << "-----------------------------------\n";

    for (const auto& s : students)
        std::cout << s << "\n";

    return 0;
}
