#ifndef BANKMANAGER_H
#define BANKMANAGER_H
#include <string>
#include <vector>
#include <map>
#include "Loan.h"

using namespace std;

class BankManager {
private:
    string bankName;
    vector<Loan*> loanList;
    map<int, Loan*> loanMap;

public:
    BankManager(string n);
    ~BankManager();

    void registerLoan(Loan* p);
    Loan* findLoanById(int id);
    void modifyLoanPrincipal(int id, double newPrincipal);
    bool deleteLoan(int id);
    double calculateTotalLoaned();
    int getLoanCount();
    void displayAllReceipts();
};
#endif