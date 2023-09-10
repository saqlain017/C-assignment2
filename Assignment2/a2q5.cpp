#include <iostream>
#include <fstream>
using namespace std;

struct Element {
    int element;
    struct Element* next;
};

struct Element* start = NULL;

void insertElement(int value) {
    struct Element* temp = new Element;
    temp->element = value;
    temp->next = NULL;
    if (start == NULL) {
        start = temp;
    }
    else {
        struct Element* current = start;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = temp;
    }
}

void printThirdLast() {
    if (start == NULL || start->next == NULL || start->next->next == NULL) {
        cout << "-1";
        return;
    }

    struct Element* thirdLast = start;
    while (thirdLast->next->next->next != NULL) {
        thirdLast = thirdLast->next;
    }

    cout << "Third-to-last element: " << thirdLast->element << endl;
}

int main() {
    ifstream inputFile("E:/university/c++/Assignment2/TestCases/05/Test01.txt");
    if (!inputFile.is_open()) {
        cout << "Unable to open the file.\n";
        return 1;
    }

    int value;
    while (inputFile >> value) {
        insertElement(value);
    }

    inputFile.close();

    printThirdLast();

    return 0;
}

