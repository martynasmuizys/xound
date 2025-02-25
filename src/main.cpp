#include "audio/soundboard.hpp"
#include "ui/ui.hpp"

int main(int argc, char* argv[]) {
    Window win;
    win.init();

    Soundboard soundboard;
    soundboard.play_one();

    return 0;
    // return run(argc, argv);
}
