#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

#define MAX 100

int accountCount = 0; 

class Account
{
private:
    int accountNumber;
    string username;
    string password;
    string accountHolderName;
    double accountBalance; 

public:
    Account()
    {
        accountNumber = 0;
        username = "";
        password = "";
        accountHolderName = "";
        accountBalance = 0.0;
    }

    // ---- Account creation -------------------------------------------------
    void createAccount(int accountsExisting, Account accounts[])
    {
        cout << "Enter the account number: ";
        cin >> accountNumber;

        bool duplicate = true;
        while (duplicate)
        {
            duplicate = false;
            for (int i = 0; i < accountsExisting; i++)
            {
                if (accounts[i].accountNumber == accountNumber)
                {
                    duplicate = true;
                    break;
                }
            }
            if (duplicate)
            {
                cout << "That account number is already in use. Enter a different one: ";
                cin >> accountNumber;
            }
        }

        cout << "Enter a username for this account: ";
        cin >> username;
        cout << "Enter a password for this account: ";
        cin >> password;
        cout << "Enter the account holder name: ";
        cin.ignore();
        getline(cin, accountHolderName);

        do
        {
            cout << "Enter the opening balance: ";
            cin >> accountBalance;
            if (accountBalance < 0)
                cout << "Opening balance cannot be negative." << endl;
        } while (accountBalance < 0);

        cout << endl;
    }

    void displayAccounts() const
    {
        cout << "Account Number      : " << accountNumber << endl;
        cout << "Account Holder Name : " << accountHolderName << endl;
        cout << "Username            : " << username << endl;
        cout << "Balance             : " << fixed << setprecision(2) << accountBalance << endl;
    }

    // ---- Login (used by the customer menu) --------------------------------
    bool login(const string& uname, const string& pass) const
    {
        return (uname == username && pass == password);
    }

    // ---- Money operations ---------------------------------------------------
    void deposit(double amount)
    {
        if (amount > 0)
        {
            accountBalance += amount;
            cout << "Amount deposited successfully. New balance: " << fixed << setprecision(2) << accountBalance << endl;
        }
        else
        {
            cout << "Invalid amount. Deposit must be greater than zero." << endl;
        }
    }

    void withdraw(double amount)
    {
        if (amount > 0 && amount <= accountBalance)
        {
            accountBalance -= amount;
            cout << "Amount withdrawn successfully. New balance: " << fixed << setprecision(2) << accountBalance << endl;
        }
        else
        {
            cout << "Invalid amount or insufficient balance." << endl;
        }
    }

    // ---- Getters / setters --------------------------------------------------
    int getAccountNumber() const { return accountNumber; }
    string getAccountHolderName() const { return accountHolderName; }
    double getBalance() const { return accountBalance; }

    void setAccountNumber(int n) { accountNumber = n; }
    void setAccountHolderName(const string& s) { accountHolderName = s; }

    void addToBalance(double amt) { accountBalance += amt; }       // used internally by transfer
    void subtractFromBalance(double amt) { accountBalance -= amt; } // used internally by transfer

    // ---- Admin operations on the whole array --------------------------------
    void updateInfo(Account accounts[])
    {
        int accNumber, choice = 0;
        bool found = false;

        do
        {
            cout << "Enter the account number whose information you want to change (-1 to cancel): ";
            cin >> accNumber;

            if (accNumber == -1) return; 

            found = false;

            for (int i = 0; i < accountCount; i++)
            {
                if (accounts[i].accountNumber == accNumber)
                {
                    found = true;

                    do
                    {
                        cout << "\n1. Change account number." << endl;
                        cout << "2. Change account holder name." << endl;
                        cout << "3. Exit." << endl;
                        cout << "\nEnter the choice: ";
                        cin >> choice;

                        if (choice == 1)
                        {
                            int newNum;
                            cout << "Enter the new account number: ";
                            cin >> newNum;

                            bool taken = false;
                            for (int j = 0; j < accountCount; j++)
                            {
                                if (j != i && accounts[j].accountNumber == newNum)
                                {
                                    taken = true;
                                    break;
                                }
                            }
                            if (taken)
                                cout << "That account number is already in use.\n";
                            else
                                accounts[i].accountNumber = newNum;
                        }
                        else if (choice == 2)
                        {
                            cout << "Enter the new account holder name: ";
                            cin.ignore();
                            getline(cin, accounts[i].accountHolderName);
                        }
                        else if (choice == 3)
                        {
                            cout << "Exiting update menu.\n";
                        }
                        else
                        {
                            cout << "Invalid choice. Try again.\n";
                        }

                    } while (choice != 3);

                    break;
                }
            }

            if (!found)
            {
                cout << "Account number not found. Try again.\n";
            }

        } while (!found);
    }

