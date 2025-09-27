#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <limits>
#include <iomanip>

class BankAccount {
private:
    int accountNumber;
    std::string name;
    double balance;

public:
    BankAccount(int accNum, std::string holderName, double initialDeposit = 0.0) {
        this->accountNumber = accNum;
        this->name = holderName;
        this->balance = initialDeposit;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "Successfully deposited $" << std::fixed << std::setprecision(2) << amount
                      << ". New balance: $" << balance << std::endl;
        } else {
            std::cout << "Deposit amount must be positive." << std::endl;
        }
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            std::cout << "Withdrawal amount must be positive." << std::endl;
        } else if (balance >= amount) {
            balance -= amount;
            std::cout << "Successfully withdrew $" << std::fixed << std::setprecision(2) << amount
                      << ". New balance: $" << balance << std::endl;
        } else {
            std::cout << "Insufficient funds. Current balance: $" << std::fixed << std::setprecision(2) << balance << std::endl;
        }
    }

    void display() const {
        std::cout << "\n--- Account Details ---" << std::endl;
        std::cout << "Account Number: " << accountNumber << std::endl;
        std::cout << "Account Holder: " << name << std::endl;
        std::cout << "Balance: $" << std::fixed << std::setprecision(2) << balance << std::endl;
        std::cout << "-----------------------" << std::endl;
    }
};

class Bank {
private:
    std::map<int, BankAccount> accounts;
    int nextAccountNumber;

    // Helper to handle invalid numeric input
    double get_numeric_input(const std::string& prompt) {
        double value;
        while (true) {
            std::cout << prompt;
            std::cin >> value;
            if (std::cin.good()) {
                // Clear the rest of the line in case user entered extra characters
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }
            std::cout << "Invalid amount. Please enter a number." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

public:
    Bank() : nextAccountNumber(1001) {}

    void createAccount() {
        std::string name;
        std::cout << "Enter account holder's name: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer before getline
        std::getline(std::cin, name);

        double initialDeposit = get_numeric_input("Enter initial deposit amount: ");
        if (initialDeposit < 0) {
            std::cout << "Initial deposit cannot be negative." << std::endl;
            return;
        }

        accounts.emplace(nextAccountNumber, BankAccount(nextAccountNumber, name, initialDeposit));
        std::cout << "\nAccount created successfully! Your account number is: " << nextAccountNumber << std::endl;
        nextAccountNumber++;
    }

    BankAccount* findAccount() {
        int accNum;
        std::cout << "Enter account number: ";
        std::cin >> accNum;
        if (std::cin.fail()) {
            std::cout << "Invalid account number. Please enter digits only." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return nullptr;
        }
        
        auto it = accounts.find(accNum);
        if (it != accounts.end()) {
            return &it->second;
        }
        return nullptr;
    }

    void performDeposit() {
        BankAccount* account = findAccount();
        if (account) {
            double amount = get_numeric_input("Enter amount to deposit: ");
            account->deposit(amount);
        } else {
            std::cout << "Account not found." << std::endl;
        }
    }

    void performWithdrawal() {
        BankAccount* account = findAccount();
        if (account) {
            double amount = get_numeric_input("Enter amount to withdraw: ");
            account->withdraw(amount);
        } else {
            std::cout << "Account not found." << std::endl;
        }
    }

    void checkBalance() {
        BankAccount* account = findAccount();
        if (account) {
            account->display();
        } else {
            std::cout << "Account not found." << std::endl;
        }
    }

    void displayAllAccounts() {
        if (accounts.empty()) {
            std::cout << "No accounts in the bank." << std::endl;
            return;
        }
        std::cout << "\n--- All Bank Accounts ---" << std::endl;
        for (const auto& pair : accounts) {
            pair.second.display();
        }
    }
};

void showMenu() {
    std::cout << "\n===== Bank Management System =====" << std::endl;
    std::cout << "1. Create New Account" << std::endl;
    std::cout << "2. Deposit Amount" << std::endl;
    std::cout << "3. Withdraw Amount" << std::endl;
    std::cout << "4. Check Balance" << std::endl;
    std::cout << "5. Display All Accounts" << std::endl;
    std::cout << "6. Exit" << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << "Enter your choice (1-6): ";
}

int main() {
    Bank bank;
    char choice;

    do {
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case '1':
                bank.createAccount();
                break;
            case '2':
                bank.performDeposit();
                break;
            case '3':
                bank.performWithdrawal();
                break;
            case '4':
                bank.checkBalance();
                break;
            case '5':
                bank.displayAllAccounts();
                break;
            case '6':
                std::cout << "Thank you for using the Bank Management System. Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 6." << std::endl;
                // Clear potential bad input from the buffer
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
        }
    } while (choice != '6');

    return 0;
}