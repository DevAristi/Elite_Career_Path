#ifndef DOCTOR_H
#define DOCTOR_H

#include <iostream>
#include <string>

class Doctor {
private:  
    int licenseId;
    std::string name;
    bool isAvailable;

public:
    Doctor(std::string name, int licenseId);
    ~Doctor();
    std::string getName() const;
    int getLicenseId() const;
    bool bookAppointment();
};

#endif // DOCTOR_H