    void deleteAccount(Account accounts[])
    {
        int accNumber;
        bool found = false;

        cout << "Enter the account number you want to delete: ";
        cin >> accNumber;

        for (int i = 0; i < accountCount; i++)
        {
            if (accounts[i].accountNumber == accNumber)
            {
                found = true;

                for (int j = i; j < accountCount - 1; j++)
                {
                    accounts[j] = accounts[j + 1];
                }

                accountCount--;
                cout << "Account deleted successfully." << endl;
                break; 
            }
        }

        if (!found)
        {
            cout << "Account number not found. Try again.\n";
        }
    }

    void searchAccount(Account accounts[])
    {
        int accNumber, choice;
        string accHolderName;
        bool found = false;

        do
        {
            found = false;
            cout << "\n1. Search by account number." << endl;
            cout << "2. Search by account holder name." << endl;
            cout << "3. Exit." << endl;
            cout << "\nEnter the choice: ";
            cin >> choice;

            if (choice == 1)
            {
                cout << "Enter the account number: ";
                cin >> accNumber;

                for (int i = 0; i < accountCount; i++)
                {
                    if (accounts[i].accountNumber == accNumber)
                    {
                        found = true;
                        accounts[i].displayAccounts();
                        break;
                    }
                }

                if (!found) cout << "Account not found.\n";
            }
            else if (choice == 2)
            {
                cout << "Enter the account holder name: ";
                cin.ignore();
                getline(cin, accHolderName);

                bool any = false; 
                for (int i = 0; i < accountCount; i++)
                {
                    if (accounts[i].accountHolderName == accHolderName)
                    {
                        any = true;
                        accounts[i].displayAccounts();
                        cout << "---" << endl;
                    }
                }

                if (!any) cout << "Account not found.\n";
            }
            else if (choice != 3)
            {
                cout << "Invalid choice.\n";
            }

        } while (choice != 3);
    }

    void moneyTransfer(Account accounts[])
    {
        int accNumber1, accNumber2;
        double amount;
        int index1 = -1, index2 = -1;

        while (true)
        {
            cout << "Enter the account number from which you want to transfer money: ";
            cin >> accNumber1;

            for (int i = 0; i < accountCount; i++)
            {
                if (accounts[i].accountNumber == accNumber1)
                {
                    index1 = i;
                    break;
                }
            }

            if (index1 != -1) break;
            cout << "Source account not found. Please try again.\n";
        }

        while (true)
        {
            cout << "Enter the account number to which you want to transfer money: ";
            cin >> accNumber2;

            if (accNumber2 == accNumber1)
            {
                cout << "Source and destination accounts cannot be the same.\n";
                continue;
            }

            for (int i = 0; i < accountCount; i++)
            {
                if (accounts[i].accountNumber == accNumber2)
                {
                    index2 = i;
                    break;
                }
            }

            if (index2 != -1) break;
            cout << "Destination account not found. Please try again.\n";
        }

        do
        {
            cout << "Enter the amount which you want to transfer: ";
            cin >> amount;
            if (amount <= 0)
                cout << "Transfer amount must be greater than zero." << endl;
        } while (amount <= 0);

        if (amount <= accounts[index1].getBalance())
        {
            accounts[index1].subtractFromBalance(amount);
            accounts[index2].addToBalance(amount);
            cout << "Amount has been transferred successfully.\n";
        }
        else
        {
            cout << "Insufficient balance. Transfer failed.\n";
        }
    }
};


