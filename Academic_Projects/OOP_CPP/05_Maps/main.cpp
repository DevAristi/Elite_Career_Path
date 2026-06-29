#include <iostream>
#include <string>
#include "MedicalClinic.h"

int main() {
    // Instantiating the clinic with standard local data
    MedicalClinic clinic("Av. Insurgentes Sur 1234, CDMX", 15000.0f);
    
    int option;
    std::string taxId, name;
    int licenseId;

    do {
        std::cout << "\n====================================" << std::endl;
        std::cout << "    CLINIC MANAGEMENT SYSTEM (MAPS)" << std::endl;
        std::cout << "====================================" << std::endl;
        std::cout << "1. Add Doctor" << std::endl;
        std::cout << "2. Remove Doctor" << std::endl;
        std::cout << "3. Display Registered Doctors" << std::endl;
        std::cout << "4. Book/Schedule Appointment" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Select an option: ";
        std::cin >> option;

        switch (option) {
            case 1: {
                std::cout << "\n--- REGISTER NEW DOCTOR ---" << std::endl;
                std::cout << "Enter Doctor's Tax ID (RFC): ";
                std::cin >> taxId;
                std::cin.ignore(50, '\n'); // Clears the buffer for getline
                
                std::cout << "Enter Full Name: ";
                std::getline(std::cin, name);
                
                std::cout << "Enter Professional License ID: ";
                std::cin >> licenseId;
                
                Doctor* newDoctor = new Doctor(name, licenseId);
                clinic.addDoctor(newDoctor, taxId);
                break;
            }
            case 2:
                std::cout << "\n--- REMOVE DOCTOR FROM SYSTEM ---" << std::endl;
                std::cout << "Enter Doctor's Tax ID (RFC) to discharge: ";
                std::cin >> taxId;
                clinic.removeDoctor(taxId);
                break;

            case 3:
                std::cout << "\n--- REGISTERED DOCTORS LIST ---" << std::endl;
                clinic.displayDoctors();
                break;

            case 4:
                std::cout << "\n--- APPOINTMENT ALLOCATION ---" << std::endl;
                clinic.scheduleAppointment();
                break;

            case 5:
                std::cout << "\nShutting down core system..." << std::endl;
                break;

            default:
                std::cout << "Invalid choice. Please select a valid option." << std::endl;
                break;
        }

    } while (option != 5);
    
    return 0;
}