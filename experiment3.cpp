// Aim : 3
// Design, Develop and Implement a Program in C/C++ for converting an Infix Expression 
// to PostfixExpression. Program should support for both parenthesized and free parenthesized 
// expressions withthe operators: +, -, *, /, % (Remainder), ^ (Power) and alphanumeric operands
#include <iostream>
#include <stack>
#include <string>
using namespace std;

// Function to return the precedence of operators
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2; 
        case '^':
            return 3;
    }
    return -1; // For non-operators
}

// Function to convert infix expression to postfix expression
string infixToPostfix(string s) {
    stack<char> st;
    string result;

    for (int i = 0; i < s.length(); i++) {
        char c = s[i];

        // If the character is an operand, add it to the result
        if (isalnum(c)) {
            result += c;
        } 
        // If the character is '(', push it to the stack
        else if (c == '(') {
            st.push('(');
        } 
        // If the character is ')', pop and append until '(' is found
        else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                result += st.top();
                st.pop();
            }
            if (!st.empty()) st.pop(); // Remove '(' from the stack
        } 
        // If the character is an operator
        else {
            while (!st.empty() && precedence(c) <= precedence(st.top())) {
                result += st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    // Pop all the remaining operators in the stack
    while (!st.empty()) {
        result += st.top();
        st.pop(); 
    }

    return result;
}

int main() {
    string infix_exp;
    cout << "Enter an infix expression: ";
    cin >> infix_exp;

    string postfix_exp = infixToPostfix(infix_exp);
    cout << "Postfix expression: " << postfix_exp << endl;

    return 0;
}
