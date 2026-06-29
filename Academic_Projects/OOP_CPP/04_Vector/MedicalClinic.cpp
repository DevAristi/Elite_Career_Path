#include "MedicalClinic.h"

MedicalClinic::MedicalClinic(std::string address, float rent) {
    this->address = address;
    this->rent = rent;
    std::cout << "Medical Clinic at " << address << " successfully created." << std::endl;
    
    // Default system doctor
    Doctor* defaultDoc = new Doctor("Chapatin", 1);
    doctors.push_back(defaultDoc);
}

MedicalClinic::~MedicalClinic() {
    // Clear dynamic memory allocation
    for (Doctor* doc : doctors) {
        delete doc; 
    } 
    std::cout << "Medical Clinic permanently closed." << std::endl;
}

std::string MedicalClinic::getAddress() const {
    return address;
}

float MedicalClinic::getRent() const {
    return rent;
}

void MedicalClinic::setRent(float r) {
    if (r > 0) {
        rent = r;
    }
}

bool MedicalClinic::bookAppointment() {
    bool hasAppointmentBeenMade = false;
    for (Doctor* doc : doctors) {
        if (doc->scheduleAppointment()) {
            std::cout << "Appointment set with Dr. " << doc->getName() << std::endl;
            hasAppointmentBeenMade = true;
            break;
        }
    }
    return hasAppointmentBeenMade;
}

void MedicalClinic::registerDoctor(const std::string& name, int licenseId) {
    Doctor* newDoc = new Doctor(name, licenseId);
    doctors.push_back(newDoc);
}

std::string MedicalClinic::displayDoctors() const {
    std::string listStr = "\n****** Clinic Doctors List ****";
    for (Doctor* doc : doctors) {
        listStr += "\nDr. " + doc->getName() + " (License ID: " + std::to_string(doc->getLicenseId()) + ")\n";
    }
    return listStr;
}

Doctor* MedicalClinic::findDoctor(const std::string& name) const {
    for (Doctor* doc : doctors) {
        if (doc->getName() == name) {
            return doc;
        }
    }
    return nullptr;
}

bool MedicalClinic::removeDoctor(const std::string& name) {
    for (size_t i = 0; i < doctors.size(); i++) {
        if (doctors[i]->getName() == name) {
            delete doctors[i]; // Avoid memory leaks
            doctors.erase(doctors.begin() + i);
            return true;
        }
    }
    return false;
}