#include <iostream>
using namespace std;

int main() {
    // Print a title with double quotes inside the string
    // The escape sequence \" is used to include double quotes within the string
    cout << "*****\"Escape Sequence Practice\"*****\n";
    
    // Print the introduction line for the BBIT program description
    cout << "BBIT is a university diploma designed to focus on\n";
    
    // Print the list of focus areas of the BBIT program
    // \t is used for a horizontal tab to indent the list items
    cout << "\t 1. Development \n";
    cout << "\t 2. Implementation, and \n";
    cout << "\t 3. Management of information systems \n";
    
    return 0; // Return 0 to indicate successful completion of the program
}
