#include <iostream>
using namespace std;

struct Node {
    string stop;
    Node* next;
};

Node* head = NULL;

// Add a bus stop
void insertStop(string name) {
    Node* newNode = new Node;
    newNode->stop = name;

    if (head == NULL) {
        head = newNode;
        newNode->next = head;
    } else {
        Node* temp = head;

        while (temp->next != head)
            temp = temp->next;

        temp->next = newNode;
        newNode->next = head;
    }
}

// Display all bus stops
void displayRoute() {
    if (head == NULL) {
        cout << "Route is empty";
        return;
    }

    Node* temp = head;

    do {
        cout << temp->stop << " -> ";
        temp = temp->next;
    } while (temp != head);

    cout << "(Back to " << head->stop << ")";
}

int main() {
    insertStop("Sangamner");
    insertStop("Akole");
    insertStop("Shirdi");
    insertStop("Nashik");

    cout << "Circular Bus Route:\n";
    displayRoute();

    return 0;
}