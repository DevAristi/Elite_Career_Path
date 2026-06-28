#include "BankManager.h"
#include <iostream>

using namespace std;

BankManager::BankManager(string n) {
    bankName = n;
}

BankManager::~BankManager() {
    for(size_t i = 0; i < loanList.size(); i++) {
        delete loanList[i];
    }
    loanList.clear();
    loanMap.clear();
}

void BankManager::registerLoan(Loan* p) {
    int id = p->getLoanId();
    
    if (findLoanById(id) != nullptr) {
        cout << "Error: ID " << id << " is already registered.\n";
        delete p;
        return;
    }

    loanMap[id] = p;
    loanList.push_back(p);
}

Loan* BankManager::findLoanById(int id) {
    auto it = loanMap.find(id);
    if(it != loanMap.end()) {
        return it->second;
    }
    return nullptr;
}

void BankManager::modifyLoanPrincipal(int id, double newPrincipal) {
    Loan* p = findLoanById(id);
    if(p != nullptr) {
        p->setPrincipal(newPrincipal);
        cout << "Principal for ID " << id << " successfully modified.\n";
    } else {
        cout << "Loan not found.\n";
    }
}

bool BankManager::deleteLoan(int id) {
    auto itMap = loanMap.find(id);
    if (itMap != loanMap.end()) {
        Loan* p = itMap->second;
        loanMap.erase(itMap);

        for (auto itVec = loanList.begin(); itVec != loanList.end(); ++itVec) {
            if (*itVec == p) {
                loanList.erase(itVec);
                break;
            }
        }
        delete p;
        return true;
    }
    return false;
}

double BankManager::calculateTotalLoaned() {
    double total = 0;
    for(size_t i = 0; i < loanList.size(); i++) {
        total += loanList[i]->getPrincipal();
    }
    return total;
}

int BankManager::getLoanCount() {
    return loanList.size();
}

void BankManager::displayAllReceipts() {
    cout << "\n*** BANK RECEIPTS FROM: " << bankName << " ***\n";
    for(size_t i = 0; i < loanList.size(); i++) {
        loanList[i]->printReceipt();
    }
}