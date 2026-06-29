#ifndef PERSONALLOAN_H
#define PERSONALLOAN_H
#include "Loan.h"
#include <string>

using namespace std;

class PersonalLoan : public Loan {
private:
    string purpose;

public:
    PersonalLoan(int id, string nom, double cap, double tasa, int m, string mot);
    ~PersonalLoan();
    void printReceipt() override;
};
#endif