#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Color_Chooser.H>
#include <FL/fl_draw.H>
#include <vector>
#include <fstream>

enum Tool { PENCIL, LINE, RECTANGLE, ELLIPSE };

class PaintCanvas : public Fl_Box {
public:
    PaintCanvas(int X, int Y, int W, int H, const char *L = 0) : Fl_Box(X, Y, W, H, L), currentTool(PENCIL), drawing(false) {
        currentColor = FL_BLACK;
    }

    void setTool(Tool tool) {
        currentTool = tool;
    }

    void setColor(Fl_Color color) {
        currentColor = color;
    }

    void clearCanvas() {
        drawings.clear();
        redraw();
    }

    void saveCanvas(const char* filename) {
        std::ofstream file(filename, std::ios::binary);
        if (file.is_open()) {
            for (const auto& drawing : drawings) {
                file.write((char*)&drawing, sizeof(drawing));
            }
            file.close();
        }
    }

protected:
    void draw() override {
        Fl_Box::draw();
        for (const auto& drawing : drawings) {
            fl_color(drawing.color);
            switch (drawing.tool) {
                case PENCIL:
                    for (size_t i = 1; i < drawing.points.size(); ++i) {
                        fl_line(drawing.points[i - 1].first, drawing.points[i - 1].second,
                                drawing.points[i].first, drawing.points[i].second);
                    }
                    break;
                case LINE:
                    fl_line(drawing.points[0].first, drawing.points[0].second,
                            drawing.points[1].first, drawing.points[1].second);
                    break;
                case RECTANGLE:
                    fl_rect(drawing.points[0].first, drawing.points[0].second,
                            drawing.points[1].first - drawing.points[0].first,
                            drawing.points[1].second - drawing.points[0].second);
                    break;
                case ELLIPSE:
                    fl_arc(drawing.points[0].first, drawing.points[0].second,
                           drawing.points[1].first - drawing.points[0].first,
                           drawing.points[1].second - drawing.points[0].second, 0, 360);
                    break;
            }
        }
    }

    int handle(int event) override {
        switch (event) {
            case FL_PUSH:
                drawing = true;
                currentDrawing.tool = currentTool;
                currentDrawing.color = currentColor;
                currentDrawing.points.push_back({Fl::event_x(), Fl::event_y()});
                return 1;
            case FL_DRAG:
                if (drawing && currentTool == PENCIL) {
                    currentDrawing.points.push_back({Fl::event_x(), Fl::event_y()});
                    redraw();
                }
                return 1;
            case FL_RELEASE:
                if (drawing) {
                    currentDrawing.points.push_back({Fl::event_x(), Fl::event_y()});
                    drawings.push_back(currentDrawing);
                    currentDrawing.points.clear();
                    drawing = false;
                    redraw();
                }
                return 1;
            default:
                return Fl_Box::handle(event);
        }
    }

private:
    struct Drawing {
        Tool tool;
        Fl_Color color;
        std::vector<std::pair<int, int>> points;
    };

    Tool currentTool;
    Fl_Color currentColor;
    bool drawing;
    Drawing currentDrawing;
    std::vector<Drawing> drawings;
};

class PaintApp {
public:
    PaintApp() {
        window = new Fl_Window(800, 600, "Paint Application");

        canvas = new PaintCanvas(10, 10, 780, 500);

        int toolButtonY = 520;

        Fl_Button *pencilButton = new Fl_Button(10, toolButtonY, 70, 30, "Pencil");
        pencilButton->callback([](Fl_Widget*, void* v) {
            ((PaintCanvas*)v)->setTool(PENCIL);
        }, canvas);

        Fl_Button *lineButton = new Fl_Button(90, toolButtonY, 70, 30, "Line");
        lineButton->callback([](Fl_Widget*, void* v) {
            ((PaintCanvas*)v)->setTool(LINE);
        }, canvas);

        Fl_Button *rectButton = new Fl_Button(170, toolButtonY, 90, 30, "Rectangle");
        rectButton->callback([](Fl_Widget*, void* v) {
            ((PaintCanvas*)v)->setTool(RECTANGLE);
        }, canvas);

        Fl_Button *ellipseButton = new Fl_Button(270, toolButtonY, 90, 30, "Ellipse");
        ellipseButton->callback([](Fl_Widget*, void* v) {
            ((PaintCanvas*)v)->setTool(ELLIPSE);
        }, canvas);

        Fl_Button *colorButton = new Fl_Button(370, toolButtonY, 70, 30, "Color");
        colorButton->callback([](Fl_Widget*, void* v) {
            Fl_Color c = ((PaintCanvas*)v)->color();
            double r = (c >> 24) & 0xFF;
            double g = (c >> 16) & 0xFF;
            double b = (c >> 8) & 0xFF;
            if (fl_color_chooser("Pick a Color", r, g, b)) {
                c = fl_rgb_color((uchar)r, (uchar)g, (uchar)b);
                ((PaintCanvas*)v)->setColor(c);
            }
        }, canvas);

        Fl_Button *clearButton = new Fl_Button(450, toolButtonY, 70, 30, "Clear");
        clearButton->callback([](Fl_Widget*, void* v) {
            ((PaintCanvas*)v)->clearCanvas();
        }, canvas);

        Fl_Button *saveButton = new Fl_Button(530, toolButtonY, 70, 30, "Save");
        saveButton->callback([](Fl_Widget*, void* v) {
            ((PaintCanvas*)v)->saveCanvas("drawing.bin");
        }, canvas);

        window->end();
    }

    void show() {
        window->show();
    }

private:
    Fl_Window *window;
    PaintCanvas *canvas;
};

int main() {
    PaintApp app;
    app.show();
    return Fl::run();
}
