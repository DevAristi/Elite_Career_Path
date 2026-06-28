#include "Student.h"
#include <iostream>

void Student::display() {
    std::cout << "\n********************" << std::endl;
    std::cout << studentID << " - " << name << std::endl;
    std::cout << "DATE: " << day << "/" << month << std::endl;
    std::cout << "Grade: " << grade << std::endl;
    std::cout << "********************" << std::endl;
}