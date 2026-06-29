#ifndef MEDICAL_CLINIC_H
#define MEDICAL_CLINIC_H

#include <iostream>
#include <string>
#include <map>
#include "Doctor.h"

class MedicalClinic {
public:
    MedicalClinic(std::string address, float rent);
    ~MedicalClinic();
    std::string getAddress() const;
    float getRent() const;
    void setRent(float rent);
    void scheduleAppointment();
    void addDoctor(Doctor* doctor, std::string taxId);
    void removeDoctor(std::string taxId);
    void displayDoctors() const;
    Doctor* findDoctor(std::string taxId) const;

private:
    std::string address;
    float rent;
    // Map tracking: Key (taxId/RFC) -> Value (Doctor pointer)
    std::map<std::string, Doctor*> employees;
};

#endif // MEDICAL_CLINIC_H