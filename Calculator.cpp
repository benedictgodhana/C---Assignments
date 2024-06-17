#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Box.H>
#include <string>
#include <sstream>

class Calculator : public Fl_Window {
public:
    Calculator(int w, int h, const char* title);

private:
    Fl_Input* display;
    std::string currentInput;
    std::string currentOperator;
    double operand1;
    bool operatorSet;

    static void ButtonCallback(Fl_Widget* widget, void* data);
    static void OperatorCallback(Fl_Widget* widget, void* data);
    static void ClearCallback(Fl_Widget* widget, void* data);
    static void EqualsCallback(Fl_Widget* widget, void* data);
};

Calculator::Calculator(int w, int h, const char* title) : Fl_Window(w, h, title) {
    display = new Fl_Input(10, 10, 280, 40);
    display->readonly(1);

    const char* buttons[] = {
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "-",
        "0", ".", "=", "+"
    };

    for (int i = 0; i < 16; ++i) {
        Fl_Button* btn = new Fl_Button(10 + (i % 4) * 70, 60 + (i / 4) * 70, 60, 60, buttons[i]);
        if (i % 4 == 3) {
            btn->callback(OperatorCallback, (void*)this);
        } else if (buttons[i] == std::string("=")) {
            btn->callback(EqualsCallback, (void*)this);
        } else {
            btn->callback(ButtonCallback, (void*)this);
        }
    }

    Fl_Button* clearButton = new Fl_Button(10, 340, 280, 40, "C");
    clearButton->callback(ClearCallback, (void*)this);

    operand1 = 0;
    operatorSet = false;

    end();
}

void Calculator::ButtonCallback(Fl_Widget* widget, void* data) {
    Calculator* calculator = (Calculator*)data;
    const char* label = widget->label();
    calculator->currentInput += label;
    calculator->display->value(calculator->currentInput.c_str());
}

void Calculator::OperatorCallback(Fl_Widget* widget, void* data) {
    Calculator* calculator = (Calculator*)data;
    if (!calculator->currentInput.empty()) {
        calculator->operand1 = std::stod(calculator->currentInput);
        calculator->currentInput.clear();
        calculator->currentOperator = widget->label();
        calculator->operatorSet = true;
    }
}

void Calculator::ClearCallback(Fl_Widget* widget, void* data) {
    Calculator* calculator = (Calculator*)data;
    calculator->currentInput.clear();
    calculator->currentOperator.clear();
    calculator->operand1 = 0;
    calculator->operatorSet = false;
    calculator->display->value("");
}

void Calculator::EqualsCallback(Fl_Widget* widget, void* data) {
    Calculator* calculator = (Calculator*)data;
    if (!calculator->currentInput.empty() && calculator->operatorSet) {
        double operand2 = std::stod(calculator->currentInput);
        double result = 0;
        if (calculator->currentOperator == "+") {
            result = calculator->operand1 + operand2;
        } else if (calculator->currentOperator == "-") {
            result = calculator->operand1 - operand2;
        } else if (calculator->currentOperator == "*") {
            result = calculator->operand1 * operand2;
        } else if (calculator->currentOperator == "/") {
            if (operand2 != 0) {
                result = calculator->operand1 / operand2;
            } else {
                calculator->display->value("Error");
                return;
            }
        }
        std::ostringstream resultStream;
        resultStream << result;
        calculator->display->value(resultStream.str().c_str());
        calculator->currentInput = resultStream.str();
        calculator->operatorSet = false;
    }
}

int main(int argc, char** argv) {
    Calculator calculator(300, 400, "Calculator");
    calculator.show(argc, argv);
    return Fl::run();
}
