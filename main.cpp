//
//  main.cpp
//  csdp250 pro3
//
//  Created by Chris Turnbull on 10/19/23.
//
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

// Stack using linked list
class Stack {
    Node* top;
public:
    Stack() : top(nullptr) {}

    void push(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = top;
        top = newNode;
    }

    int pop() {
        if(!top) return -1;
        Node* temp = top;
        int value = top->data;
        top = top->next;
        delete temp;
        return value;
    }

    bool isEmpty() {
        return top == nullptr;
    }
};


class Queue {
    Node *front, *rear;
public:
    Queue() : front(nullptr), rear(nullptr) {}

    void enqueue(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = nullptr;
        if (!rear) {
            front = rear = newNode;
            return;
        }
        rear->next = newNode;
        rear = newNode;
    }

    int dequeue() {
        if (!front) return -1;
        Node* temp = front;
        int value = front->data;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
        return value;
    }

    bool isEmpty() {
        return front == nullptr;
    }
};

int main() {
    double number;
    cout << "Enter a decimal number: ";
    cin >> number;

    // Step 1: Split the number
    int integerPart = static_cast<int>(number);
    double decimalPart = number - integerPart;

    // Step 2: Convert integer to binary using Stack
    Stack integerStack;
    while (integerPart) {
        integerStack.push(integerPart % 2);
        integerPart /= 2;
    }

    // Step 3: Convert decimal to binary using Queue
    Queue decimalQueue;
    for (int i = 0; i < 8 && decimalPart > 0; i++) {  // Limiting to 8 bits for precision
        decimalPart *= 2;
        if (decimalPart >= 1) {
            decimalQueue.enqueue(1);
            decimalPart -= 1;
        } else {
            decimalQueue.enqueue(0);
        }
    }

    
    cout << "Binary representation: ";
    while (!integerStack.isEmpty()) {
        cout << integerStack.pop();
    }
    cout << ".";
    while (!decimalQueue.isEmpty()) {
        cout << decimalQueue.dequeue();
    }
    cout << endl;

    return 0;
}
