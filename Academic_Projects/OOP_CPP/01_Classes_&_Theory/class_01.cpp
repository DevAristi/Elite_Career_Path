/* UVM OOP (Object-Oriented Programming)
SEBASTIAN ARISTI 2026
BASICS OF A PROGRAM
*/
#include <iostream>
#include <cmath>
using namespace std; // To avoid putting "std::" in every line of code.

int main()
{
    // Numeric information ;)
    // Integers
    int integer_num;
    // Double precision reals
    double double_precision;
    // Symbol (only 1) - character       
    char initial;
    // String of characters
    string name; 
    // Single precision reals
    float base, height, area; 
    
    cout << "\nHello! What is your name? ";
    cin >> name;
    
    cout << "Let's calculate the area of a rectangle.\n";
    cout << "Enter the length of the base: ";
    cin >> base;
    
    cout << "Enter the height: ";
    cin >> height;
    
    area = base * height;
    
    // Here is the magic space and comma applied perfectly
    cout << name << ", the area of your rectangle is: " << area << "\n";
    
    return 0;
}
