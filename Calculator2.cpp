#include <iostream>
using namespace std;

// Function declarations
void addition(double num1, double num2);
void subtraction(double num1, double num2);
void multiplication(double num1, double num2);
void division(double num1, double num2);

int main() {
    char op;
    double num1, num2;

    // Display menu
    cout << "Simple Calculator" << endl;
    cout << "-----------------" << endl;
    cout << "Operations available:" << endl;
    cout << "+ Addition" << endl;
    cout << "- Subtraction" << endl;
    cout << "* Multiplication" << endl;
    cout << "/ Division" << endl;
    cout << "Enter operator (+, -, *, /): ";
    cin >> op;

    // Prompt user for numbers
    cout << "Enter two numbers: ";
    cin >> num1 >> num2;

    // Perform operation based on operator
    switch (op) {
        case '+':
            addition(num1, num2);
            break;
        case '-':
            subtraction(num1, num2);
            break;
        case '*':
            multiplication(num1, num2);
            break;
        case '/':
            division(num1, num2);
            break;
        default:
            cout << "Error: Invalid operator entered." << endl;
            break;
    }

    return 0;
}

// Function definitions
void addition(double num1, double num2) {
    cout << num1 << " + " << num2 << " = " << (num1 + num2) << endl;
}

void subtraction(double num1, double num2) {
    cout << num1 << " - " << num2 << " = " << (num1 - num2) << endl;
}

void multiplication(double num1, double num2) {
    cout << num1 << " * " << num2 << " = " << (num1 * num2) << endl;
}

void division(double num1, double num2) {
    if (num2 != 0) {
        cout << num1 << " / " << num2 << " = " << (num1 / num2) << endl;
    } else {
        cout << "Error: Division by zero is not allowed." << endl;
    }
}
