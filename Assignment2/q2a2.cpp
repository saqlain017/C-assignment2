#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

struct MedianNode {
	int value;
	MedianNode* next;
	MedianNode* previous;
};

int isOdd = 0;
int totalNumbers = 0;
float currentMedian = 0;
MedianNode* head = NULL;

void AddToMedianList(int newValue) {
	MedianNode* newNode = (MedianNode*)malloc(sizeof(struct MedianNode));
	newNode->value = newValue;

	if (head == NULL) {
		// If the list is empty, set the new node as the head
		head = newNode;
		head->previous = NULL;
		head->next = NULL;
		currentMedian = head->value;
		isOdd = 1;
		totalNumbers = 1;
	}
	else {
		MedianNode* current = head;
		while (current->next != NULL && current->value < newNode->value) {
			current = current->next;
		}
		if (current == head && current->value >= newNode->value) {
			// Insert the new node before the head
			head = newNode;
			head->next = current;
			current->previous = head;
		}
		else if (current->next == NULL && current->value < newNode->value) {
			// Insert the new node at the end
			current->next = newNode;
			newNode->previous = current;
			newNode->next = NULL;
		}
		else {
			// Insert the new node in the middle
			MedianNode* currentPrev = current->previous;
			currentPrev->next = newNode;
			newNode->previous = currentPrev;
			newNode->next = current;
			current->previous = newNode;
		}
		totalNumbers++;

		if (isOdd == 0) {
			MedianNode* current = head;
			for (int c = 1; c != (totalNumbers + 1) / 2; c++) {
				current = current->next;
			}
			currentMedian = current->value;
			isOdd = 1;
		}
		else {
			MedianNode* current = head;
			for (int c = 1; c != (totalNumbers / 2); c++) {
				current = current->next;
			}
			float hold = current->value;
			current = current->next;
			currentMedian = (hold + current->value) / 2;
			isOdd = 0;
		}
	}
}

int main() {
	int number;
	int check = 0;
	ifstream inputFile("E:/university/c++/Assignment2/TestCases/02/Test03.txt");
	while (check != -1 && check != 10) {
		inputFile >> number;
		AddToMedianList(number);
		cout << "Current Median: " << currentMedian << endl;
		check = inputFile.get();
	}

}
