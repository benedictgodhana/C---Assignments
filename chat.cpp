#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Multiline_Output.H>
#include <iostream>
#include <string>

// Function to get chatbot response
std::string getResponse(const std::string& input) {
    if (input.find("hello") != std::string::npos || input.find("hi") != std::string::npos) {
        return "Hello! How can I assist you today?";
    } else if (input.find("how are you") != std::string::npos) {
        return "I'm just a bot, but I'm here to help you!";
    } else if (input.find("name") != std::string::npos) {
        return "I am a simple C++ chatbot.";
    } else if (input.find("weather") != std::string::npos) {
        return "I can't check the weather, but it's always sunny in the world of code!";
    } else {
        return "I'm not sure how to respond to that. Can you ask something else?";
    }
}

// Callback function for the button
void respond(Fl_Widget* w, void* data) {
    Fl_Input* input = (Fl_Input*)data;
    Fl_Multiline_Output* output = (Fl_Multiline_Output*)w->parent()->child(1);

    std::string userInput = input->value();
    std::string botResponse = getResponse(userInput);

    std::string currentText = output->value();
    currentText += "You: " + userInput + "\n";
    currentText += "Chatbot: " + botResponse + "\n\n";
    
    output->value(currentText.c_str());
    input->value("");
}

int main(int argc, char **argv) {
    Fl_Window *window = new Fl_Window(400, 300, "Chatbot");

    Fl_Input *input = new Fl_Input(60, 10, 300, 25, "You:");
    Fl_Button *button = new Fl_Button(150, 50, 100, 25, "Send");
    Fl_Multiline_Output *output = new Fl_Multiline_Output(10, 90, 380, 200, "Chat:");

    button->callback(respond, (void*)input);

    window->end();
    window->show(argc, argv);
    return Fl::run();
}
