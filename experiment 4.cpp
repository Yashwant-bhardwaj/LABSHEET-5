// Aim : 4 
// Design, Develop and Implement a menu driven Program in C/C++ for the following 
// operations on QUEUE of Characters 
// a. Insert an Element on to Linear QUEUE 
// b. Delete an Element from Linear QUEUE
/*
Name: Yashwant 
Rollno : 2301010329 
section: 05
btech cse 
*/
#include <iostream>
using namespace std;
#define MAX 100

class Queue {
private:
    int front, rear;
    char queue[MAX];

public:
    Queue() {
        front = -1;
        rear = -1;
    }

    bool isEmpty() {
        return front == -1;
    }

    bool isFull() {
        return (rear + 1) % MAX == front;
    }

    void enqueue(char x) {
        if (isFull()) {
            cout << "Queue Overflow\n";
            return;
        }
        if (isEmpty()) {
            front = rear = 0;
        } else {
            rear = (rear + 1) % MAX;
        }
        queue[rear] = x;
        cout << x << " enqueued to queue\n";
    }

    char dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow\n";
            return -1;
        }
        char x = queue[front];
        if (front == rear) {
            front = rear = -1; // Reset queue when last element is removed
        } else {
            front = (front + 1) % MAX;
        }
        return x;
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue is Empty\n";
            return;
        }
        cout << "Queue elements: ";
        for (int i = front; i != rear; i = (i + 1) % MAX) {
            cout << queue[i] << " ";
        }
        cout << queue[rear] << endl; // Print the last element
    }
};

int main() {
    Queue q;
    int choice;
    char x;

    do {
        cout << "\nMenu:\n";
        cout << "1. Enqueue\n";
        cout << "2. Dequeue\n";
        cout << "3. Display Queue\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter a character to enqueue: ";
                cin >> x;
                q.enqueue(x);
                break;
            case 2:
                x = q.dequeue();
                if (x != -1) {
                    cout << x << " dequeued from queue\n";
                }
                break;
            case 3:
                q.display();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}
