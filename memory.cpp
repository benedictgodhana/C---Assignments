#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

constexpr int NUM_CARDS = 16;
constexpr int GRID_SIZE = 4;

class MemoryGame {
public:
    MemoryGame() : window(400, 400, "Memory Game"), scoreBox(10, 10, 100, 20, "Score: 0") {
        initGame();
        window.end();
        window.callback([](Fl_Widget* w, void* data) { static_cast<MemoryGame*>(data)->onCardClick(w); }, this);
    }

    void show() {
        window.show();
    }

private:
    Fl_Window window;
    Fl_Box scoreBox;
    Fl_Button* cards[NUM_CARDS];
    std::vector<int> cardValues;
    int openCardIndex = -1;
    int score = 0;

    void initGame() {
        window.begin();
        generateRandomCardValues();
        int cardIndex = 0;
        for (int row = 0; row < GRID_SIZE; ++row) {
            for (int col = 0; col < GRID_SIZE; ++col) {
                int value = cardValues[cardIndex++];
                Fl_Button* button = new Fl_Button(100 * col, 40 * row + 40, 100, 40);
                button->label("?");
                button->user_data(this);
                button->callback([](Fl_Widget* w, void* data) {
                    static_cast<MemoryGame*>(data)->onCardClick(w);
                });
                cards[row * GRID_SIZE + col] = button;
            }
        }
    }

    void generateRandomCardValues() {
        cardValues.clear();
        for (int i = 0; i < NUM_CARDS / 2; ++i) {
            cardValues.push_back(i);
            cardValues.push_back(i);
        }
        std::random_shuffle(cardValues.begin(), cardValues.end());
    }

    void onCardClick(Fl_Widget* widget) {
        Fl_Button* button = static_cast<Fl_Button*>(widget);
        int index = buttonIndex(button);
        if (index == openCardIndex || button->label() != "?") return; // Already opened or matched
        button->label(std::to_string(cardValues[index]).c_str());
        button->redraw();
        if (openCardIndex == -1) {
            openCardIndex = index;
        } else {
            Fl_Button* openCard = cards[openCardIndex];
            if (cardValues[openCardIndex] == cardValues[index]) {
                score += 10;
                scoreBox.label(("Score: " + std::to_string(score)).c_str());
                openCard->deactivate();
                button->deactivate();
            } else {
                Fl::add_timeout(1.0, closeCardsTimeout, this);
            }
            openCardIndex = -1;
        }
    }

    static void closeCardsTimeout(void* data) {
        MemoryGame* game = static_cast<MemoryGame*>(data);
        game->closeCards();
    }

    void closeCards() {
        cards[openCardIndex]->label("?");
        cards[openCardIndex]->redraw();
        cards[buttonIndex(cards[openCardIndex])]->label("?");
        cards[buttonIndex(cards[openCardIndex])]->redraw();
    }

    int buttonIndex(Fl_Button* button) {
        for (int i = 0; i < NUM_CARDS; ++i) {
            if (cards[i] == button) return i;
        }
        return -1;
    }
};

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    MemoryGame game;
    game.show();
    return Fl::run();
}
