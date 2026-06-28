#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

class Student {
public:
    // Attributes
    std::string studentID; 
    std::string name;      
    int day;               
    int month;             
    float grade;           

    // Method prototype
    void display();        
};

#endif