#include "app.h"

#include <opencv2/opencv.hpp>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Expected 2 video files as arguments." << std::endl;
        return 1;
    }

    App app{argv[1], argv[2]};
    app.run();

    return 0;
}