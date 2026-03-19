#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <stdexcept>

class Student {
private:
    std::string name;
    std::string surname;
    std::vector<int> homeworks;
    int exam;
    double finalPoint;

public:
    Student();
    Student(std::string n, std::string s, std::vector<int> hw, int e);
    
    // Getters
    std::string getName() const { return name; }
    std::string getSurname() const { return surname; }
    double getFinalPoint() const { return finalPoint; }

    // Setters
    void setName(const std::string& n) { name = n; }
    void setSurname(const std::string& s) { surname = s; }
    void setHomeworks(const std::vector<int>& hw) { homeworks = hw; }
    void setExam(int e) { exam = e; }

    void calculateFinal(bool useMedian = false);
    
    // I/O
    friend std::ostream& operator<<(std::ostream& os, const Student& s);
    friend std::istream& operator>>(std::istream& is, Student& s);
};

#endif
