
#include <iostream>
#include <string>
using namespace std;
#define MAX 100

class Stack {
private:
    int top;
    int yashwant[MAX];

public:
    Stack() {
        top = -1;
    }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == MAX - 1;
    }

    void push(int x) {
        if (isFull()) {
            cout << "Stack Overflow\n";
            return;
        }
        yashwant[++top] = x;
        cout << x << " pushed into stack\n";
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow\n";
            return -1;
        }
        return yashwant[top--];
    }

    bool isPalindrome(string str) {
        Stack tempStack;
        // Push all characters to stack
        for (char ch : str) {
            tempStack.push(ch);
        }
        // Pop from stack and compare
        for (char ch : str) {
            if (tempStack.pop() != ch) {
                return false;
            }
        }
        return true;
    }

    void display() {
        if (isEmpty()) {
            cout << "Stack is Empty\n";
            return;
        }
        cout << "Stack elements: ";
        for (int i = top; i >= 0; i--) {
            cout << yashwant[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    Stack s;
    int choice, x;
    string str;

    do {
        cout << "\nMenu:\n";
        cout << "1. Push\n";
        cout << "2. Pop\n";
        cout << "3. Check Palindrome\n";
        cout << "4. Display Stack\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter an element to push: ";
            cin >> x;
            s.push(x);
            break;

        case 2:
            x = s.pop();
            if (x != -1) {
                cout << x << " popped from stack\n";
            }
            break;

        case 3:
            cout << "Enter a string: ";
            cin >> str;
            if (s.isPalindrome(str)) {
                cout << str << " is a palindrome\n";
            } else {
                cout << str << " is not a palindrome\n";
            }
            break;

        case 4:
            s.display();
            break;

        case 5:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}
