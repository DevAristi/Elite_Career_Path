#ifndef MEDICAL_CLINIC_H
#define MEDICAL_CLINIC_H

#include <iostream>
#include <string>
#include <vector>
#include "Doctor.h"

class MedicalClinic {
public:
    MedicalClinic(std::string address, float rent);
    ~MedicalClinic();
    std::string getAddress() const;
    float getRent() const;
    void setRent(float r);
    bool bookAppointment();
    void registerDoctor(const std::string& name, int licenseId);
    std::string displayDoctors() const;
    Doctor* findDoctor(const std::string& name) const;
    bool removeDoctor(const std::string& name);

private:
    std::string address;
    float rent;
    std::vector<Doctor*> doctors;
};

#endif // MEDICAL_CLINIC_H