class Loan
{
private:
    int loanId;
    int accountNumber;
    double amount;
    double interestRate;
    int durationMonths;

public:
    
    bool createLoan(Account accounts[], int accountsExisting)
    {
        cout << "\nEnter Loan ID: ";
        cin >> loanId;

        bool accountExists = false;
        do
        {
            cout << "Enter Account Number: ";
            cin >> accountNumber;

            for (int i = 0; i < accountsExisting; i++)
            {
                if (accounts[i].getAccountNumber() == accountNumber)
                {
                    accountExists = true;
                    break;
                }
            }

            if (!accountExists)
                cout << "No account exists with that number. Try again.\n";

        } while (!accountExists);

        do
        {
            cout << "Enter Loan Amount: ";
            cin >> amount;
            if (amount <= 0) cout << "Loan amount must be greater than zero." << endl;
        } while (amount <= 0);

        do
        {
            cout << "Enter Interest Rate (%): ";
            cin >> interestRate;
            if (interestRate < 0) cout << "Interest rate cannot be negative." << endl;
        } while (interestRate < 0);

        do
        {
            cout << "Enter Duration (months): ";
            cin >> durationMonths;
            if (durationMonths <= 0) cout << "Duration must be greater than zero." << endl;
        } while (durationMonths <= 0);

        return true;
    }

    void displayLoan() const
    {
        cout << "\nLoan ID: " << loanId
             << "\nAccount Number: " << accountNumber
             << "\nAmount: " << amount
             << "\nInterest Rate: " << interestRate
             << "\nDuration: " << durationMonths << " months\n";
    }

    int getAccountNumber() const { return accountNumber; }
    int getLoanId() const { return loanId; }
};

class LoanManager
{
private:
    Loan loans[MAX];
    int loanCount = 0;

public:
    void addLoan(Account accounts[], int accountsExisting)
    {
        if (loanCount < MAX)
        {
            if (loans[loanCount].createLoan(accounts, accountsExisting))
            {
                loanCount++;
                cout << "Loan added successfully.\n";
            }
        }
        else
        {
            cout << "Loan limit reached!\n";
        }
    }

    void displayAllLoans() const
    {
        if (loanCount == 0)
            cout << "No loans to display.\n";
        else
            for (int i = 0; i < loanCount; i++)
                loans[i].displayLoan();
    }

    void searchLoanByAccountNumber() const
    {
        int accNum;
        bool found = false;

        cout << "Enter account number to search loans: ";
        cin >> accNum;

        for (int i = 0; i < loanCount; i++)
        {
            if (loans[i].getAccountNumber() == accNum)
            {
                loans[i].displayLoan();
                found = true;
            }
        }

        if (!found) cout << "No loan found for this account.\n";
    }
};

bool adminLogin()
{
    const string ADMIN_USER = "admin";
    const string ADMIN_PASS = "admin1235";

    string uname, pass;
    cout << "Enter Admin Username: ";
    cin >> uname;
    cout << "Enter Admin Password: ";
    cin >> pass;

    if (uname == ADMIN_USER && pass == ADMIN_PASS)
    {
        cout << "Admin Login Successful!" << endl;
        return true;
    }
    cout << "Admin Login Failed!" << endl;
    return false;
}

int customerLogin(Account accounts[])
{
    string uname, pass;
    cout << "Enter Customer Username: ";
    cin >> uname;
    cout << "Enter Customer Password: ";
    cin >> pass;

    for (int i = 0; i < accountCount; i++)
    {
        if (accounts[i].login(uname, pass))
        {
            cout << "Customer Login Successful!" << endl;
            return i;
        }
    }

    cout << "Invalid customer credentials." << endl;
    return -1;
}

