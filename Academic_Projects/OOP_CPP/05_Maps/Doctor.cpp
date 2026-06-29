#include "Doctor.h"

Doctor::Doctor(std::string name, int licenseId) {
    this->name = name;
    this->licenseId = licenseId;
    this->isAvailable = true;
}

Doctor::~Doctor() {
    std::cout << "Doctor " << name << " has been removed from the system." << std::endl;
}

std::string Doctor::getName() const {
    return name;
}

int Doctor::getLicenseId() const {
    return licenseId;
}

bool Doctor::bookAppointment() {
    if (isAvailable) {
        isAvailable = false;
        std::cout << "Appointment successfully registered." << std::endl;
        return true;
    } else {
        std::cout << "Doctor " << name << " is currently unavailable." << std::endl;
        return false;
    }
}