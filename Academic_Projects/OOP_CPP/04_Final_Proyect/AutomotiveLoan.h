#ifndef AUTOMOTIVELOAN_H
#define AUTOMOTIVELOAN_H
#include "Loan.h"
#include <string>

using namespace std;

class AutomotiveLoan : public Loan {
private:
    string carModel;

public:
    AutomotiveLoan(int id, string nom, double cap, double tasa, int m, string mod);
    ~AutomotiveLoan();
    void printReceipt() override;
    string getCarModel();
};
#endif