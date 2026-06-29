#ifndef LOAN_H
#define LOAN_H
#include <string>

using namespace std;

class Loan {
private: 
    int loanId;
    string clientName;
    double principal;
    double annualRate;
    int months;

public:
    Loan(int id, string nom, double cap, double tasa, int m);
    virtual ~Loan();

    int getLoanId();
    string getClientName();
    double getPrincipal();
    double getAnnualRate();
    int getMonths();

    void setPrincipal(double cap);
    void setAnnualRate(double tasa);

    virtual void printReceipt() = 0;
};
#endif