void customerMenu(Account& acc)
{
    int option;
    do
    {
        cout << "\nCustomer Menu:" << endl;
        cout << "1. View Balance" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. Logout" << endl;
        cout << "Choose option: ";
        cin >> option;

        if (option == 1)
        {
            cout << "Your current balance is: " << fixed << setprecision(2) << acc.getBalance() << endl;
        }
        else if (option == 2)
        {
            double amount;
            cout << "Enter the amount you want to deposit: ";
            cin >> amount;
            acc.deposit(amount);
        }
        else if (option == 3)
        {
            double amount;
            cout << "Enter the amount you want to withdraw: ";
            cin >> amount;
            acc.withdraw(amount);
        }
        else if (option == 4)
        {
            cout << "Logging out..." << endl;
        }
        else
        {
            cout << "Invalid option." << endl;
        }

    } while (option != 4);
}

void adminMenu(Account accounts[], LoanManager& loanManager)
{
    Account helper; 
    int choice;

    do
    {
        cout << "\nAdmin Menu:\n";
        cout << "1. Create Account\n";
        cout << "2. Display Accounts\n";
        cout << "3. Update Information\n";
        cout << "4. Delete Account\n";
        cout << "5. Search Account\n";
        cout << "6. Money Transfer\n";
        cout << "7. Loan Management\n";
        cout << "8. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            if (accountCount >= MAX)
            {
                cout << "Cannot create more accounts. Limit reached.\n";
            }
            else
            {
                accounts[accountCount].createAccount(accountCount, accounts);
                accountCount++;
                cout << "Account created successfully.\n";
            }
        }
        else if (choice == 2)
        {
            if (accountCount == 0)
                cout << "No accounts to display.\n";
            for (int i = 0; i < accountCount; i++)
            {
                accounts[i].displayAccounts();
                cout << "---" << endl;
            }
        }
        else if (choice == 3)
        {
            if (accountCount == 0) cout << "No accounts exist yet.\n";
            else helper.updateInfo(accounts);
        }
        else if (choice == 4)
        {
            if (accountCount == 0) cout << "No accounts exist yet.\n";
            else helper.deleteAccount(accounts);
        }
        else if (choice == 5)
        {
            if (accountCount == 0) cout << "No accounts exist yet.\n";
            else helper.searchAccount(accounts);
        }
        else if (choice == 6)
        {
            if (accountCount < 2) cout << "Need at least two accounts to transfer between.\n";
            else helper.moneyTransfer(accounts);
        }
        else if (choice == 7)
        {
            int loanChoice;
            do
            {
                cout << "\nLoan Management Menu:\n";
                cout << "1. Add Loan\n";
                cout << "2. Display All Loans\n";
                cout << "3. Search Loan by Account Number\n";
                cout << "4. Exit Loan Management\n";
                cout << "Enter choice: ";
                cin >> loanChoice;

                if (loanChoice == 1)
                {
                    if (accountCount == 0)
                        cout << "No accounts exist yet. Create an account before issuing a loan.\n";
                    else
                        loanManager.addLoan(accounts, accountCount);
                }
                else if (loanChoice == 2)
                {
                    loanManager.displayAllLoans();
                }
                else if (loanChoice == 3)
                {
                    loanManager.searchLoanByAccountNumber();
                }
                else if (loanChoice != 4)
                {
                    cout << "Invalid choice.\n";
                }

            } while (loanChoice != 4);
        }
        else if (choice != 8)
        {
            cout << "Invalid choice.\n";
        }

    } while (choice != 8);
}

void customerSection(Account accounts[])
{
    int idx = customerLogin(accounts);
    if (idx != -1)
    {
        customerMenu(accounts[idx]);
    }
}

int main()
{
    Account accounts[MAX];
    LoanManager loanManager;
    int mainChoice;

    do
    {
        cout << "\nMain Menu:\n";
        cout << "1. Admin\n";
        cout << "2. Customer\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> mainChoice;

        if (mainChoice == 1)
        {
            if (adminLogin())
            {
                adminMenu(accounts, loanManager);
            }
        }
        else if (mainChoice == 2)
        {
            customerSection(accounts);
        }
        else if (mainChoice == 3)
        {
            cout << "Exiting program." << endl;
        }
        else
        {
            cout << "Invalid option. Try again." << endl;
        }

    } while (mainChoice != 3);

    return 0;
}
