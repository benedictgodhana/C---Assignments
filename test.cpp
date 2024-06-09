#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>

// Define global variables for windows and buttons
Fl_Window *loginWindow;
Fl_Window *registrationWindow;
Fl_Input *loginUsernameInput;
Fl_Input *loginPasswordInput;
Fl_Input *registrationUsernameInput;
Fl_Input *registrationPasswordInput;
Fl_Input *registrationEmailInput;

// Colors
Fl_Color backgroundColor = FL_WHITE;  // White background
Fl_Color textColor = FL_BLACK;        // Black text
Fl_Color buttonColor = FL_BLUE;       // Blue buttons

// Function to handle login button click
void showLogin(Fl_Widget *widget, void *data) {
    loginWindow->show();
    registrationWindow->hide();
}

// Function to handle registration button click
void showRegistration(Fl_Widget *widget, void *data) {
    registrationWindow->show();
    loginWindow->hide();
}

// Function to handle login action
void login(Fl_Widget *widget, void *data) {
    const char *username = loginUsernameInput->value();
    const char *password = loginPasswordInput->value();
    // Perform login authentication logic here
}

// Function to handle registration action
void registerUser(Fl_Widget *widget, void *data) {
    const char *username = registrationUsernameInput->value();
    const char *password = registrationPasswordInput->value();
    // Perform registration logic here
}

int main() {
    // Create login form window
    loginWindow = new Fl_Window(600, 300, "Login Form");
    loginWindow->color(backgroundColor); // Set background color
    Fl_Box *loginTitleLabel = new Fl_Box(20, 20, 360, 30, "Login Form");
    loginTitleLabel->align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE);
    loginTitleLabel->labelcolor(textColor); // Set text color
    loginUsernameInput = new Fl_Input(150, 60, 200, 30, "Username:");
    loginPasswordInput = new Fl_Input(150, 100, 200, 30, "Password:");
    Fl_Button *loginButton = new Fl_Button(150, 140, 90, 30, "Login");
    loginButton->color(buttonColor); // Set button color
    loginButton->callback(login);
    Fl_Button *registerButton = new Fl_Button(260, 140, 90, 30, "Register");
    registerButton->color(buttonColor); // Set button color
    registerButton->callback(showRegistration);
    loginWindow->end();

    // Create registration form window
    registrationWindow = new Fl_Window(600, 300, "Registration Form");
    registrationWindow->color(backgroundColor); // Set background color
    Fl_Box *registrationTitleLabel = new Fl_Box(20, 20, 360, 30, "Registration Form");
    registrationTitleLabel->align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE);
    registrationTitleLabel->labelcolor(textColor); // Set text color
    registrationUsernameInput = new Fl_Input(150, 60, 200, 30, "Username:");
    registrationEmailInput = new Fl_Input(150, 100, 200, 30, "Email:");
    registrationPasswordInput = new Fl_Input(150, 140, 200, 30, "Password:");
    Fl_Button *registerUserButton = new Fl_Button(150, 180, 90, 30, "Register");
    registerUserButton->color(buttonColor); // Set button color
    registerUserButton->callback(registerUser);
    Fl_Button *backToLoginButton = new Fl_Button(260, 180, 90, 30, "Login");
    backToLoginButton->color(buttonColor); // Set button color
    backToLoginButton->callback(showLogin);
    registrationWindow->end();

    // Show the login form initially
    loginWindow->show();
    registrationWindow->hide();

    return Fl::run();
}
