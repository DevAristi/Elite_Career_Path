#include "AutomotiveLoan.h"
#include "InterestCalculator.h"
#include <iostream>

using namespace std;

AutomotiveLoan::AutomotiveLoan(int id, string nom, double cap, double tasa, int m, string mod)
    : Loan(id, nom, cap, tasa, m) {
    carModel = mod;
}

AutomotiveLoan::~AutomotiveLoan() {}

string AutomotiveLoan::getCarModel() { return carModel; }

void AutomotiveLoan::printReceipt() {
    InterestCalculator calc;
    double total = calc.calculateTotal(getPrincipal(), getAnnualRate(), getMonths());

    cout << "\n===============================" << endl;
    cout << "   RECEIPT: AUTOMOTIVE LOAN" << endl;
    cout << "===============================" << endl;
    cout << "ID: " << getLoanId() << " | Client: " << getClientName() << endl;
    cout << "Car Model: " << carModel << endl;
    cout << "Principal: $" << getPrincipal() << endl;
    cout << "Rate: " << getAnnualRate() << "% | Term: " << getMonths() << " months" << endl;
    cout << "-------------------------------" << endl;
    cout << "TOTAL TO PAY: $" << total << endl;
    cout << "===============================" << endl;
}