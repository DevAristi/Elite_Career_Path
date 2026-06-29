#include <iostream>
#include <string>
#include "BankManager.h"
#include "PersonalLoan.h"
#include "AutomotiveLoan.h"
#include <iomanip>

using namespace std;

int main() {
    BankManager myBank("Central Bank");
    int option = 0;
    cout << fixed << setprecision(4);

    do {
        cout << "\n========== BANK MENU ==========\n";
        cout << "1. Register Personal Loan\n";
        cout << "2. Register Automotive Loan\n";
        cout << "3. Find Loan by ID\n";
        cout << "4. Modify Loan Principal\n";
        cout << "5. Delete a Loan\n";
        cout << "6. Display All Receipts\n";
        cout << "7. View Statistics (Total & Count)\n";
        cout << "8. Exit\n";
        cout << "Select an option: ";
        cin >> option;

        switch(option) {
            case 1: {
                int id, months;
                double principal, rate;
                string name, purpose;
                
                cout << "\n--- NEW PERSONAL LOAN ---\n";
                cout << "Loan ID: "; cin >> id;
                cout << "Client Name: "; cin.ignore(); getline(cin, name);
                cout << "Principal $: "; cin >> principal;
                cout << "Annual Rate %: "; cin >> rate;
                cout << "Term (months): "; cin >> months;
                cout << "Loan Purpose: "; cin.ignore(); getline(cin, purpose);

                PersonalLoan* p1 = new PersonalLoan(id, name, principal, rate, months, purpose);
                myBank.registerLoan(p1);
                cout << "Loan successfully registered.\n";
                break;
            }
            case 2: {
                int id, months;
                double principal, rate;
                string name, carModel;
                
                cout << "\n--- NEW AUTOMOTIVE LOAN ---\n";
                cout << "Loan ID: "; cin >> id;
                cout << "Client Name: "; cin.ignore(); getline(cin, name);
                cout << "Principal $: "; cin >> principal;
                cout << "Annual Rate %: "; cin >> rate;
                cout << "Term (months): "; cin >> months;
                cout << "Car Model: "; cin.ignore(); getline(cin, carModel);

                AutomotiveLoan* p2 = new AutomotiveLoan(id, name, principal, rate, months, carModel);
                myBank.registerLoan(p2);
                cout << "Loan successfully registered.\n";
                break;
            }
            case 3: {
                int idToFind;
                cout << "\nEnter ID to find: "; cin >> idToFind;
                Loan* found = myBank.findLoanById(idToFind);
                if(found != nullptr) {
                    found->printReceipt();
                } else {
                    cout << "Error: No loan exists with ID " << idToFind << ".\n";
                }
                break;
            }
            case 4: {
                int idMod;
                double newPrincipal;
                cout << "\nEnter Loan ID to modify: "; cin >> idMod;
                cout << "Enter new principal $: "; cin >> newPrincipal;
                myBank.modifyLoanPrincipal(idMod, newPrincipal);
                break;
            }
            case 5: {
                int idToDelete;
                cout << "\nEnter Loan ID to delete: "; cin >> idToDelete;
                if(myBank.deleteLoan(idToDelete)) {
                    cout << "Loan successfully deleted from the system.\n";
                } else {
                    cout << "Error: Loan not found for deletion.\n";
                }
                break;
            }
            case 6: {
                myBank.displayAllReceipts();
                break;
            }
            case 7: {
                cout << "\n--- BANK STATISTICS ---\n";
                cout << "Active Loans Count: " << myBank.getLoanCount() << endl;
                cout << "Total Capital Loaned: $" << myBank.calculateTotalLoaned() << endl;
                break;
            }
            case 8: {
                cout << "\nExiting banking system...\n";
                break;
            }
            default: {
                cout << "\nInvalid option. Please try again.\n";
                break;
            }
        }
    } while (option != 8);

    return 0;
}