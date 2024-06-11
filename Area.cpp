#include <iostream>

using namespace std;
 
//Declare the function prototype
void Area();

//variable declaration
int area, width, length;

int main(){

//get the output
Area();

return 0;

}


void Area(){

//variable Initialization
length=8;
width=5;

//calculating the area of the Rectangle
area= length*width;


//print the output
cout<<"The area of " << length << " by " <<width<<  " is "<< area << endl;

}