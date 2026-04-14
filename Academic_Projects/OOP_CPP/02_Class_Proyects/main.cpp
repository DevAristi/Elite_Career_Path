/* UVM ProgOO 
   Modeling the Student class 
*/
#include <iostream>
#include "Student.h"

using namespace std;

int main() {
    // Creating objects
    Student x, y, z;

    // Hardcoded data for Student X
    x.studentID = "A01";
    x.name = "Sebastian Aristi";
    x.day = 23;
    x.month = 2;
    x.grade = 10.5;

    cout << "Hello" << endl;
    x.display(); // Showing student x data

    // User input for Student Y
    cout << "Enter Student ID: ";
    cin >> y.studentID;

    cout << "Enter Name: ";
    cin >> y.name;

    cout << "Enter Day of the Month: ";
    cin >> y.day;

    cout << "Enter Month: ";
    cin >> y.month;

    cout << "Enter Grade: ";
    cin >> y.grade;

    // Showing student and data
    y.display();

    return 0;
}