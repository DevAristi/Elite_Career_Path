#include <iostream>
#include "MedicalClinic.h"

int main() {
    int option;
    std::string doctorName;
    int licenseId;
    
    // Instantiate clinic
    MedicalClinic clinic("Tlalpan 3050", 75000);

    do {
        std::cout << "\n--- CLINIC MANAGEMENT SYSTEM ---" << std::endl;
        std::cout << "1. Book an appointment" << std::endl;
        std::cout << "2. View address" << std::endl;
        std::cout << "3. View current rent" << std::endl;
        std::cout << "4. Update rent value" << std::endl;
        std::cout << "5. Register a new doctor" << std::endl;
        std::cout << "6. Display all doctors" << std::endl;
        std::cout << "7. Search doctor by name" << std::endl;
        std::cout << "8. Remove doctor from system" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Select an option: ";
        std::cin >> option;

        switch(option) {
            case 0: 
                std::cout << "Shutting down system..." << std::endl;
                break;
                
            case 1: 
                clinic.bookAppointment(); 
                break;
                
            case 2: 
                std::cout << "Clinic Address: " << clinic.getAddress() << std::endl; 
                break;
                
            case 3: 
                std::cout << "Current Rent: $" << clinic.getRent() << std::endl; 
                break;
                
            case 4: {
                float newRent;
                std::cout << "Enter new rent amount: ";
                std::cin >> newRent;
                clinic.setRent(newRent);
                break;
            }
            
            case 5:
                std::cout << "Enter new doctor's name: ";
                std::cin >> doctorName;
                std::cout << "Enter professional license ID: ";
                std::cin >> licenseId;
                clinic.registerDoctor(doctorName, licenseId);
                std::cout << "Doctor successfully registered." << std::endl;
                break;
                
            case 6: 
                std::cout << clinic.displayDoctors() << std::endl;
                break;
                
            case 7: {
                std::cout << "Enter doctor's name to search: ";
                std::cin >> doctorName;
                Doctor* foundDoctor = clinic.findDoctor(doctorName);
                if (foundDoctor != nullptr) {
                    std::cout << "Doctor found! Dr. " << foundDoctor->getName() 
                              << " - License ID: " << foundDoctor->getLicenseId() << std::endl;
                } else {
                    std::cout << "No record found for Dr. '" << doctorName << "'." << std::endl;
                }
                break;
            }
                
            case 8: {
                std::cout << "Enter doctor's name to remove: ";
                std::cin >> doctorName;
                if (clinic.removeDoctor(doctorName)) {
                    std::cout << "Doctor has been safely wiped from the database." << std::endl;
                } else {
                    std::cout << "Operation failed: Dr. '" << doctorName << "' does not exist." << std::endl;
                }
                break;
            }
                
            default: 
                std::cout << "Invalid selection. Try again.\n";
        }
    } while(option != 0);

    return 0;
}