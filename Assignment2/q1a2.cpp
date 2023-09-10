#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

int count = 0;

// struct customer with a customer id and a next pointer for linking
struct Customer {
    int customerID;
    struct Customer* next;
};

// pointers for maintaining mid
struct Customer* start = NULL;
struct Customer* mid = NULL;

// insert a customer
void insertCustomer(int customerID) {
    struct Customer* temp = new Customer;
    temp->customerID = customerID;
    temp->next = NULL;

    if (start == NULL) {
        start = temp;
        mid = temp;
    } else {
        struct Customer* current = start;
        struct Customer* prev = NULL;

        while (current != NULL) {
            prev = current;
            current = current->next;
        }

        prev->next = temp;

        // after insertion, it checks if it is even or odd
        if (count % 2 == 0) {
            mid = mid->next;
        }
    }

    count++;
}

void deleteCustomer() {
    if (start == NULL) {
        cout << "Linked List is empty. Nothing to delete." << endl;
        return;
    }

    struct Customer* current = start;
    struct Customer* prev = NULL;

    // Traverse to the last node
    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }

    // Check if the last node is the middle node
    if (current == mid) {
        mid = prev;
    }

    // If the list contains only one node, reset start to NULL
    if (prev == NULL) {
        start = NULL;
    } else {
        prev->next = NULL;
    }

    delete current;
    count--;
}

void getMiddledCustomer() {
    if (count == 0) {
        cout << "No customers available." << endl;
    } else if (count % 2 == 0) {
        cout << "Middle customers IDs: " << mid->customerID << " and " << mid->next->customerID << endl;
    } else if (mid != NULL) {
        cout << "Centered customer ID: " << mid->customerID << endl;
    }
}

int main() {
    ifstream inputFile("E:/university/c++/Assignment2/TestCases/01/Test01.txt");
    if (!inputFile.is_open()) {
        cout << "Unable to open the file." << endl;
        return 1;
    }

    string command;
    int customerID;

    while (inputFile >> command) {
        if (command == "ADD") {
            inputFile >> customerID;
            insertCustomer(customerID);
        } else if (command == "DELETE") {
            deleteCustomer();
        } else if (command == "END") {
            getMiddledCustomer(); // Print the centered customer
            cout << "Exiting..." << endl;
            return 0;
        } else {
            cout << "Invalid command: " << command << ". Skipping." << endl;
        }
    }

    inputFile.close();

    return 0;
}
//"E:/university/c++/TestCases/01/Test01.txt"
