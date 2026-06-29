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
    Doctor(std::string n, int c);
    ~Doctor();
    std::string getName() const;
    int getLicenseId() const;
    bool scheduleAppointment();
};

#endif // DOCTOR_H