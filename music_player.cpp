#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Progress.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Media_Player.H>
#include <string>

class MusicPlayer {
public:
    MusicPlayer() : window(400, 300, "Music Player") {
        setupUI();
        window.end();
        window.resizable(window);
    }

    void show() {
        window.show();
    }

private:
    Fl_Window window;
    Fl_Button openButton;
    Fl_Button playButton;
    Fl_Button pauseButton;
    Fl_Button stopButton;
    Fl_Button nextButton;
    Fl_Button prevButton;
    Fl_Slider volumeSlider;
    Fl_Progress progressBar;
    Fl_Output fileNameOutput;
    Fl_Multiline_Output statusOutput;

    void setupUI() {
        window.begin();

        openButton = Fl_Button(10, 10, 80, 30, "Open");
        openButton.callback([](Fl_Widget* w, void* data) {
            static_cast<MusicPlayer*>(data)->onOpen();
        }, this);

        playButton = Fl_Button(100, 10, 80, 30, "Play");
        playButton.callback([](Fl_Widget* w, void* data) {
            static_cast<MusicPlayer*>(data)->onPlay();
        }, this);

        pauseButton = Fl_Button(190, 10, 80, 30, "Pause");
        pauseButton.callback([](Fl_Widget* w, void* data) {
            static_cast<MusicPlayer*>(data)->onPause();
        }, this);

        stopButton = Fl_Button(280, 10, 80, 30, "Stop");
        stopButton.callback([](Fl_Widget* w, void* data) {
            static_cast<MusicPlayer*>(data)->onStop();
        }, this);

        nextButton = Fl_Button(10, 50, 80, 30, "Next");
        nextButton.callback([](Fl_Widget* w, void* data) {
            static_cast<MusicPlayer*>(data)->onNext();
        }, this);

        prevButton = Fl_Button(100, 50, 80, 30, "Previous");
        prevButton.callback([](Fl_Widget* w, void* data) {
            static_cast<MusicPlayer*>(data)->onPrevious();
        }, this);

        volumeSlider = Fl_Slider(10, 100, 350, 20, "Volume");
        volumeSlider.type(FL_HORIZONTAL);
        volumeSlider.bounds(0, 100);
        volumeSlider.value(50);
        volumeSlider.callback([](Fl_Widget* w, void* data) {
            static_cast<MusicPlayer*>(data)->onVolumeChange();
        }, this);

        progressBar = Fl_Progress(10, 130, 350, 20, "Progress");
        progressBar.minimum(0);
        progressBar.maximum(100);
        progressBar.value(0);

        fileNameOutput = Fl_Output(10, 170, 350, 20, "File:");

        statusOutput = Fl_Multiline_Output(10, 200, 350, 60, "Status:");
        statusOutput.text("Ready");

        window.end();
    }

    void onOpen() {
        Fl_File_Chooser chooser(".", "*", Fl_File_Chooser::SINGLE, "Open Audio File");
        chooser.show();
        while (chooser.shown())
            Fl::wait();
        if (chooser.value() != nullptr) {
            player.load(chooser.value());
            fileNameOutput.value(chooser.value());
        }
    }

    void onPlay() {
        player.play();
        statusOutput.text("Playing");
    }

    void onPause() {
        player.pause();
        statusOutput.text("Paused");
    }

    void onStop() {
        player.stop();
        statusOutput.text("Stopped");
    }

    void onNext() {
        // Implement next track functionality
    }

    void onPrevious() {
        // Implement previous track functionality
    }

    void onVolumeChange() {
        player.volume(volumeSlider.value() / 100.0);
    }
};

int main() {
    MusicPlayer player;
    player.show();
    return Fl::run();
}
