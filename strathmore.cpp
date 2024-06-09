#include <iostream>
using namespace std;

// Function prototypes
void line();
void message();
void header();
int main() {
    // Print title of the vision statement

    header();
    // Print line of dots to visually separate the title from the vision statement
    line();

    // Print the vision statement
    message();

    return 0;
}


void header(){
        cout << "Strathmore University Vision\n";
}

// Function to print a line of dots
void line() {
    cout << "...........................\n\n";
}

// Function to print the vision statement
void message() {
    cout << "To become a leading outcome-driven entrepreneurial research \n";
    cout << "University by translating our excellence into major contribution \n";
    cout << "to culture, economic well-being and quality of life\n";
}
