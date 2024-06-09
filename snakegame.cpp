#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/fl_draw.H>
#include <FL/fl_ask.H>
#include <vector>
#include <cstdlib>
#include <algorithm>  // Include for std::find

const int CELL_SIZE = 20;
const int ROWS = 30;
const int COLS = 30;

enum Direction { UP, DOWN, LEFT, RIGHT };

class SnakeGame : public Fl_Window {
public:
    SnakeGame() : Fl_Window(COLS * CELL_SIZE, ROWS * CELL_SIZE, "Snake Game"), direction(RIGHT) {
        // Initialize snake
        snake.push_back({10, 10});
        snake.push_back({9, 10});
        snake.push_back({8, 10});
        
        // Initialize food
        placeFood();

        // Initialize timer
        Fl::add_timeout(0.1, timerCallback, this);

        this->end();
    }

    int handle(int event) {
        switch (event) {
            case FL_KEYDOWN:
                switch (Fl::event_key()) {
                    case FL_Up:
                        if (direction != DOWN) direction = UP;
                        break;
                    case FL_Down:
                        if (direction != UP) direction = DOWN;
                        break;
                    case FL_Left:
                        if (direction != RIGHT) direction = LEFT;
                        break;
                    case FL_Right:
                        if (direction != LEFT) direction = RIGHT;
                        break;
                }
                return 1;
            default:
                return Fl_Window::handle(event);
        }
    }

private:
    std::vector<std::pair<int, int>> snake;
    std::pair<int, int> food;
    Direction direction;

    static void timerCallback(void *userdata) {
        SnakeGame *game = static_cast<SnakeGame*>(userdata);
        game->update();
        game->redraw();
        Fl::repeat_timeout(0.1, timerCallback, userdata);
    }

    void update() {
        // Move the snake
        auto head = snake.front();
        switch (direction) {
            case UP:    head.second -= 1; break;
            case DOWN:  head.second += 1; break;
            case LEFT:  head.first -= 1; break;
            case RIGHT: head.first += 1; break;
        }

        // Check for collisions
        if (head.first < 0 || head.first >= COLS || head.second < 0 || head.second >= ROWS ||
            std::find(snake.begin(), snake.end(), head) != snake.end()) {
            // Game over
            Fl::remove_timeout(timerCallback, this);
            fl_message("Game Over");
            exit(0);
        }

        // Check for food
        if (head == food) {
            snake.push_back(snake.back()); // Grow the snake
            placeFood(); // Place new food
        }

        // Move the snake
        for (size_t i = snake.size() - 1; i > 0; --i) {
            snake[i] = snake[i - 1];
        }
        snake[0] = head;
    }

    void draw() override {
        Fl_Window::draw();
        fl_color(FL_BLACK);
        fl_rectf(0, 0, w(), h());

        // Draw the snake
        fl_color(FL_GREEN);
        for (auto &segment : snake) {
            fl_rectf(segment.first * CELL_SIZE, segment.second * CELL_SIZE, CELL_SIZE, CELL_SIZE);
        }

        // Draw the food
        fl_color(FL_RED);
        fl_rectf(food.first * CELL_SIZE, food.second * CELL_SIZE, CELL_SIZE, CELL_SIZE);
    }

    void placeFood() {
        int x = std::rand() % COLS;
        int y = std::rand() % ROWS;
        food = {x, y};
    }
};

int main() {
    SnakeGame game;
    game.show();
    return Fl::run();
}
