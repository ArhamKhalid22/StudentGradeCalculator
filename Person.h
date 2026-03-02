#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Person {
private:
    std::string firstName;
    std::string lastName;
    std::vector<int> homeworks;
    int exam;
    double finalGrade;

public:
    // --- Constructors ---
    Person(); // Default constructor
    Person(std::string f, std::string l, std::vector<int> h, int e);

    // --- The Rule of Three ---
    ~Person();                                 // 1. Destructor
    Person(const Person& other);                // 2. Copy Constructor
    Person& operator=(const Person& other);     // 3. Copy Assignment Operator

    // --- Grading Methods ---
    void calculateFinal(bool useMedian);
    double getFinal() const { return finalGrade; }
    
    // --- Getters for Sorting ---
    std::string getFirstName() const { return firstName; }
    std::string getLastName() const { return lastName; }

    // --- Overloaded Operators (Input/Output) ---
    // These allow you to do: cin >> student; or cout << student;
    friend std::istream& operator>>(std::istream& in, Person& p);
    friend std::ostream& operator<<(std::ostream& out, const Person& p);
};

#endif
