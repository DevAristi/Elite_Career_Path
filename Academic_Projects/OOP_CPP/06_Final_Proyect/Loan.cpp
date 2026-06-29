#include "Loan.h"
#include "InterestCalculator.h"
#include <iostream>

using namespace std;

Loan::Loan(int id, string nom, double cap, double tasa, int m) {
    loanId = id;
    clientName = nom;
    setPrincipal(cap);
    setAnnualRate(tasa);
    months = (m <= 0) ? 1 : m;
}

Loan::~Loan() {}

int Loan::getLoanId() { return loanId; }
string Loan::getClientName() { return clientName; }
double Loan::getPrincipal() { return principal; }
double Loan::getAnnualRate() { return annualRate; }
int Loan::getMonths() { return months; }

void Loan::setPrincipal(double cap) {
    principal = (cap < 1000.0) ? 1000.0 : cap;
}

void Loan::setAnnualRate(double tasa) {
    annualRate = (tasa >= 45.0) ? 44.0 : tasa;
}