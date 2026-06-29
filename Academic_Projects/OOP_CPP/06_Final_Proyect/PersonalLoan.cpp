#include "PersonalLoan.h"
#include "InterestCalculator.h"
#include <iostream>

using namespace std;

PersonalLoan::PersonalLoan(int id, string nom, double cap, double tasa, int m, string mot)
    : Loan(id, nom, cap, tasa, m) {
    purpose = mot;
}

PersonalLoan::~PersonalLoan() {}

void PersonalLoan::printReceipt() {
    InterestCalculator calc;
    double total = calc.calculateTotal(getPrincipal(), getAnnualRate(), getMonths());

    cout << "\n===============================" << endl;
    cout << "     RECEIPT: PERSONAL LOAN" << endl;
    cout << "===============================" << endl;
    cout << "ID: " << getLoanId() << " | Client: " << getClientName() << endl;
    cout << "Purpose: " << purpose << endl;
    cout << "Principal: $" << getPrincipal() << endl;
    cout << "Rate: " << getAnnualRate() << "% | Term: " << getMonths() << " months" << endl;
    cout << "-------------------------------" << endl;
    cout << "TOTAL TO PAY: $" << total << endl;
    cout << "===============================" << endl;
}