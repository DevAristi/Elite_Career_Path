#include "MedicalClinic.h"

MedicalClinic::MedicalClinic(std::string address, float rent) {
    this->address = address;
    this->rent = rent;
}

MedicalClinic::~MedicalClinic() {
    // Correct loop using modern C++ structured binding for cleaner syntax
    for (auto const& [taxId, doctorPtr] : employees) {
        delete doctorPtr;
    }
    std::cout << "Medical Clinic permanently closed." << std::endl;
}

std::string MedicalClinic::getAddress() const {
    return address;
}

float MedicalClinic::getRent() const {
    return rent;
}

void MedicalClinic::setRent(float rent) {
    if (rent > 0) {
        this->rent = rent;
    }
}

void MedicalClinic::scheduleAppointment() {
    std::map<std::string, Doctor*>::iterator it;
    for (it = employees.begin(); it != employees.end(); it++) {
        if (it->second->bookAppointment()) {
            std::cout << "Appointment set with Dr. " << it->second->getName() << std::endl;
            std::cout << "Tax ID (RFC): " << it->first << std::endl;
            break;
        }
    }
    if (it == employees.end()) {
        std::cout << "No available appointments found." << std::endl;
    }
}

void MedicalClinic::addDoctor(Doctor* doctor, std::string taxId) {
    if (doctor != nullptr && employees.find(taxId) == employees.end()) {
        employees[taxId] = doctor;
        std::cout << "Doctor " << doctor->getName() << " successfully registered." << std::endl;
    } else {
        std::cout << "Error: Doctor already exists or invalid pointer." << std::endl;
    }
}

void MedicalClinic::removeDoctor(std::string taxId) {
    auto it = employees.find(taxId);
    if (it != employees.end()) {
        delete it->second; // Free allocated memory to avoid leaks
        employees.erase(it);
        std::cout << "Doctor with Tax ID " << taxId << " has been removed." << std::endl;
    } else {
        std::cout << "Error: Doctor with Tax ID " << taxId << " not found." << std::endl;
    }
}

void MedicalClinic::displayDoctors() const {
    for (auto const& [taxId, doctorPtr] : employees) {
        std::cout << "\n********* Doctor Tax ID: " << taxId << " *********" << std::endl;
        std::cout << "Name: " << doctorPtr->getName() << std::endl;
        std::cout << "License ID: " << doctorPtr->getLicenseId() << std::endl;
    }
}

Doctor* MedicalClinic::findDoctor(std::string taxId) const {
    auto it = employees.find(taxId);
    if (it != employees.end()) {
        return it->second;
    }
    return nullptr; 
}
