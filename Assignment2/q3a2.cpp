#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Transaction {
    int transactionId;
    double transactionAmount;
    struct Transaction* next;
} * start = NULL;

void insertTransaction(int id, double amount) {
    struct Transaction* temp = new Transaction;
    temp->transactionId = id;
    temp->transactionAmount = amount;
    temp->next = NULL;
    if (start == NULL) {
        start = temp;
    }
    else {
        struct Transaction* current = start;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = temp;
    }
}

void deleteTransaction(int transactionId) {
    struct Transaction* current = start;
    struct Transaction* prev = NULL;

    while (current != NULL) {
        if (transactionId == current->transactionId) {
            if (prev == NULL) {
                // If the matching transaction is the first node
                start = current->next;
            }
            else {
                prev->next = current->next;
            }
            delete current;
            cout << "Transaction ID " << transactionId << " has been deleted.\n";
            return;
        }
        prev = current;
        current = current->next;
    }
    cout << "Transaction ID " << transactionId << " not found.\n";
}

void printTransaction() {
    struct Transaction* current = start;
    if (current == NULL) {
        cout << "Transaction List is empty.\n";
    }
    else {
        while (current != NULL) {
            cout << "Transaction ID: " << current->transactionId << "\nTransaction Amount: " << current->transactionAmount << "\n";
            current = current->next;
        }
    }
}

int main() {
    ifstream inputFile("E:/university/c++/Assignment2/TestCases/03/Test03.txt");
    if (!inputFile.is_open()) {
        cout << "Unable to open the file.\n";
        return 1;
    }

    int numberOfTransactions, numberOfFraudulentTransactions;
    inputFile >> numberOfTransactions >> numberOfFraudulentTransactions;

    for (int i = 0; i < numberOfTransactions; ++i) {
        int transactionId;
        double transactionAmount;
        char comma;
        inputFile >> transactionId >> comma >> transactionAmount;
        insertTransaction(transactionId, transactionAmount);
    }

    cout << "Enter the fraudulent transaction IDs: ";
    for (int i = 0; i < numberOfFraudulentTransactions; ++i) {
        int fraudulentId;
        inputFile >> fraudulentId;
        deleteTransaction(fraudulentId);
    }

    inputFile.close();

    printTransaction();

    return 0;
}

